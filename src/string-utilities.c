#include "string-utilities.h"

int wcsrmbydfn(wchar_t * ws, int(*discrim)(wint_t)) {
    register size_t i, n = 0;
    size_t sz;

    if(ws == NULL || discrim == NULL) abort();

    sz = wcslen(ws);

    for(i = 0; i < sz + 1; i++) {
        if(discrim(ws[i]) == 0) {
            ws[n] = ws[i];
            n++;
        }
    }

    return sz - wcslen(ws);
}

int wcseosdfn(const wchar_t * ws, int(*discrim)(wint_t)) {
    size_t sz;

    if(ws == NULL || discrim == NULL) abort();

    sz = wcslen(ws);

    if(sz == 0) return 0;

    if(discrim(ws[sz - 1]))
        return 1;
    
    return 0;
}

int wcssatdfn(const wchar_t * ws, int(*discrim)(wint_t)) {
    register size_t i, n;
    size_t sz;

    n = 0;

    if(ws == NULL || discrim == NULL) abort();

    sz = wcslen(ws);

    if(sz == 0) return -1;

    for (i = 0; i < sz; i++) {
        if(discrim(ws[i]) != 0)
            n++;
    }

    if(n == sz)
        return 1;
    else if(n > 0)
        return 0;
    else
        return -1;
}

int wcspfx(const wchar_t * ws, const wchar_t * px)
{
    if(ws == NULL || px == NULL) abort();

    return wcsncmp(px, ws, wcslen(px)) == 0;
}

int wcssfx(const wchar_t * ws, const wchar_t * sx)
{
    size_t lenstr = wcslen(ws);
    size_t lensuffix = wcslen(sx);

    if(ws == NULL || sx == NULL) abort();

    if (lensuffix > lenstr)
        return 0;
    return wcsncmp(ws + lenstr - lensuffix, sx, lensuffix) == 0;
}

int strpfx(const char * s, const char * px)
{
    if(s == NULL || px == NULL) abort();

    return strncmp(px, s, strlen(px)) == 0;
}