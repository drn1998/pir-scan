#include <stdio.h>
#include <stdlib.h>

#include <locale.h>

#include "../src/circular-buffer.h"
#include "../src/corpus.h"
#include "../src/eval.h"
#include "../src/pir-code.h"
#include "../src/result_fmt.h"
#include "../src/sentence-break.h"
#include "../src/sentence-iterator.h"

int main() {
    FILE * input_fp;
    FILE * corpus_fp;
    FILE * result_fp;
    FILE * stopword_fp;

    CircularBuffer * words;

    StopwordCollection * stopwords;

    SentenceContextHandle * handle;
    Sentence * current_sentence = NULL;

    corpus_handle corpus;

    result_collection_t * res;
    fmt_t format;

    size_t sentence_no;

    wchar_t * test[1];
    wchar_t local[64];
    char pir[3] = {0, 0, 0};

    setlocale(LC_ALL, "");

    stopword_fp = fopen("../res/stopwords.csv", "r");

    if(stopword_fp == NULL) exit(EXIT_FAILURE);

    stopwords = stopword_collection_from_file(stopword_fp);

    fclose(stopword_fp);

    if(stopwords == NULL) exit(EXIT_FAILURE);

    input_fp = fopen("text", "r");
    if(input_fp == NULL) abort();

    corpus_fp = fopen("output_corpus", "w");
    if(corpus_fp == NULL) abort();

    result_fp = fopen("output_result", "w");
    if(result_fp == NULL) abort();

    words = circular_buffer_new(1, 64);
    if(words == NULL) abort();

    handle = sentence_iterator_new(input_fp, is_sentence_break);
    if(handle == NULL) abort();

    corpus = corpus_new_html(corpus_fp, 2, 2, 2, 3);
    corpus_write_head(corpus);
    corpus_write_first_title(corpus, "Example file");

    res = result_collection_new(false);
    format = format_new_plain(80, 62);

    do {
        current_sentence = sentence_iterator_sentence_next(handle);
        if(current_sentence == NULL) break;

        sentence_no = corpus_write_sentence(&corpus, current_sentence);
        for(register size_t i = 0; i < current_sentence->word_n; i++) {
            circular_buffer_add(words, current_sentence->word_v[i]);
            // If i > n_tokens - 1, always true with 1
            test[0] = circular_buffer_read(words, 0);
            if(eval(test, 1, pir, stopwords, NULL, 0) == 1) {
                wcscpy(local, test[0]);
                wcsrmbydfn(local, iswpunct);
                result_collection_add_result(res, L"This file", local, sentence_no, NULL, NULL);
            }
        }
        sentence_free(current_sentence);
    } while(1);

    corpus_write_end(corpus);
    result_write_file(stdout, res, format);

    result_collection_free(res);
    circular_buffer_free(words);
    sentence_iterator_free(handle);
    stopword_collection_free(stopwords);

    fclose(input_fp);
    fclose(corpus_fp);
    fclose(result_fp);
}
