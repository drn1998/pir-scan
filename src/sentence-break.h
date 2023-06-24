#ifndef SENTENCE_BREAK_H
#define SENTENCE_BREAK_H

#include <stdio.h>
#include <wchar.h>
#include <wctype.h>

#include "string-utilities.h"

/**
 * @brief A function that checks if two consecutive words are in different sentences.
 * Currently, only a version optimized for the German language is provided, it may
 * perform acceptable with english as well. Implementations for other languages are
 * hopefully added in the future, although this will largely depend on contributions
 * by those speaking the particular language.
 * @author Darius Runge (https://darius-runge.eu)
 */

/**
 * @brief Checks if a sentence break exists between the two consecutive words provided
 * as a wide string. This function does not, and never will work perfectly. It is meant
 * to be "good enough" for generating a printed corpus where each sentence has an index
 * number. However, some rare abbreviations, non-unicode based roman numerals made of
 * basic latin characters etc. cause it to return both false-positive and false-negative
 * results.
 * 
 * @param a The first word
 * @param b The second word
 * @return int: 1, if a sentence break is between the two tokens, otherwise 0
 */
int is_sentence_break(const wchar_t * a, const wchar_t * b);

#endif