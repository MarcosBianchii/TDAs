#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include <stdlib.h>

typedef void (*Job)(void *);
typedef struct ThreadPool ThreadPool;


// Instanciates a new `ThreadPool` with `nthreads` workers.
ThreadPool *threadpool_new(size_t nthreads);


// Assigns `job` to the first available worker.
//
// # Return
//
// Returns `0` on success and `1` on failure.
int threadpool_spawn(ThreadPool *pool, Job job, void *arg);


// Blocks the running thread until all workers finish their tasks.
void threadpool_wait(ThreadPool *pool);


// Returns the amount of running workers.
size_t threadpool_running(ThreadPool *pool);


// Returns the amount of threads in the pool.
size_t threadpool_len(ThreadPool *pool);


// Prints the state of the pool.
void threadpool_show(ThreadPool *pool);


// Free's the memory used by the thread pool.
//
// # Considerations
//
// This function will block until all workers have finished their task.
// It will not wait for the task queue to be empty, just for the running
// workers to finish. Consider calling `threadpool_wait` before this.
void threadpool_del(ThreadPool *pool);

#endif // __THREADPOOL_H__