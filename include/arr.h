#ifndef ARR_H
#define ARR_H

#include <stddef.h>

/**
 * @file arr.h
 * @brief Dynamic Array Implementation
 *
 * This header file declares the interface for a dynamic array (arr_t) data structure
 * and associated functions. The dynamic array supports operations such as insertion,
 * removal, access, and modification of elements. The array automatically resizes as needed
 * when elements are added or removed.
 */

/**
 * @struct arr_t
 * @brief A structure representing a dynamic array.
 *
 * The dynamic array is designed to store elements and grow as needed. It has the following members:
 * - `len`: The current number of elements in the array.
 * - `size`: The maximum capacity of the array.
 * - `arr`: A pointer to an array of elements.
 *
 * @note Users should not modify the structure directly. All interactions should
 *       be done via the provided functions.
 */
typedef struct _arr_t arr_t;

/**
 * @brief Creates a new dynamic array.
 *
 * This function allocates and initializes a dynamic array with the specified capacity.
 * Initially, the array will be able to store up to `size` elements.
 *
 * @param size The initial capacity of the array.
 *
 * @return A pointer to the created dynamic array.
 *
 * @note The array needs to be freed using `arr_destroy()` when no longer needed.
 */
arr_t *arr_create(size_t size);

/**
 * @brief Creates a copy of an existing dynamic array.
 *
 * This function creates and returns a new dynamic array that is a duplicate of the given source array.
 * The new array will have the same elements, but any subsequent modifications to the copied array
 * will not affect the original array and vice versa.
 *
 * @param source_arr A pointer to the dynamic array to be copied.
 *
 * @return A pointer to the newly created dynamic array that is a copy of the source.
 *
 * @note The caller is responsible for freeing the memory of the copied array using `arr_destroy()`
 *       when it is no longer needed.
 */
arr_t *arr_copy(arr_t *source_arr);

/**
 * @brief Pushes an element to the back of the array.
 *
 * This function adds a new element to the end of the dynamic array. If the array is full, it will
 * resize the array to accommodate the new element.
 *
 * @param arr A pointer to the dynamic array.
 * @param element A pointer to the element to be added.
 */
void arr_push_back(arr_t *arr, void *element);

/**
 * @brief Pushes an element to the front of the array.
 *
 * This function adds a new element to the front of the dynamic array. The array will shift existing
 * elements to accommodate the new element at the beginning.
 *
 * @param arr A pointer to the dynamic array.
 * @param element A pointer to the element to be added.
 */
void arr_push_front(arr_t *arr, void *element);

/**
 * @brief Gets the element at the specified index.
 *
 * This function retrieves the element at the given index in the dynamic array. If the index is out of bounds,
 * the program will abort. The caller should not free the element returned by this function.
 *
 * @param arr A pointer to the dynamic array.
 * @param i The index of the element to retrieve.
 *
 * @return A pointer to the element at the specified index.
 */
const void *arr_get(arr_t *arr, size_t i);

/**
 * @brief Sets the element at the specified index.
 *
 * This function replaces the element at the given index with a new element. If the index is out of bounds,
 * the program will abort. The function returns the replaced element, or NULL if the index was empty.
 *
 * @param arr A pointer to the dynamic array.
 * @param i The index of the element to replace.
 * @param element A pointer to the new element to be set.
 *
 * @return A pointer to the element that was replaced, or NULL if the index was empty.
 */
const void *arr_set(arr_t *arr, size_t i, void *element);

/**
 * @brief Inserts an element at the specified index.
 *
 * This function inserts an element at the given index in the dynamic array. All elements in or after the index
 * will be shifted to make room for the new element. If the index is out of bounds, the program will abort.
 *
 * @param arr A pointer to the dynamic array.
 * @param i The index where the new element should be inserted.
 * @param element A pointer to the element to be inserted.
 *
 * @return A pointer to the inserted element.
 */
void *arr_insert(arr_t *arr, size_t i, void *element);

/**
 * @brief Removes and returns the element at the front of the array.
 *
 * This function removes the element at the front of the array and shifts the remaining elements to the left.
 * The removed element is returned. The caller is responsible for freeing the removed element.
 *
 * @param arr A pointer to the dynamic array.
 *
 * @return A pointer to the element that was removed from the front of the array.
 */
const void *arr_pop_front(arr_t *arr);

/**
 * @brief Removes and returns the element at the back of the array.
 *
 * This function removes the element at the back of the array. The removed element is returned.
 * The caller is responsible for freeing the removed element.
 *
 * @param arr A pointer to the dynamic array.
 *
 * @return A pointer to the element that was removed from the back of the array.
 */
const void *arr_pop_back(arr_t *arr);

/**
 * @brief Removes and returns the element at the specified index.
 *
 * This function removes the element at the given index in the array. The remaining elements are shifted
 * to fill the gap. The removed element is returned, and the caller is responsible for freeing it.
 * If the index is out of bounds, the program will abort.
 *
 * @param arr A pointer to the dynamic array.
 * @param i The index of the element to remove.
 *
 * @return A pointer to the element that was removed from the array.
 */
const void *arr_remove(arr_t *arr, size_t i);

/**
 * @brief Returns the number of elements in the array.
 *
 * This function returns the current number of elements in the dynamic array.
 *
 * @param arr A pointer to the dynamic array.
 *
 * @return The number of elements in the array.
 */
size_t arr_len(arr_t *arr);

/**
 * @brief Checks if the array is empty.
 *
 * This function checks whether the dynamic array contains any elements.
 *
 * @param arr A pointer to the dynamic array.
 *
 * @return `1` if the array is empty, `0` otherwise.
 */
char arr_is_empty(arr_t *arr);

/**
 * @brief Returns the maximum capacity of the array.
 *
 * This function returns the maximum number of elements the array can hold before resizing is needed.
 *
 * @param arr A pointer to the dynamic array.
 *
 * @return The maximum capacity of the array.
 */
size_t arr_size(arr_t *arr);

/**
 * @brief Prints the elements of the array.
 *
 * This function prints the elements of the dynamic array. The `to_str` function is used to convert each
 * element to a string for printing.
 *
 * @param arr A pointer to the dynamic array to be printed.
 * @param to_str A function that converts each element in the array to a string.
 */
void arr_print(arr_t *arr, const char* (*to_str)(const void *));

/**
 * @brief Destroys the dynamic array and frees its associated memory.
 *
 * This function frees the memory used by the dynamic array's elements and the array itself.
 * If the elements in the array are pointers to dynamically allocated memory, the `free_func` is called
 * for each element before freeing the array structure.
 *
 * @param arr A pointer to the dynamic array to be destroyed.
 * @param free_func A function that frees the memory for each element in the array. This function
 *                  should take a pointer to an element as its argument and return void.
 *
 * @note The caller is responsible for providing an appropriate `free_func` if needed to avoid memory leaks.
 */
void arr_destroy(arr_t *arr, void (*free_func)(void *));

/**
 * @brief A constant function pointer that provides a default string representation of a pointer.
 *
 * This function pointer, `DEFAULT_TO_STR`, is used to obtain a string representation of a pointer. It is
 * particularly useful for debugging or logging purposes when you want to print the address or a simple
 * string representation of the pointer itself.
 *
 * The function pointed to by `DEFAULT_TO_STR` will return a string that represents the pointer address,
 * not the contents of the memory it points to.
 */
extern const char *(*const DEFAULT_TO_STR)(const void *);

#endif
