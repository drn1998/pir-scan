#ifndef EVAL_H
#define EVAL_H

#include <wchar.h>
#include <wctype.h>
#include <stdbool.h>

#include "string-utilities.h"
#include "stopword.h"
#include "pir-code.h"

/*** @brief The size of a token in characters */
#define TOKEN_SIZE 64

/**
 * @brief Evaluates a token by a PIR code
 * 
 * @param token_wcs The token that is evaluated 
 * @param pir_match The PIR code that is matched
 * @param exclude_stopword If true, stopwords will never evaluate to true
 * @param stem The function that is used for stemming or NULL if no stemming is desired
 * @param prefix The number of characters significant for the comparison
 * @return 1, if evaluated true, otherwise 0
 */
int eval(wchar_t ** token_v, size_t token_n, const char pir_match[PIR_CODE_LENGTH], StopwordCollection * stopwords, void(*stem)(wchar_t *), size_t prefix);

#endif