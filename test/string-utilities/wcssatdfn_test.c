#include <stdio.h>
#include <wctype.h>
#include <assert.h>
#include <locale.h>

#include "../../string-utilities.h"

int main() {
    wchar_t test_1[] = L"44f80e9";
    wchar_t test_2[] = L"lowercase";
    wchar_t test_3[] = L"Mixedcase";
    wchar_t test_4[] = L"UPPERCASE";
    wchar_t test_5[] = L"This sentence has 5 words.";
    wchar_t test_6[] = L"";
    wchar_t test_7[] = L"A";

    setlocale(LC_ALL, "");

    assert(wcssatdfn(test_1, iswxdigit) == 1);
    assert(wcssatdfn(test_1, iswalnum) == 1);
    assert(wcssatdfn(test_1, iswdigit) == 0);
    assert(wcssatdfn(test_1, iswpunct) == -1);

    assert(wcssatdfn(test_2, iswlower) == 1);
    assert(wcssatdfn(test_2, iswalpha) == 1);
    assert(wcssatdfn(test_2, iswcntrl) == -1);

    assert(wcssatdfn(test_3, iswlower) == 0);
    assert(wcssatdfn(test_3, iswupper) == 0);
    assert(wcssatdfn(test_3, iswalpha) == 1);
    assert(wcssatdfn(test_3, iswdigit) == -1);

    assert(wcssatdfn(test_4, iswalpha) == 1);
    assert(wcssatdfn(test_4, iswupper) == 1);
    assert(wcssatdfn(test_4, iswxdigit) == 0);  // Some are A to F by coincidence...

    assert(wcssatdfn(test_5, iswalnum) == 0);
    assert(wcssatdfn(test_5, iswblank) == 0);
    assert(wcssatdfn(test_5, iswprint) == 1);

    assert(wcssatdfn(test_6, iswdigit) == -1);
    assert(wcssatdfn(test_6, iswprint) == -1);

    assert(wcssatdfn(test_7, iswalpha) == 1);
    assert(wcssatdfn(test_7, iswdigit) == -1);

    return 0;
}