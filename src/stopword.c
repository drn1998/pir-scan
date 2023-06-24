#include "stopword.h"

static int stopword_cmp(const void * a, const void * b) {
    Stopword _a = *(Stopword*)a;
    Stopword _b = *(Stopword*)b;

    return wcscmp(_a.word, _b.word);
}

static StopwordCollection * stopword_collection_new() {
    StopwordCollection * new;

    new = malloc(sizeof(StopwordCollection));
    if(new == NULL) return NULL;

    new->stopword_a = 64;
    new->stopword_n = 0;

    new->stopword_v = malloc(sizeof(Stopword) * new->stopword_a);
    if(new->stopword_v == NULL) {
        free(new);
        return NULL;
    }

    return new;
}

static int stopword_collection_add_stopword(StopwordCollection * ptr, wchar_t * stopword, bool is_cs) {
    Stopword * tmp_realloc;

    if(ptr->stopword_a == ptr->stopword_n) {
        ptr->stopword_a *= 2;
        tmp_realloc = realloc(ptr->stopword_v, sizeof(Stopword) * ptr->stopword_a);
        if(tmp_realloc == NULL)
            return -1;
        
        ptr->stopword_v = tmp_realloc;
    }

    ptr->stopword_v[ptr->stopword_n].word = malloc((wcslen(stopword)+1) * sizeof(wchar_t));
    if(ptr->stopword_v[ptr->stopword_n].word == NULL) return -1;

    wcscpy(ptr->stopword_v[ptr->stopword_n].word, stopword);
    ptr->stopword_v[ptr->stopword_n].is_cs = is_cs;

    ptr->stopword_n++;

    return 0;
}

StopwordCollection * stopword_collection_from_file(FILE * fp_stopword_csv) {
    StopwordCollection * new;
    wchar_t stopword_buffer[MAX_WORD_LENGTH];
    int cs_input;

    if (fp_stopword_csv == NULL) abort();
    if (feof(fp_stopword_csv) || ferror(fp_stopword_csv)) return NULL;

    new = stopword_collection_new();
    if(new == NULL) return NULL;

    while(fwscanf(fp_stopword_csv, L" %l[^;];%i", stopword_buffer, &cs_input) != WEOF) {
        if(stopword_collection_add_stopword(new, stopword_buffer, cs_input) == -1) {
            stopword_collection_free(new);
            return NULL;
        }
    }

    qsort(new->stopword_v, new->stopword_n, sizeof(Stopword), stopword_cmp);

    return new;
}

bool stopword_collection_check(StopwordCollection * ptr, wchar_t * to_check) {
    Stopword key;
    Stopword * match;
    wchar_t search_word[MAX_WORD_LENGTH];
    uint8_t is_upper = 1;

    if(ptr == NULL || to_check == NULL) abort();

    wcscpy(search_word, to_check);
    if(iswupper(search_word[0])) {
        search_word[0] = towlower(search_word[0]);
    } else {
        is_upper = 0;
    }

    key.word = search_word;

    match = bsearch(&key, ptr->stopword_v, ptr->stopword_n, sizeof(Stopword), stopword_cmp);

    if(match == NULL) return false;

    if(match->is_cs == 0) return true;

    if(match->is_cs == 1) {
        if(is_upper == 1) return false;
        else if(is_upper == 0) return true;
    }

    return false;
}

void stopword_collection_free(StopwordCollection * ptr) {
    for(register size_t i = 0; i < ptr->stopword_n; i++) {
        free(ptr->stopword_v[i].word);
    }

    free(ptr->stopword_v);
    free(ptr);

    return;
}