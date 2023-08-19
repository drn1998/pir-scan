#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <locale.h>

#include "../../stopword.h"

int main() {
    StopwordCollection * stopwords;
    FILE * fp_stopwords;

    setlocale(LC_ALL, "");

    fp_stopwords = fopen("../../res/stopwords.csv", "r");

    if(fp_stopwords == NULL) exit(EXIT_FAILURE);

    stopwords = stopword_collection_from_file(fp_stopwords);

    if(stopwords == NULL) exit(EXIT_FAILURE);

    // Trivial cases
    assert(stopword_collection_check(stopwords, L"wäre") == true);
    assert(stopword_collection_check(stopwords, L"müsste") == true);
    assert(stopword_collection_check(stopwords, L"aber") == true);
    assert(stopword_collection_check(stopwords, L"Historizialität") == false);
    assert(stopword_collection_check(stopwords, L"Faksimile") == false);
    assert(stopword_collection_check(stopwords, L"dielektrisch") == false);

    // Case sensitivity
    assert(stopword_collection_check(stopwords, L"würde") == true);
    assert(stopword_collection_check(stopwords, L"Würde") == false); // e.g. "die Würde des Menschen"
    assert(stopword_collection_check(stopwords, L"möchte") == true);
    assert(stopword_collection_check(stopwords, L"Möchte") == true);
    assert(stopword_collection_check(stopwords, L"lasse") == true);
    assert(stopword_collection_check(stopwords, L"Lasse") == false); // Scandinavian first name
    assert(stopword_collection_check(stopwords, L"neuer") == true);
    assert(stopword_collection_check(stopwords, L"Neuer") == false); // German last name
    assert(stopword_collection_check(stopwords, L"ließ") == true);
    assert(stopword_collection_check(stopwords, L"Ließ") == true);
    assert(stopword_collection_check(stopwords, L"als") == true);
    assert(stopword_collection_check(stopwords, L"Als") == true);
    assert(stopword_collection_check(stopwords, L"ALS") == false);

    // Edge cases
    assert(stopword_collection_check(stopwords, L"") == false);
    assert(stopword_collection_check(stopwords, L"würdevoll") == false); // A stopword is a prefix of word tested

    stopword_collection_free(stopwords);

    fclose(fp_stopwords);

    exit(EXIT_SUCCESS);
}