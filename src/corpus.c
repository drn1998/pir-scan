#include "corpus.h"

corpus_handle corpus_new_plain(FILE * corpus_fp, size_t nth_sentence, uint8_t col, uint8_t row) {
    corpus_handle new;

    new.fp_out = corpus_fp;
    new.n = 0;

    new.fmt.interval = nth_sentence;
    new.fmt.format = TEXT_PLAIN;
    new.fmt.text.lines = row;
    new.fmt.text.columns = col;

    return new;
}

corpus_handle corpus_new_escp(FILE * corpus_fp, size_t nth_sentence, uint8_t col, uint8_t row) {
    corpus_handle new;

    new.fp_out = corpus_fp;
    new.n = 0;

    new.fmt.interval = nth_sentence;
    new.fmt.format = TEXT_ESCP;
    new.fmt.text.lines = row;
    new.fmt.text.columns = col;

    return new;
}

corpus_handle corpus_new_html(FILE * corpus_fp, size_t nth_sentence, uint8_t font_sz, uint8_t head_sz, uint8_t typographic_columns) {
    corpus_handle new;

    new.fp_out = corpus_fp;
    new.n = 0;

    new.fmt.interval = nth_sentence;
    new.fmt.format = HTML;
    new.fmt.html.font_sz = font_sz;
    new.fmt.html.head_sz = head_sz;
    new.fmt.html.columns = typographic_columns;

    return new;
}

int corpus_write_head(corpus_handle handle) {
    if(handle.fmt.format == HTML) {
        if(fwprintf(handle.fp_out, L"<!DOCTYPE html>\n<html>\n\t<body>") > 0)
            return 0;
        else return -1;
    }

    else return 0;
}

// Not a wide char as it will usually be a file name!
int corpus_write_first_title(corpus_handle handle, char * title) {
    if(handle.fmt.format == HTML) {
        if(fwprintf(handle.fp_out, L"<h1>%s</h1><p>", title) > 0)
            return 0;
        else return -1;
    }

    else return 0;
}

// Not a wide char as it will usually be a file name!
int corpus_write_next_title(corpus_handle handle, char * title) {
    if(handle.fmt.format == HTML) {
        if(fwprintf(handle.fp_out, L"</p><h1>%s</h1><p>", title) > 0)
            return 0;
        else return -1;
    }

    else return 0;
}


int corpus_write_sentence(corpus_handle * handle, Sentence * sentence) {
    switch (handle->fmt.format)
    {
    case TEXT_PLAIN:
    case TEXT_ESCP:
        for(register size_t i = 0; i < sentence->word_n; i++) {
            if(handle->n % handle->fmt.interval == 0)
                fwprintf(handle->fp_out, L"(%i)", handle->n);
            fwprintf(handle->fp_out, L"%ls ", sentence->word_v[i]);
            handle->n++;
        }
        break;
    case HTML:
        if(handle->n % handle->fmt.interval == 0)
            fwprintf(handle->fp_out, L"<sub>%i</sub>", handle->n + 1);
        for(register size_t i = 0; i < sentence->word_n; i++) {
            fwprintf(handle->fp_out, L"%ls ", sentence->word_v[i]);
        }
        handle->n++;
        break;
    default:
        break;
    }

    return handle->n;
}

// Not a wide char as it will usually be a file name!
int corpus_write_end(corpus_handle handle) {
    if(handle.fmt.format == HTML) {
        if(fwprintf(handle.fp_out, L"</p>\n</body></html>") > 0)
            return 0;
        else return -1;
    }

    else return 0;
}