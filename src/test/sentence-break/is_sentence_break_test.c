#include <stdio.h>
#include <assert.h>
#include <locale.h>

#include "../../sentence-break.h"
#include "../../string-utilities.h"

int main() {
    setlocale(LC_ALL, "");

    assert(is_sentence_break(L"vorbereitet.", L"Nur") == 1);
    assert(is_sentence_break(L"genehmigt.", L"Sie") == 1);
    assert(is_sentence_break(L"versucht?", L"Bei") == 1);
    assert(is_sentence_break(L"zutreffend!", L"Somit") == 1);

    assert(is_sentence_break(L"", L"Nur") == 0);
    assert(is_sentence_break(L"Nur", L"") == 0);
    assert(is_sentence_break(L"", L"") == 0);
    assert(is_sentence_break(L"bzw.", L"morgen") == 0);
    assert(is_sentence_break(L"bzw.", L"Substitutionen") == 0);
    assert(is_sentence_break(L"Dr.", L"Frantz") == 0);
    assert(is_sentence_break(L"ich", L"wollte") == 0);
    assert(is_sentence_break(L"als", L"Bürgermeister") == 0);
    assert(is_sentence_break(L"Als", L"Bürgermeister") == 0);

    return 0;
}