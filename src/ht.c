#include "utils.h"
#include "ht.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @struct _kv_pair
 * @brief A structure representing a key-value pair in the hash table.
 *
 * This structure is used internally to store key-value pairs in the hash table.
 * Each entry holds a pointer to the key, a pointer to the value, and the index
 * of the next entry in the case of a collision.
 *
 * @note This structure is for internal usage only. Users should not modify it
 *       directly.
 *
 * @param k A pointer to the key.
 * @param v A pointer to the value associated with the key.
 * @param next The index of the next key-value pair in the event of a collision.
 */
typedef struct {
    const void *k;
    const void *v;
    size_t next;
} _kv_pair;

struct _ht_t {
    size_t len;
    size_t size;
    int (*equal)(const void *, const void *);
    unsigned (*hash)(const void *);
    const _kv_pair **arr;
};


ht_t *ht_create(size_t size, int (*equal)(const void *, const void *), unsigned (*hash)(const void *)) {
    ht_t *ht = malloc(sizeof(ht_t));
    ht->len = 0, ht->size = 0, ht->equal = equal, ht->hash = hash;
    ht->arr = malloc(size * sizeof(_kv_pair *));
    return ht;
};


void ht_destroy(ht_t *ht) {
    for (size_t i = 0; i < ht->len; i++)
        free((_kv_pair *)ht->arr[i]);
    free(ht->arr);
    free(ht);
};

void ht_insert(ht_t *ht, const void *k, const void *v) {
    if (ht->len + 1 >= ht->size) {
        fprintf(stderr, "ht_error: New length %ld is greater than ht size %ld\n", ht->len + 1, ht->size);
        abort();
    }

};
