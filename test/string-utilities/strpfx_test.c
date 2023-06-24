#include <stdio.h>
#include <assert.h>

#include "../../string-utilities.h"

int main() {
    assert(strpfx("prefix", "pre") == 1);
    assert(strpfx("decaffeination", "de") == 1);
    assert(strpfx("generic", "") == 1);
    assert(strpfx("test", "test") == 1);
    assert(strpfx("Dr. Murray", "Dr.") == 1);
    assert(strpfx("", "") == 1);

    assert(strpfx("", "a") == 0);
    assert(strpfx("", "aa") == 0);
    assert(strpfx("Test", "unrelated") == 0);
    assert(strpfx("Test", "wje") == 0);
    assert(strpfx("define", "De") == 0);
    assert(strpfx("define", "D") == 0);

    return 0;
}