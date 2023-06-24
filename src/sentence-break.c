#include "sentence-break.h"

static int is_special_sentence_delimiter(wint_t wc) {
    switch(wc) {
        case L'?':
        case L'!':
            return 1;
        default:
            return 0;
    }
}

static int is_vowel(wint_t wc) {
    wint_t vowel = towlower(wc);
    
    switch(vowel) {
        case L'a':
        case L'e':
        case L'i':
        case L'o':
        case L'u':
        case L'y':
        case L'ä':
        case L'ö':
        case L'ü':
            return 1;
        default:
            return 0;
    }
}

int is_sentence_break(const wchar_t * a, const wchar_t * b) {
    if(a == NULL || b == NULL) abort();
    
    if(iswlower(b[0])) return 0;
    
    if(wcseosdfn(a, is_special_sentence_delimiter)) return 1;
    
    if(a[wcslen(a) - 1] != L'.') return 0;
    
    if(wcssatdfn(a, is_vowel) != 0) return 0;
    
    return 1;
}