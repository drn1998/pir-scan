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

    buffer = circular_buffer_new(4, 6);

    if(buffer == NULL) return 0;

    for(register size_t i = 0; i < sizeof(words)/sizeof(wchar_t*); i++) {
        circular_buffer_add(buffer, words[i]);
    }

    assert(circular_buffer_add(buffer, L"bababadalgharaghtakamminarronnkonnbronntonnerronntuonnthunntrovarrhounawnskawntoohoohoordenenthurnuk!") == -1);

    circular_buffer_free(buffer);
}