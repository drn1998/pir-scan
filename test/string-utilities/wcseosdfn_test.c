#include <stdio.h>
#include <wctype.h>
#include <assert.h>
#include <locale.h>

#include "../../string-utilities.h"

int main() {
    wchar_t test_1[] = L"revisited.";
    wchar_t test_2[] = L"therefore,";
    wchar_t test_3[] = L"without";
    wchar_t test_4[] = L"";
    wchar_t test_5[] = L"a";
    wchar_t test_6[] = L":";

    setlocale(LC_ALL, "");

    assert(wcseosdfn(test_1, iswpunct) == 1);
    assert(wcseosdfn(test_2, iswpunct) == 1);
    assert(wcseosdfn(test_3, iswpunct) == 0);
    assert(wcseosdfn(test_4, iswpunct) == 0);
    assert(wcseosdfn(test_5, iswpunct) == 0);
    assert(wcseosdfn(test_6, iswpunct) == 1);

    return 0;
}

