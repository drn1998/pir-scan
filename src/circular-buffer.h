#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

/**
 * @brief Dynamically allocated array of fixed size containing the last n wide strings
 * that were added with the circular_buffer_add function.
 * 
 */

typedef struct {
    wchar_t ** v_circular_token; // Vector to the pointers to each token
    size_t n_circular_token;     // Number of tokens
    size_t l_circular_token;     // Maximum length of each single token
    size_t p_circular_tokens;    // Position
} CircularBuffer;

/**
 * @brief Create a new circular buffer with fixed number of wide strings of fixed length
 * 
 * @param nc Number of elements
 * @param lc Length of each element
 * @return CircularBuffer* Pointer to newly created CircularBuffer or NULL if parameters
 * or no dynamic memory was available.
 */
CircularBuffer * circular_buffer_new(size_t nc, size_t lc);

/**
 * @brief Frees a previously created CircularBuffer
 * 
 * @param cb The CircularBuffer to be freed
 */
void circular_buffer_free(CircularBuffer * cb);

/**
 * @brief Read the n-th element of the CircularBuffer, where higher values are
 * more recent entries
 * 
 * @param cb The CircularBuffer to be read from
 * @param index The index (0 is the last element still inside, nc-1 the most recent
 * element inside the buffer)
 * @return wchar_t* Reference to the n-th element (not a copy, must not be freed)
 */
wchar_t * circular_buffer_read(const CircularBuffer * cb, size_t index);

/**
 * @brief Add an element to the CircularBuffer
 * 
 * @param cb The CircularBuffer to be written to
 * @param token The wide character string to be added
 * @return int: 0, if the operation was successful, -1 if tokens length exceeds
 * the maximum of the particular buffer as declared when created
 */
int circular_buffer_add(CircularBuffer * cb, wchar_t * token);

/**
 * @brief Add an empty string to the CircularBuffer
 * 
 * @param cb The CircularBuffer to be written to
 */
void circular_buffer_push(CircularBuffer * cb);

/**
 * @brief Prints a formatted visualization of the CircularBuffer to stdout for
 * debugging and testing purposes. If the content of the buffer should be shown
 * to the user, please iterate over its members using circular_buffer_read and
 * implement a custom, appropriate formatting
 * 
 * @param cb The CircularBuffer to be printed
 */
void circular_buffer_print_dbg(CircularBuffer * cb);

#endif