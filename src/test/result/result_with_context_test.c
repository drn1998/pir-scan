#include <stdio.h>
#include <locale.h>

#include "../../result.h"
#include "../../result_fmt.h"

int main(int argc, char const *argv[])
{
    result_collection_t * res;
    fmt_t format;

    setlocale(LC_ALL, "");

    format = format_new_plain(80, 63);

    res = result_collection_new(true);

    result_collection_add_result(res, L"Zweifelderwirtschaft", L"Waldfrüchte", 23, L"Die meisten", L"trugen jedoch keine Samen.");
    result_collection_add_result(res, L"Zweifelderwirtschaft", L"Waldfrüchte", 18, L"Obwohl", L"schon lange angebaut wurden...");
    result_collection_add_result(res, L"Zweifelderwirtschaft", L"Römer", 2, L"Solche Zweifelderwirtschaft kannten vermutlich bereits die", L"");

    result_collection_add_result(res, L"Andreas Gryphius", L"Leiden", 2, L"Viele seiner Sonette thematisieren das", L"und Gebrechen des Lebens und der Welt.");
    result_collection_add_result(res, L"Andreas Gryphius", L"Leiden", 8, L"Nach seinem Studium in", L"wo er auch mit den Neuerungen der Philosophie in Berührung kam.");
    result_collection_add_result(res, L"Andreas Gryphius", L"Freistadt", 2, L"Im Buch 'Feurige", L", seinem größten prosaischen Werk, ...");

    result_write_file(stdout, res, format);

    result_collection_free(res);

    return 0;
}