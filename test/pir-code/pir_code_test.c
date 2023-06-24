#include <assert.h>

#include "../../pir-code.h"

int main() {
    pir_t pir;

    pir_code_init(&pir);
    pir_code_write(L"E", &pir);
    assert(strncmp(pir.pir, "100", 3) == 0);

    pir_code_init(&pir);
    pir_code_write(L"sch", &pir);
    assert(strncmp(pir.pir, "800", 3) == 0);

    pir_code_init(&pir);
    pir_code_write(L"sche", &pir);
    assert(strncmp(pir.pir, "801", 3) == 0);

    pir_code_init(&pir);
    pir_code_write(L"test", &pir);
    assert(strncmp(pir.pir, "651", 3) == 0);

    pir_code_init(&pir);
    pir_code_write(L"TEST", &pir);
    assert(strncmp(pir.pir, "651", 3) == 0);
}