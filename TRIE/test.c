#include "src/trie.h"
#include <assert.h>


void
test_new()
{
    Trie t = trie_new();

    assert(!t.end);
    assert(t.count == 0);

    for (size_t i = 0; i < CHILDREN_LEN; i++) {
        assert(t.children[i] == NULL);
    }
}

void
test_add()
{
    Trie t = trie_new();
    trie_add(&t, "hello");
    trie_add(&t, "hell");
    trie_add(&t, "hello, world");

    assert(trie_contains(t, "hello, world"));
    assert(trie_contains(t, "hello"));
    assert(trie_contains(t, "hell"));

    trie_del(&t);
}

void
test_contains()
{
    Trie t = trie_new();

    // Add some fields.
    assert(!trie_add(&t, "Madagascar"));
    assert(!trie_add(&t, "Alex"));
    assert(!trie_add(&t, "Marty"));
    assert(!trie_add(&t, ""));
    assert(trie_add(&t, "Marty"));
    assert(trie_add(&t, ""));

    // Assert containing prefixes.
    assert(trie_contains_prefix(t, "Mad"));
    assert(trie_contains_prefix(t, "Mar"));
    assert(trie_contains_prefix(t, ""));
    assert(trie_contains_prefix(t, "A"));

    // Negatively assert the non-containing prefixes.
    assert(!trie_contains_prefix(t, "abc"));
    assert(!trie_contains_prefix(t, "bcd"));

    // Assert the containing strings.
    assert(trie_contains(t, "Madagascar"));
    assert(trie_contains(t, "Alex"));
    assert(trie_contains(t, "Marty"));

    // Negatively assert the non-containig fields.
    assert(!trie_contains(t, "Melman"));
    assert(!trie_contains(t, "Gloria"));
    assert(!trie_contains(t, "King Julian"));
    assert(!trie_contains(t, "Glory"));
    assert(!trie_contains(t, "King"));
    assert(!trie_contains(t, "Madaga"));

    // Assert the exsistance of strings when removed.
    assert(trie_rm(&t, ""));
    assert(trie_rm(&t, "Madagascar"));

    // Assert the lack of string when removed.
    assert(!trie_rm(&t, "Melman"));

    // Assert the lack of strings after removal.
    assert(!trie_contains(t, ""));
    assert(!trie_contains(t, "Madagascar"));
    assert(!trie_contains(t, "Melman"));

    // Assert the non-removed strings.
    assert(trie_contains(t, "Alex"));
    assert(trie_contains(t, "Marty"));

    // Repeat the procedure.
    assert(!trie_add(&t, ""));
    assert(!trie_add(&t, "Madagascar"));

    assert(trie_contains(t, ""));
    assert(trie_contains(t, "Madagascar"));

    assert(trie_rm(&t, ""));
    assert(trie_rm(&t, "Madagascar"));

    trie_del(&t);
}


int
main()
{
    test_new();
    test_add();
    test_contains();

    return 0;
}