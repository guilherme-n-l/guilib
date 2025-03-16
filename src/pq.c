#include "utils.h"
#include "pq.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define QUEUE(A, B, C) (A[B++] = C)
#define DEQUEUE(A, B) (B--, A[0])

#define MAX(A, B) ((A) > (B) ? (A) : (B))
#define UP(i) ((i - 1) >> 1)
#define LEFT(i) (2 * i + 1)
#define RIGHT(i) (LEFT(i) + 1)

typedef struct {
    int                 copies;
    const void          *val;
} _pq_node_t;

struct _pq_t {
    size_t              len;
    size_t              size;
    int                 (*compare)(const void *, const void *);
    _pq_node_t          **arr;
};

void _sift_down(pq_t *pq, size_t idx, char is_left) {
    size_t child_idx = is_left ? LEFT(idx) : RIGHT(idx);

    _pq_node_t *tmp = pq->arr[idx];
    pq->arr[idx] = pq->arr[child_idx];

    pq->arr[child_idx] = tmp;
}

void _sift_up(pq_t *pq, size_t i) {
    _pq_node_t *tmp = pq->arr[i];
    pq->arr[i] = pq->arr[UP(i)];

    pq->arr[UP(i)] = tmp;
}

pq_t *pq_create(size_t size, int (*func)(const void *, const void *)) {
    if (!func) {
        fprintf(stderr, "pq_error: Compare function must not be nullptr\n");
        abort();
    }

    pq_t *pq_ptr = malloc(sizeof(pq_t));
    pq_ptr->arr = malloc(size * sizeof(_pq_node_t *));
    pq_ptr->size = size;
    pq_ptr->len = 0;

    pq_ptr->compare = func;

    return pq_ptr;
}

void pq_destroy(pq_t *pq, void (*free_func)(void *)) {
    for (int i = 0; i < pq->len; i++)
        if (!--pq->arr[i]->copies) {
            if (free_func)
                free_func((void *)pq->arr[i]->val);

            free((void *)pq->arr[i]);
        }

    free(pq->arr);
    free(pq);
}

pq_t *pq_copy(pq_t *source_pq) {
    if (!source_pq) {
        fprintf(stderr, "pq_error: Trying to copy from nullptr\n");
        abort();
    }

    pq_t *pq_ptr = malloc(sizeof(pq_t));
    pq_ptr->arr = malloc(source_pq->size * sizeof(_pq_node_t *));
    pq_ptr->size = source_pq->size;
    pq_ptr->len = source_pq->len;
    pq_ptr->compare = source_pq->compare;

    for (size_t i = 0; i < source_pq->len; i++) {
        pq_ptr->arr[i] = source_pq->arr[i];
        pq_ptr->arr[i]->copies++;
    }
    memcpy(pq_ptr->arr, source_pq->arr, source_pq->size * sizeof(void *));

    return pq_ptr;
}

char pq_is_empty(pq_t *pq) {
    return !pq->len;
}

void pq_insert(pq_t *pq, void *i) {
    if (!pq) {
        fprintf(stderr, "pq_error: Trying to insert to nullptr\n");
        abort();
    }

    if (pq->len + 1 > pq->size) {
        fprintf(stderr, "pq_error: New length %ld is greater than pq size %ld\n", pq->len + 1, pq->size);
        abort();
    }

    size_t idx = pq->len;

    _pq_node_t *i_node = malloc(sizeof(_pq_node_t));
    i_node->copies = 1;
    i_node->val = i;

    QUEUE(pq->arr, pq->len, i_node);

    while (idx > 0 && pq->compare(i_node->val, pq->arr[UP(idx)]->val) < 0) {
        _sift_up(pq, idx);
        idx = UP(idx);
    }
}

const void *pq_peek(pq_t *pq) {
    if (!pq) {
        fprintf(stderr, "pq_error: Trying to peek in nullptr\n");
        abort();
    }

    if (!pq->len) {
        fprintf(stderr, "pq_error: Trying to access element in empty pq\n");
        abort();
    }

    return pq->arr[0]->val;
}

const void *pq_remove(pq_t *pq) {
    if (!pq) {
        fprintf(stderr, "pq_error: Trying to remove from nullptr\n");
        abort();
    }

    if (!pq->len) {
        fprintf(stderr, "pq_error: Trying to remove element from empty pq\n");
        abort();
    }

    _pq_node_t *top_val = DEQUEUE(pq->arr, pq->len);

    if (!pq->len) {
        top_val->copies--;
        return top_val->val;
    }

    pq->arr[0] = pq->arr[pq->len];

    size_t idx = 0;

    while (
            (LEFT(idx) < pq->len && pq->compare(pq->arr[idx]->val, pq->arr[LEFT(idx)]->val) > 0) ||
            (RIGHT(idx) < pq->len && pq->compare(pq->arr[idx]->val, pq->arr[RIGHT(idx)]->val) > 0)
          ) {
        char is_left = RIGHT(idx) >= pq->len || pq->compare(pq->arr[LEFT(idx)]->val, pq->arr[RIGHT(idx)]->val) < 0;
        _sift_down(pq, idx, is_left);
        idx = is_left ? LEFT(idx) : RIGHT(idx);
    }

    top_val->copies--;
    return top_val->val;
}

size_t pq_len(pq_t *pq) {
    if (!pq) {
        fprintf(stderr, "pq_error: Trying to get len from nullptr\n");
        abort();
    }

    return pq->len;
}

size_t pq_size(pq_t *pq) {
    if (!pq) {
        fprintf(stderr, "pq_error: Trying to get size from nullptr\n");
        abort();
    }

    return pq->size;
}

void pq_print(pq_t *pq, const char* (* to_str)(const void *)) {
    if (!pq) {
        fprintf(stderr, "pq_error: Trying to print nullptr\n");
        abort();
    }

    if (!to_str) {
        fprintf(stderr, "pq_error: Must provide a print function\n");
        abort();
    }

    pq_t *cp = pq_copy(pq);

    while (!pq_is_empty(cp)) {
        const char *str = to_str(pq_remove(cp));
        printf(!pq_len(cp) ? "%s" : "%s ", str);
        free((void *)str);
    }

    pq_destroy(cp, NULL);
};
