/**
 * @file ht.h
 * @brief Hash Table Implementation
 * 
 * This header file declares the interface for a hash table (ht_t) data structure
 * and associated functions. The hash table supports insertion, removal, retrieval,
 * and destruction of elements based on a key-value mechanism.
 * 
 * The hash table is implemented using a hashing function for key comparison
 * and a collision resolution strategy.
 */
#ifndef HT_H
#define HT_H

#include <stddef.h>

/**
 * @struct ht_t
 * @brief A structure representing a hash table.
 *
 * The hash table is implemented with the following members:
 * - `len`: The current number of elements in the hash table.
 * - `size`: The number of buckets in the hash table.
 * - `equal`: A function used to check if two keys are equal.
 * - `hash`: A function used to compute the hash value of keys.
 * - `arr`: An array of pointers to the elements in the table.
 *
 * @note Users should not modify the structure directly. All interactions should
 *       be done via the provided functions.
 */
typedef struct _ht_t ht_t;

/**
 * @brief Creates a new hash table.
 *
 * This function allocates and initializes a hash table with the specified
 * size, key comparison function, and key hash function.
 *
 * @param size The number of entries the hash table can hold.
 * @param equal A function to compare keys for equality. The function should return:
 *        - Zero if the keys are equal.
 *        - A non-zero value if the keys are not equal.
 * @param hash A function that computes the hash value for a given key. The function
 *        should return an unsigned integer that represents the hash value of the key.
 *
 * @return A pointer to the created hash table.
 *
 * @note The hash table needs to be freed using `ht_destroy()` when no longer needed.
 */
ht_t *ht_create(size_t size, int (*equal)(const void *, const void *), unsigned (*hash)(const void *));

/**
 * @brief Destroys a hash table.
 *
 * This function frees the memory used by the hash table, including all of its
 * entries and keys. However, the caller is responsible for freeing any dynamically
 * allocated memory in the keys or values before or after destroying the table.
 *
 * @param ht A pointer to the hash table to be destroyed.
 */
void ht_destroy(ht_t *ht);

/**
 * @brief Inserts a key-value pair into the hash table.
 *
 * This function inserts a value into the hash table. The key is hashed using
 * the `compare` function to determine the correct bucket for insertion. If the
 * key already exists in the table, it will be updated with the new value.
 *
 * @param ht A pointer to the hash table.
 * @param k A pointer to the key. 
 * @param v A pointer to the value to be inserted. 
 * 
 * @note The caller is responsible for allocating memory for the key if needed.
 */
void ht_insert(ht_t *ht, const void *k, const void *v);

/**
 * @brief Removes a value in key from the hash table.
 *
 * This function removes a key-value pair from the hash table. The key is hashed
 * using the `compare` function to find the correct bucket and remove the pair.
 * If the key is not found, no operation is performed.
 *
 * @param ht A pointer to the hash table.
 * @param k A pointer to the key whose value is to be removed.
 * 
 * @return A pointer to the value associated with the key, or NULL if
 *         the key is not found.
 */
const void *ht_remove(ht_t *ht, const void *k);

/**
 * @brief Retrieves the value associated with a key in the hash table.
 *
 * This function looks up a key in the hash table and returns the corresponding
 * value. The key is hashed using the `compare` function to determine the correct
 * bucket for retrieval. If the key is not found, the function returns NULL.
 *
 * @param ht A pointer to the hash table.
 * @param k A pointer to the key to be looked up.
 *
 * @return A pointer to the value associated with the key, or NULL if the
 *         key is not found.
 */
const void *ht_get(ht_t *ht, const void *k);

/**
 * @brief Returns the number of entries in the hash table.
 *
 * This function returns the current number of key-value pairs stored in the hash table.
 *
 * @param ht A pointer to the hash table.
 * 
 * @return The number of elements in the hash table.
 */
size_t ht_len(ht_t *ht);

/**
 * @brief Returns the maximum size of the hash table.
 *
 * This function returns the maximum number of elements the hash table can hold.
 *
 * @param ht A pointer to the hash table.
 * 
 * @return The maximum size of the hash table.
 */
size_t ht_size(ht_t *ht);

/**
 * @brief Computes a hash value based on the address of the key.
 *
 * This function generates a hash value for a given key by directly using its
 * memory address. It treats the key as a pointer and casts it to an unsigned
 * integer value that represents the hash.
 *
 * @param k A pointer to the key whose hash value is to be computed.
 *
 * @return An unsigned integer representing the hash value of the key's address.
 */
unsigned ht_direct_hash(const void *k);

/**
 * @brief Compares two keys by their memory addresses.
 *
 * This function compares two keys by checking if their memory addresses are equal.
 *
 * @param k_a A pointer to the first key.
 * @param k_b A pointer to the second key.
 *
 * @return 0 if the memory addresses of the two keys are equal, a non-zero value otherwise.
 */
int ht_direct_equal(const void *k_a, const void *k_b);

/**
 * @brief Computes a hash value for a string.
 *
 * This function generates a hash value for the given string.
 *
 * @param k A pointer to the string whose hash value is to be computed.
 *
 * @return An unsigned integer representing the hash value of the string.
 */
unsigned ht_string_hash(const void *k);

/**
 * @brief Compares two strings for equality.
 *
 * This function compares two strings for equality.
 *
 * @param k_a A pointer to the first string.
 * @param k_b A pointer to the second string.
 *
 * @return 0 if the strings are equal, a non-zero value otherwise.
 */
int ht_string_equal(const void *k_a, const void *k_b);

#endif
