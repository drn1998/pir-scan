#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <locale.h>

#include "../../sentence-iterator.h"
#include "../../sentence-break.h"

int main() {
    SentenceContextHandle * handle;
    Sentence * current_sentence = NULL;
    FILE * fp_text;

    setlocale(LC_ALL, "");

    fp_text = fopen("example_text", "r");

    if(fp_text == NULL) {
        wprintf(L"Unable to open file 'example_text': Check read permission.\n");
        exit(EXIT_FAILURE);
    }

    handle = sentence_iterator_new(fp_text, is_sentence_break);
    if(handle == NULL) {
        fclose(fp_text);
        exit(EXIT_FAILURE);
    }

    do {
        current_sentence = sentence_iterator_sentence_next(handle);
        if(current_sentence == NULL) break;

        for(register size_t i = 0; i < current_sentence->word_n; i++) {
            wprintf(L"%ls ", current_sentence->word_v[i]);
        }

        wprintf(L"\n");
        sentence_free(current_sentence);
    } while(1);

    sentence_iterator_free(handle);
    fclose(fp_text);
}