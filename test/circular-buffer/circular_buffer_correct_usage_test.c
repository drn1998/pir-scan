#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <locale.h>

#include "../../circular-buffer.h"
#include "../../pir-scan-limits.h"

int main() {
    CircularBuffer * buffer;
    wchar_t * words[] = {L"This", L"is", L"a", L"test", L"for", L"a", L"cyclic", L"array", L"consisting", L"of", L"memory", L"for", L"four", L"words."};

    setlocale(LC_ALL, "");

    buffer = circular_buffer_new(4, 12);

    if(buffer == NULL) return 0;

    for(register size_t i = 0; i < sizeof(words)/sizeof(wchar_t*); i++) {
        circular_buffer_add(buffer, words[i]);
    }

    assert(wcscmp(L"memory", circular_buffer_read(buffer, 0)) == 0);
    assert(wcscmp(L"for", circular_buffer_read(buffer, 1)) == 0);
    assert(wcscmp(L"four", circular_buffer_read(buffer, 2)) == 0);
    assert(wcscmp(L"words.", circular_buffer_read(buffer, 3)) == 0);

    circular_buffer_free(buffer);
}