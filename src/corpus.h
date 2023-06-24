#ifndef CORPUS_H
#define CORPUS_H

#include <stdio.h>
#include <stdint.h>
#include "sentence-iterator.h"

typedef enum {
    TEXT_PLAIN, TEXT_ESCP, HTML, PS
} corpus_fmt_e;

typedef struct {
    uint8_t lines;
    uint8_t columns;
} corpus_text_fmt;

typedef struct {
	uint8_t font_sz;
    uint8_t head_sz;
    uint8_t columns;
} corpus_html_fmt;

typedef struct {
    size_t interval;
    corpus_fmt_e format;
    union {
        corpus_text_fmt text;
        corpus_html_fmt html;
    };
} corpus_fmt;

typedef struct {
    FILE * fp_out;
    size_t n;
    corpus_fmt fmt;
} corpus_handle;

corpus_handle corpus_new_plain(FILE * corpus_fp, size_t nth_sentence, uint8_t col, uint8_t row);
corpus_handle corpus_new_escp(FILE * corpus_fp, size_t nth_sentence, uint8_t col, uint8_t row);
corpus_handle corpus_new_html(FILE * corpus_fp, size_t nth_sentence, uint8_t font_sz, uint8_t head_sz, uint8_t typographic_columns);

int corpus_write_head(corpus_handle handle);
int corpus_write_first_title(corpus_handle handle, char * title);
int corpus_write_next_title(corpus_handle handle, char * title);
int corpus_write_sentence(corpus_handle * handle, Sentence * sentence);
int corpus_write_end(corpus_handle handle);

#endif