#ifndef RESULT_H
#define RESULT_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <wchar.h>

typedef struct {
	wchar_t * pre_context;
	wchar_t * post_context;
	uint16_t sentence;
} with_context_result_t;

typedef struct {
	uint16_t sentence;
} no_context_result_t;

typedef struct {
	wchar_t * match_verb;
	void ** result_v; // Points to struct with context pointers or only sentence numbers
	size_t result_n;
	size_t result_a;
} match_t;

typedef struct {
	wchar_t * section_name;
	match_t ** match_v;
	size_t match_n;
	size_t match_a;
} section_t;

typedef struct {
	section_t ** section_v;
	size_t section_n;
	size_t section_a;
	bool has_context;
	bool sorted;
} result_collection_t;

result_collection_t * result_collection_new(bool has_context);
void result_collection_add_result(result_collection_t * collection, wchar_t * section, wchar_t * match_verb, uint16_t sentence_no, wchar_t * pre_context, wchar_t * post_context);
void result_collection_free(result_collection_t * collection);
void result_collection_sort(result_collection_t * collection);

#endif // RESULT_H