#ifndef STRING_UTILITIES
#define STRING_UTILITIES

#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>

/**
 * @brief A collection of string functions for both wide and "narrow" strings as
 * needed within the pir-scan project. Unless specifically mentioned, any argument
 * of these functions must not be NULL, as this will cause an abnormal termination.
 * @author Darius Runge (https://darius-runge.eu)
 */

/**
 * @brief Remove individual characters from a wide string based on a discrimination
 * function in the style of wctype, such as iswupper, iswpunct, ...
 * 
 * @param ws The wide string from which the characters should be removed (the function
 * modifies this very string, create a copy if desirable)
 * @param discrim Pointer to a wctype-style character discrimination function
 * @return int: Number of characters actually removed
 */
int wcsrmbydfn(wchar_t * ws, int(*discrim)(wint_t));

/**
 * @brief Checks, whether the last wide character of a wide string satisfies a
 * discrimination function
 * 
 * @param ws The wide string from which the last character should be checked
 * @param discrim Pointer to a wctype-style character discrimination function
 * @return int: 1, if the last character satisfies the function, otherwise 0.
 * An empty wide string results in 0.
 */
int wcseosdfn(const wchar_t * ws, int(*discrim)(wint_t));

/**
 * @brief Checks if all, some or none wide characters in a wide string satisfy
 * a discrimination function
 * 
 * @param ws The wide string whose characters are to be checked
 * @param discrim Pointer to a wctype-style character discrimination function
 * @return int: 1, if all characters satisfy the function, 0, if some characters
 * do and -1, if not a single character does. An empty wide string results to -1.
 */
int wcssatdfn(const wchar_t * ws, int(*discrim)(wint_t));

/**
 * @brief Checks if a wide string has a particular prefix
 * 
 * @param ws The wide string which is to be tested for having a prefix
 * @param px The prefix
 * @return int: 1 if px is a prefix of ws (or they are identical), otherwise 0
 */
int wcspfx(const wchar_t * ws, const wchar_t * px);

/**
 * @brief Checks if a wide string has a particular suffix
 * 
 * @param ws The wide string which is to be tested for having a suffix
 * @param sx The suffix
 * @return int: 1 if sx is a suffix of ws (or they are identical), otherwise 0
 */
int wcssfx(const wchar_t * ws, const wchar_t * sx);

/**
 * @brief Checks if a string has a particular prefix
 * 
 * @param s The string which is to be tested for having a prefix
 * @param px The prefix
 * @return int: 1 if px is a prefix of s (or they are identical), otherwise 0
 */
int strpfx(const char * s, const char * px);

#endif