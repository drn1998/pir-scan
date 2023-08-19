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

    res = result_collection_new(false);

    result_collection_add_result(res, L"Zweifelderwirtschaft", L"Waldfrüchte", 18, NULL, NULL);
    result_collection_add_result(res, L"Dreifelderwirtschaft", L"Zwangsarbeit", 138, NULL, NULL);
    result_collection_add_result(res, L"Zweifelderwirtschaft", L"Ackerbau", 189, NULL, NULL);
    result_collection_add_result(res, L"Dreifelderwirtschaft", L"Getreide", 83, NULL, NULL);
    result_collection_add_result(res, L"Dreifelderwirtschaft", L"Obstbaum", 118, NULL, NULL);
    result_collection_add_result(res, L"Zweifelderwirtschaft", L"Zentner", 19, NULL, NULL);

    result_collection_add_result(res, L"Dreifelderwirtschaft", L"Ackerbau", 28, NULL, NULL);
    result_collection_add_result(res, L"Zweifelderwirtschaft", L"Getreide", 49, NULL, NULL);
    result_collection_add_result(res, L"Dreifelderwirtschaft", L"Hochmittelalter", 61, NULL, NULL);
    result_collection_add_result(res, L"Zweifelderwirtschaft", L"Ackerbau", 29, NULL, NULL);
    result_collection_add_result(res, L"Dreifelderwirtschaft", L"Ackerbau", 92, NULL, NULL);
    result_collection_add_result(res, L"Zweifelderwirtschaft", L"Getreide", 48, NULL, NULL);
    result_collection_add_result(res, L"Dreifelderwirtschaft", L"Ackerbau", 23, NULL, NULL);
    result_collection_add_result(res, L"Dreifelderwirtschaft", L"Getreide", 83, NULL, NULL);
    result_collection_add_result(res, L"Dreifelderwirtschaft", L"Getreide", 17, NULL, NULL);

    result_collection_add_result(res, L"Zweifelderwirtschaft", L"Hochmittelalter", 189, NULL, NULL);
    result_collection_add_result(res, L"Dreifelderwirtschaft", L"Ackerbau", 43, NULL, NULL);
    result_collection_add_result(res, L"Zweifelderwirtschaft", L"Hochmittelalter", 18, NULL, NULL);
    result_collection_add_result(res, L"Dreifelderwirtschaft", L"Hochmittelalter", 28, NULL, NULL);
    result_collection_add_result(res, L"Zweifelderwirtschaft", L"Ackerbau", 489, NULL, NULL);
    result_collection_add_result(res, L"Zweifelderwirtschaft", L"Getreide", 49, NULL, NULL);
    result_collection_add_result(res, L"Zweifelderwirtschaft", L"Ackerbau", 183, NULL, NULL);
    result_collection_add_result(res, L"Dreifelderwirtschaft", L"Feldfrüchte", 8, NULL, NULL);

    result_collection_add_result(res, L"Dritte Sektion", L"Einzeltreffer", 28, NULL, NULL);
    result_collection_add_result(res, L"Dritte Sektion", L"Einzeltreffer", 47, NULL, NULL);
    result_collection_add_result(res, L"Dritte Sektion", L"Einzeltreffer", 1, NULL, NULL);

    result_write_file(stdout, res, format);

    result_collection_free(res);

    return 0;
}