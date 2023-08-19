#include <stdio.h>
#include <assert.h>
#include <locale.h>

#include "../../string-utilities.h"

int main() {
    setlocale(LC_ALL, "");

    assert(wcssfx(L"Nation", L"ion") == 1);
    assert(wcssfx(L"Satisfaction", L"ion") == 1);
    assert(wcssfx(L"angry", L"gry") == 1);
    assert(wcssfx(L"hungry", L"gry") == 1);
    assert(wcssfx(L"native", L"tive") == 1);
    assert(wcssfx(L"test", L"") == 1);
    assert(wcssfx(L"test", L"t") == 1);
    assert(wcssfx(L"test", L"test") == 1);
    assert(wcssfx(L"", L"") == 1);

    assert(wcssfx(L"", L"a") == 0);
    assert(wcssfx(L"", L"aa") == 0);
    assert(wcssfx(L"Test", L"tt") == 0);
    assert(wcssfx(L"Test", L"d") == 0);
    assert(wcssfx(L"define", L"ewewewewewewew") == 0);
    assert(wcssfx(L"define", L"E") == 0);

    return 0;
}
