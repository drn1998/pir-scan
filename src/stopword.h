#ifndef STOPWORD_H
#define STOPWORD_H

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include <stdbool.h>
#include <stdint.h>

#include "pir-scan-limits.h"

typedef struct {
    wchar_t * word;
    uint8_t is_cs;
} Stopword;

typedef struct {
    Stopword * stopword_v;
    size_t stopword_n;
    size_t stopword_a;
} StopwordCollection;

StopwordCollection * stopword_collection_from_file(FILE * fp_stopword_csv);
bool stopword_collection_check(StopwordCollection * ptr, wchar_t * to_check);
void stopword_collection_free(StopwordCollection * ptr);

#endif