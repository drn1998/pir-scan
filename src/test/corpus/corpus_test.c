#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <locale.h>

#include "../../corpus.h"
#include "../../sentence-iterator.h"
#include "../../sentence-break.h"

int main() {
    SentenceContextHandle * handle;
    Sentence * current_sentence = NULL;
    FILE * fp_text;
    FILE * fp_corpus;

    corpus_handle corpus;   // TODO Inconsistent naming and pointer/value mismatch

    setlocale(LC_ALL, "");

    fp_text = fopen("example_text", "r");

    if(fp_text == NULL) {
        wprintf(L"Unable to open file 'example_text': Check read permission.\n");
        exit(EXIT_FAILURE);
    }

    fp_corpus = fopen("example_out", "w");

    if(fp_corpus == NULL) {
        wprintf(L"Unable to open file 'example_out': Check write permission.\n");
        exit(EXIT_FAILURE);
    }

    handle = sentence_iterator_new(fp_text, is_sentence_break);
    if(handle == NULL) {
        fclose(fp_text);
        exit(EXIT_FAILURE);
    }

    corpus = corpus_new_html(fp_corpus, 5, 2, 2, 3);
    corpus_write_head(corpus);
    corpus_write_first_title(corpus, "Example file");

    do {
        current_sentence = sentence_iterator_sentence_next(handle);
        if(current_sentence == NULL) break;

        corpus_write_sentence(&corpus, current_sentence);
        //wprintf(L"%ls", current_sentence->word_v[0]);
        sentence_free(current_sentence);
    } while(1);

    sentence_iterator_free(handle);
    corpus_write_end(corpus);

    fclose(fp_text);
    fclose(fp_corpus);
}