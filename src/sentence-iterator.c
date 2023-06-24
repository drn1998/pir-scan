#include "sentence-iterator.h"

static Sentence * sentence_new() {
    Sentence * new;

    new = malloc(sizeof(Sentence));
    if(new == NULL) return NULL;

    new->word_a = DEFAULT_WORD_COUNT_PER_SENTENCE;
    new->word_n = 0;
    new->word_v = malloc(sizeof(wchar_t*) * new->word_a);

    if(new->word_v == NULL) {
        free(new);
        return NULL;
    }

    return new;
}

static int sentence_add(Sentence * sentence, wchar_t * word) {
    wchar_t ** tmp_realloc;

    if(sentence == NULL || word == NULL) abort();

    if(sentence->word_a == sentence->word_n) {
        sentence->word_a *= 2;
        tmp_realloc = realloc(sentence->word_v, sizeof(wchar_t*) * sentence->word_a);

        if(tmp_realloc == NULL) {
            return -1;
        } else {
            sentence->word_v = tmp_realloc;
        }
    }

    sentence->word_v[sentence->word_n] = malloc((wcslen(word) + 1) * sizeof(wchar_t));

    if(sentence->word_v[sentence->word_n] == NULL) return -1;

    wcscpy(sentence->word_v[sentence->word_n], word);

    sentence->word_n++;

    return 0;
}

void sentence_free(Sentence * ptr) {
    for(register size_t i = 0; i < ptr->word_n; i++) {
        free(ptr->word_v[i]);
    }

    free(ptr->word_v);
    free(ptr);
}

SentenceContextHandle * sentence_iterator_new(FILE * fp_text, int(*eos)(const wchar_t *, const wchar_t *)) {
    SentenceContextHandle * new;

    if(fp_text == NULL || eos == NULL) abort();
    if(feof(fp_text) || ferror(fp_text)) return NULL;

    new = malloc(sizeof(SentenceContextHandle));
    if(new == NULL) return NULL;

    new->circ = circular_buffer_new(2, MAX_WORD_LENGTH);
    if(new->circ == NULL) {
        free(new);
        return NULL;
    }

    new->fp_text = fp_text;
    new->eos = eos;

    return new;
}

Sentence * sentence_iterator_sentence_next(SentenceContextHandle* handle) {
    Sentence * ret;
    wchar_t buffer[MAX_WORD_LENGTH];

    ret = sentence_new();
    if (ret == NULL) return NULL;

    if(wcslen(circular_buffer_read(handle->circ, 0)) != 0) sentence_add(ret, circular_buffer_read(handle->circ, 1));

    if(fwscanf(handle->fp_text, L" %63ls", buffer) == WEOF){
        sentence_free(ret);
        return NULL;
    }
    sentence_add(ret, buffer);
    circular_buffer_add(handle->circ, buffer);

    while(fwscanf(handle->fp_text, L" %63ls", buffer) != WEOF) {
        circular_buffer_add(handle->circ, buffer);
        if(handle->eos(circular_buffer_read(handle->circ, 0), circular_buffer_read(handle->circ, 1)) == 1) {
            return ret;
        }
        sentence_add(ret, buffer);
    }
    
    return ret;
}

void sentence_iterator_free(SentenceContextHandle * handle) {
    circular_buffer_free(handle->circ);
    free(handle);
}