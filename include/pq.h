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
 *        - A negative integer if the first element has higher priority than the second.
 *        - Zero if the two elements have equal priority.
 *        - A positive integer if the first element has lower priority than the second.
 *
 * @return A pointer to the created priority queue.
 *
 * @note The compare function must not be NULL
 * @note The priority queue needs to be freed using `pq_destroy()` when no longer needed.
 */
pq_t *pq_create(size_t size, int (*compare)(const void *, const void *));

/**
 * @brief Creates a copy of an existing priority queue.
 *
 * This function creates and returns a new priority queue that is a duplicate
 * of the given source priority queue. The new queue will have the same elements
 * and will maintain the same heap order as the source queue. The comparison function
 * will be copied, and the array of elements will be duplicated in memory.
 *
 * @param source_pq A pointer to the priority queue to be copied.
 *
 * @return A pointer to the newly created priority queue that is a copy of the source.
 *
 * @note The elements in the copied queue are the same as those in the original queue,
 *       but any subsequent modifications to the copied queue will not affect the original
 *       queue and vice versa.
 *
 * @note The caller is responsible for freeing the memory of the copied priority queue
 *       using `pq_destroy()` when it is no longer needed.
 */
pq_t *pq_copy(pq_t *source_pq);

/**
 * @brief Destroys a priority queue and frees its associated memory.
 *
 * This function frees the memory used by the priority queue's array and its elements.
 * If the elements in the queue are pointers to dynamically allocated memory, the function
 * will use the provided `free_func` to free each element individually before freeing the
 * memory for the array and the priority queue structure itself.
 *
 * @param pq A pointer to the priority queue to be destroyed.
 * @param free_func A pointer to a function that frees the memory for each element
 *       in the priority queue. This function should take a pointer to an element
 *       as its argument and return void. It is called for each element before
 *       the queue structure and array are freed.
 *
 * @note The caller is responsible for providing a valid `free_func` if needed. Failure to
 *       provide an appropriate `free_func` for dynamically allocated elements may lead to
 *       memory leaks.
 *
 * @note This function frees both the internal array holding the elements and the memory used
 *       by the priority queue structure itself.
 */
void pq_destroy(pq_t *pq, void (*free_func)(void *));

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

/**
 * @brief Prints the elements of a priority queue.
 *
 * This function prints the elements of the priority queue in order of their priority.
 * The `to_str` function is used to convert each element to a string for printing.
 *
 * @param pq A pointer to the priority queue to be printed.
 * @param to_str A function that converts each element in the queue to a string.
 */
void pq_print(pq_t *pq, const char* (*to_str)(const void *));

/**
 * @brief A constant function pointer that provides a string representation of a pointer.
 *
 * This function pointer, `DEFAULT_TO_STR`, is used to obtain a string representation
 * of a pointer. It is particularly useful for debugging or logging purposes, where you
 * may want to print the address or a simple string representation of the pointer itself.
 *
 * The function pointed to by `DEFAULT_TO_STR` will return a string that represents
 * the pointer address, not the contents of the memory it points to. It is a default
 * function used in the absence of a custom string conversion function for the elements
 * in the priority queue.
 *
 * @note The function `DEFAULT_TO_STR` will not dereference the pointer or attempt
 *       to display the value stored at the memory location; instead, it will only return
 *       a string representation of the pointer address.
 */
extern const char *(*const DEFAULT_TO_STR)(const void *);

#endif
