#include "pq.h"
#include <stdio.h>
#include <stdlib.h>

#define QUEUE(A, B, C) (A[B++] = C)
#define DEQUEUE(A, B) (B--, A[0])

#define MAX(A, B) ((A) > (B) ? (A) : (B))
#define UP(i) ((i - 1) >> 1)
#define LEFT(i) (2 * i + 1)
#define RIGHT(i) (LEFT(i) + 1)

struct _pq_t {
    size_t       len;
    size_t       size;
    int          (*compare)(const void *, const void *);
    const void   **arr;
};

void sift_down(pq_t *pq, size_t idx, char is_left) {
    size_t child_idx = is_left ? LEFT(idx) : RIGHT(idx);

    const void *tmp = pq->arr[idx];
    pq->arr[idx] = pq->arr[child_idx];

    pq->arr[child_idx] = tmp;
}

void sift_up(pq_t *pq, size_t i) {
    const void *tmp = pq->arr[i];
    pq->arr[i] = pq->arr[UP(i)];

    pq->arr[UP(i)] = tmp;
}

pq_t *pq_create(size_t size, int (*func)(const void *, const void *)) {
    pq_t *pq_ptr = malloc(sizeof(pq_t));
    pq_ptr->arr = malloc(size * sizeof(void *));
    pq_ptr->size = size;
    pq_ptr->len = 0;

    if (!func) {
        fprintf(stderr, "pq_error: Compare function must not be null\n");
        abort();
    }

    pq_ptr->compare = func;

    return pq_ptr;
}

void pq_destroy(pq_t *pq) {
    for (int i = 0; i < pq->len; i++) free((void *)pq->arr[i]);
    free(pq->arr);
    free(pq);
}

char pq_is_empty(pq_t *pq) {
    return !pq->len;
}

void pq_insert(pq_t *pq, void *i) {
    if (pq->len + 1 > pq->size) {
        fprintf(stderr, "pq_error: New length %ld is greater than pq size %ld\n", pq->len + 1, pq->size);
        abort();
    }

    size_t idx = pq->len;
    QUEUE(pq->arr, pq->len, i);
    
    while (idx > 0 && pq->compare(i, pq->arr[UP(idx)]) < 0) {
        sift_up(pq, idx);
        idx = UP(idx);
    }
}

const void *pq_peek(pq_t *pq) {
    if (pq->len == 0) {
        fprintf(stderr, "pq_error: Trying to access element in empty pq\n");
        abort();
    }
    return pq->arr[0];
}

const void *pq_remove(pq_t *pq) {
    if (pq->len == 0) {
        fprintf(stderr, "pq_error: Trying to remove element from empty pq\n");
        abort();
    }

    const void *top_val = DEQUEUE(pq->arr, pq->len);

    if (!pq->len) return top_val;

    pq->arr[0] = pq->arr[pq->len];

    size_t idx = 0;

    while (
            (LEFT(idx) < pq->len && pq->compare(pq->arr[idx], pq->arr[LEFT(idx)]) > 0) ||
            (RIGHT(idx) < pq->len && pq->compare(pq->arr[idx], pq->arr[RIGHT(idx)]) > 0)
          ) {
        char is_left = RIGHT(idx) >= pq->len || pq->compare(pq->arr[LEFT(idx)], pq->arr[RIGHT(idx)]) < 0;
        sift_down(pq, idx, is_left);
        idx = is_left ? LEFT(idx) : RIGHT(idx);
    }

    return top_val;
}

size_t pq_len(pq_t *pq) {
    return pq->len;
}

size_t pq_size(pq_t *pq) {
    return pq->size;
}
