#ifndef UTILS_H
#define UTILS_H

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
