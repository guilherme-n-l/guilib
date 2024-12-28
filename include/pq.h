#ifndef PQ_H
#define PQ_H

#include <stddef.h>

/**
 * @file pq.h
 * @brief Priority Queue Implementation
 * 
 * This header file declares the interface for a priority queue (pq_t) data structure
 * and associated functions. The priority queue is implemented using a binary heap
 * and supports insertion, removal, peeking, and various utility functions.
 * The heap is maintained according to the provided comparison function.
 */

/**
 * @struct pq_t
 * @brief A structure representing a priority queue.
 *
 * The priority queue is implemented as a binary heap with the following members:
 * - `len`: The current number of elements in the priority queue.
 * - `size`: The maximum capacity of the priority queue.
 * - `compare`: A comparison function used to maintain heap order.
 * - `arr`: An array of pointers to the elements in the queue.
 *
 * @note Users should not modify the structure directly. All interactions should
 *       be done via the provided functions.
 */
typedef struct _pq_t pq_t;


/**
 * @brief Creates a new priority queue.
 *
 * This function allocates and initializes a priority queue with the specified 
 * maximum size and comparison function.
 *
 * @param size The maximum number of elements the priority queue can hold.
 * @param compare A comparison function used to maintain the heap order.
 *        The function should return:
 *        - A negative integer if the first element has lower priority than the second.
 *        - Zero if the two elements have equal priority.
 *        - A positive integer if the first element has higher priority than the second.
 *
 *        @note If `compare` is NULL, the function will abort.
 *
 * @return A pointer to the created priority queue.
 * 
 * @note The priority queue needs to be freed using `pq_destroy()` when no longer needed.
 */
pq_t *pq_create(size_t size, int (*compare)(const void *, const void *));

/**
 * @brief Destroys a priority queue.
 *
 * This function frees the memory used by the priority queue's array and its elements.
 * However, if the elements in the queue are pointers to structs, it will only free
 * the memory for the struct itself, not any dynamically allocated memory held by
 * the struct's attributes. The caller is responsible for freeing any such dynamically
 * allocated memory in the struct before or after destroying the queue.
 *
 * @param pq A pointer to the priority queue to be destroyed.
 */
void pq_destroy(pq_t *pq);

/**
 * @brief Inserts an element into the priority queue.
 *
 * This function inserts a new element into the queue and ensures that the heap
 * property is maintained. If the queue is full, the function will terminate the
 * program by calling `abort()`.
 *
 * @param pq A pointer to the priority queue.
 * @param i A pointer to the element to be inserted.
 *
 * @note If the priority queue is full, this function will terminate the program 
 *       by calling `abort()`.
 * 
 * @note The caller is responsible for allocating memory for the element `i`. 
 */
void pq_insert(pq_t *pq, void *i);

/**
 * @brief Checks if the priority queue is empty.
 *
 * This function checks if the priority queue contains any elements.
 *
 * @param pq A pointer to the priority queue.
 * 
 * @return `1` if the priority queue is empty, `0` otherwise.
 */
char pq_is_empty(pq_t *pq);

/**
 * @brief Returns the element at the top of the priority queue.
 *
 * This function provides access to the top element of the queue without removing it.
 * The top element is the one with the highest priority according to the comparison function.
 *
 * @param pq A pointer to the priority queue.
 * 
 * @return A pointer to the top element in the priority queue.
 * 
 * @note If the queue is empty, this function will abort the program.
 */
const void *pq_peek(pq_t *pq);

/**
 * @brief Removes and returns the element at the top of the priority queue.
 *
 * This function removes the top element of the priority queue and reorders the queue
 * to maintain the heap property. The element removed is returned.
 *
 * @param pq A pointer to the priority queue.
 * 
 * @return A pointer to the element that was removed from the top of the queue.
 * 
 * @note If the queue is empty, this function will abort the program.
 */
const void *pq_remove(pq_t *pq);

/**
 * @brief Returns the number of elements in the priority queue.
 *
 * This function returns the current number of elements in the priority queue.
 *
 * @param pq A pointer to the priority queue.
 * 
 * @return The number of elements in the priority queue.
 */
size_t pq_len(pq_t *pq);

/**
 * @brief Returns the maximum size of the priority queue.
 *
 * This function returns the maximum number of elements the priority queue can hold.
 *
 * @param pq A pointer to the priority queue.
 * 
 * @return The maximum size of the priority queue.
 */
size_t pq_size(pq_t *pq);

#endif 
