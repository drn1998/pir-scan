#ifndef SENTENCE_ITERATOR_H
#define SENTENCE_ITERATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#include "circular-buffer.h"
#include "pir-scan-limits.h"

/**
 * @brief A module that can be used to read a text file sentence by sentence with the structure returned by
 * the iteration containing the individual words of the sentence.
 * @author Darius Runge (https://darius-runge.eu)
 */

/**
 * @brief Dynamic array containing pointers to every word in a sentence
 * 
 */
typedef struct {
    wchar_t ** word_v; // Pointer to pointers, each pointing to first character of n-th sentence
    size_t word_n; // Number of words actually present
    size_t word_a; // Number of pointers for words allocated, not neccessarily all in use
} Sentence;

/**
 * @brief A context handle to use the sentence iterator module for all sentences in a particular text file
 * 
 */
typedef struct {
    FILE * fp_text; // An stdio file pointer with an open read stream to the text file from which the sentences are read
    int(*eos)(const wchar_t *, const wchar_t *); // Function pointer to the sentence-break detection function
    CircularBuffer * circ; // A circular buffer containing the last two words read
} SentenceContextHandle;

/**
 * @brief Returns a SentenceContextHandle for a new sentence iteration
 * 
 * @param fp_text Pointer to an already opened file that has read permission and contains the text that shall be returned sentence_wise
 * @param eos Function pointer to a sentence-break function
 * @return SentenceContextHandle* The handle used in subsequent calls to sentence_iterator_sentence_next (must be freed after usage) or NULL if not enough dynamic memory is available
 */
SentenceContextHandle * sentence_iterator_new(FILE * fp_text, int(*eos)(const wchar_t *, const wchar_t *));

/**
 * @brief Returns the next sentence from a handle
 * 
 * @param handle The handle from which the sentence shall be returned
 * @return Sentence* The sentence read (must be freed after usage and before overwriting e.g. in a loop) or NULL if no further sentence can be read or if not enough dynamic memory is available
 * @bug Sentences containing a single word are not handled properly. They will not break the system, but are most likely contained at the start or end of another sentence.
 */
Sentence * sentence_iterator_sentence_next(SentenceContextHandle * handle);

/**
 * @brief Frees a sentence returned by sentence_iterator_sentence_next
 * 
 * @param ptr The sentence that should be freed
 */
void sentence_free(Sentence * ptr);

/**
 * @brief Frees a handle for the sentence iterator returned by sentence_iterator_free
 * 
 * @param handle 
 */
void sentence_iterator_free(SentenceContextHandle * handle);

#endif