#include <stdio.h>
#include <wctype.h>
#include <assert.h>
#include <locale.h>

#include "../../string-utilities.h"

int main() {
    wchar_t test_1[] = L"4From t4his sent4enc23e, eve14ry decimal digit 28094should be remo4ved.1454";
    wchar_t test_2[] = L"This sentence does not contain any decimal digits, and should therefore be unaltered.";
    wchar_t test_3[] = L"0123456789";
    wchar_t test_4[] = L"";

    setlocale(LC_ALL, "");

    size_t test_1_initial_length = wcslen(test_1);
    size_t test_2_initial_length = wcslen(test_2);

    assert(wcsrmbydfn(test_1, iswdigit) == 17);
    assert(test_1_initial_length - wcslen(test_1) == 17);
    assert(wcscmp(L"From this sentence, every decimal digit should be removed.", test_1) == 0);

    assert(wcsrmbydfn(test_2, iswdigit) == 0);
    assert(test_2_initial_length - wcslen(test_2) == 0);

    assert(wcsrmbydfn(test_3, iswdigit) == 10);
    assert(wcslen(test_3) == 0);
    assert(wcscmp(L"", test_3) == 0);

    assert(wcsrmbydfn(test_4, iswalnum) == 0);
    assert(wcslen(test_4) == 0);
    assert(wcscmp(L"", test_4) == 0);

    return 0;
}