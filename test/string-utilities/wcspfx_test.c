#include <stdio.h>
#include <assert.h>
#include <locale.h>

#include "../../string-utilities.h"

int main() {
    setlocale(LC_ALL, "");

    assert(wcspfx(L"prefix", L"pre") == 1);
    assert(wcspfx(L"decaffeination", L"de") == 1);
    assert(wcspfx(L"generic", L"") == 1);
    assert(wcspfx(L"test", L"test") == 1);
    assert(wcspfx(L"Dr. Murray", L"Dr.") == 1);
    assert(wcspfx(L"", L"") == 1);

    assert(wcspfx(L"", L"a") == 0);
    assert(wcspfx(L"", L"aa") == 0);
    assert(wcspfx(L"Test", L"unrelated") == 0);
    assert(wcspfx(L"Test", L"wje") == 0);
    assert(wcspfx(L"define", L"De") == 0);
    assert(wcspfx(L"define", L"D") == 0);

    return 0;
}