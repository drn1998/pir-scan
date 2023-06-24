#include "circular-buffer.h"

CircularBuffer * circular_buffer_new(size_t nc, size_t lc) {
    CircularBuffer * new;

    if(nc == 0 || lc == 0)
        return NULL;
    
    new = malloc(sizeof(CircularBuffer));
    if(new == NULL) return NULL;

    new->n_circular_token = nc;
    new->l_circular_token = lc;
    new->p_circular_tokens = 0;

    new->v_circular_token = calloc(nc, sizeof(wchar_t*));
    if(new->v_circular_token == NULL) {
        free(new);
        return NULL;
    }

    for(register size_t i = 0; i < nc; i++) {
        new->v_circular_token[i] = calloc(lc, sizeof(wchar_t));
        if(new->v_circular_token[i] == NULL) {
            for(register size_t j = 0; j < i; j++) {
                free(new->v_circular_token[j]);
            }
            free(new->v_circular_token);
            free(new);
            return NULL;
        }
    }

    return new;
}

void circular_buffer_free(CircularBuffer * cb) {
    for(register size_t i = 0; i < cb->n_circular_token; i++) {
        free(cb->v_circular_token[i]);
    }

    free(cb->v_circular_token);
    free(cb);

    return;
}

wchar_t * circular_buffer_read(const CircularBuffer * cb, size_t index) {
    if(index > cb->n_circular_token)
        return NULL;
    
    return cb->v_circular_token[(cb->p_circular_tokens + index) % cb->n_circular_token];
}

int circular_buffer_add(CircularBuffer * cb, wchar_t * token) {
    if(wcslen(token) < cb->l_circular_token) {
        wcscpy(cb->v_circular_token[cb->p_circular_tokens], token);
        cb->p_circular_tokens = (cb->p_circular_tokens + 1) % cb->n_circular_token;
        return 0;
    }

    return -1;
}

void circular_buffer_push(CircularBuffer * cb) {
    cb->v_circular_token[cb->p_circular_tokens][0] = L'\0';

    cb->p_circular_tokens = (cb->p_circular_tokens + 1) % cb->n_circular_token;

    return;
}

void circular_buffer_print_dbg(CircularBuffer * cb) {
    for(register size_t i = 0; i < cb->n_circular_token; i++) {
        wprintf(L"%02llu '%-*ls'\n", i, cb->l_circular_token, circular_buffer_read(cb, i));
    }

    wprintf(L"\n");

    return;
}