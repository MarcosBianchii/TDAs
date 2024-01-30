#include "deque.h"
#include "threadpool.h"
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>


typedef struct Task {
    Job func;
    void *arg;
} Task;


struct ThreadPool {
    pthread_t *workers;
    pthread_mutex_t work_lock;
    pthread_cond_t new_task, finished;
    size_t running, len;
    Deque tasks;
    bool exit;
};


static Task *
task_new(Job func, void *arg)
{
    Task *task = malloc(sizeof(Task));
    if (!task) return NULL;

    task->func = func;
    task->arg = arg;
    return task;

}


static void
task_del(void *task)
{
    free(task);
}


static void *
__f(void *__send)
{
    ThreadPool *pool = (ThreadPool *) __send;
    while (1) {
        pthread_mutex_lock(&pool->work_lock);
        while (deque_empty(pool->tasks) && !pool->exit) {
            pthread_cond_wait(&pool->new_task, &pool->work_lock);
        }

        if (pool->exit) {
            pthread_mutex_unlock(&pool->work_lock);
            break;
        }

        if (!deque_empty(pool->tasks)) {
            pool->running++;

            // Get task from queue.
            Task *task = deque_pop_front(&pool->tasks);
            pthread_mutex_unlock(&pool->work_lock);

            task->func(task->arg);
            task_del(task);

            // Decrement running tasks count.
            pthread_mutex_lock(&pool->work_lock);
            pool->running--;
        }

        // Signal that this task has finished.
        pthread_cond_signal(&pool->finished);
        pthread_mutex_unlock(&pool->work_lock);
    }

    return NULL;
}


ThreadPool *
threadpool_new(size_t nthreads)
{
    if (nthreads == 0) return NULL;

    ThreadPool *pool = calloc(1, sizeof(ThreadPool));
    if (!pool) return NULL;

    Deque tasks = deque_new(4 * nthreads);
    if (!tasks.vec) {
        free(pool);
        return NULL;
    }

    pthread_t *workers = malloc(nthreads * sizeof(pthread_t));
    if (!workers) {
        deque_del(&tasks, free);
        free(pool);
        return NULL;
    }

    // Initialize pool.
    *pool = (ThreadPool) {
        workers: workers,
        tasks: tasks,
        len: nthreads,
    };

    pthread_mutex_init(&pool->work_lock, NULL);
    pthread_cond_init(&pool->new_task, NULL);
    pthread_cond_init(&pool->finished, NULL);

    for (size_t i = 0; i < nthreads; i++) {
        pthread_create(&pool->workers[i], NULL, __f, pool);
    }

    return pool;
}


int
threadpool_spawn(ThreadPool *pool, Job job, void *arg)
{
    if (!pool || !job || pool->exit) return 1;

    Task *task = task_new(job, arg);
    if (!task) return 1;

    pthread_mutex_lock(&pool->work_lock);
    int res = deque_push_back(&pool->tasks, task);
    pthread_cond_signal(&pool->new_task);
    pthread_mutex_unlock(&pool->work_lock);
    return res;
}


size_t
threadpool_running(ThreadPool *pool)
{
    return pool ? pool->running : 0;
}


size_t
threadpool_len(ThreadPool *pool)
{
    return pool ? pool->len : 0;
}


void
threadpool_wait(ThreadPool *pool)
{
    if (!pool) return;

    pthread_mutex_lock(&pool->work_lock);

    while (!deque_empty(pool->tasks) || threadpool_running(pool) > 0) {
        pthread_cond_wait(&pool->finished, &pool->work_lock);
    }

    pthread_mutex_unlock(&pool->work_lock);
}


void
threadpool_show(ThreadPool *pool)
{
    printf("pool: %p\n", pool);
    if (!pool) return;

    printf("    running: %li\n", threadpool_running(pool));
    printf("    len: %li\n", threadpool_len(pool));
    printf("    exit: %s\n", pool->exit ? "true" : "false");

    printf("    tasks: %li\n", deque_len(pool->tasks));
    printf("    capacity: %li\n", deque_cap(pool->tasks));
}


void
threadpool_del(ThreadPool *pool)
{
    if (!pool || pool->exit) return;

    pthread_mutex_lock(&pool->work_lock);
    pool->exit = true;
    pthread_cond_broadcast(&pool->new_task);
    pthread_mutex_unlock(&pool->work_lock);

    for (size_t i = 0; i < pool->len; i++) {
        pthread_join(pool->workers[i], NULL);
    }

    pthread_mutex_destroy(&pool->work_lock);
    pthread_cond_destroy(&pool->new_task);
    pthread_cond_destroy(&pool->finished);

    deque_del(&pool->tasks, task_del);
    free(pool->workers);
    free(pool);
}
