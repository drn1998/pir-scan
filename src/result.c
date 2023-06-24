#include "result.h"

int cmp_ctx_res(const void * a, const void * b) {
    with_context_result_t * _a = *(with_context_result_t**)a;
    with_context_result_t * _b = *(with_context_result_t**)b;

    return _a->sentence - _b->sentence;
}

int cmp_res(const void * a, const void * b) {
    no_context_result_t * _a = *(no_context_result_t**)a;
    no_context_result_t * _b = *(no_context_result_t**)b;

    return _a->sentence - _b->sentence;
}

int cmp_match(const void * a, const void * b) {
    match_t * _a = *(match_t**)a;
    match_t * _b = *(match_t**)b;

    return wcscmp(_a->match_verb, _b->match_verb);
}

int cmp_section(const void * a, const void * b) {
    section_t * _a = *(section_t**)a;
    section_t * _b = *(section_t**)b;

    return wcscmp(_a->section_name, _b->section_name);
}

void add_no_context_result(match_t * match, uint16_t sentence) {
    void ** tmp_realloc;

    for(register size_t i = 0; i < match->result_n; i++) {
        if(((no_context_result_t**)match->result_v)[i]->sentence == sentence)
            return;
    }

    if(match->result_n == match->result_a) {
        match->result_a *= 2;
        tmp_realloc = realloc(match->result_v, sizeof(no_context_result_t *) * match->result_a);
        if(tmp_realloc == NULL) { abort(); }
        match->result_v = tmp_realloc;
    }

    match->result_v[match->result_n] = malloc(sizeof(no_context_result_t));
    if(match->result_v[match->result_n] == NULL) { abort(); }

    ((no_context_result_t**)match->result_v)[match->result_n]->sentence = sentence;

    match->result_n++;

    return;
}

void add_context_result(match_t * match, uint16_t sentence, wchar_t * pre, wchar_t * post) {
    void ** tmp_realloc;

    for(register size_t i = 0; i < match->result_n; i++) {
        if(((with_context_result_t**)match->result_v)[i]->sentence == sentence)
            return;
    }

    if(match->result_n == match->result_a) {
        match->result_a *= 2;
        tmp_realloc = realloc(match->result_v, sizeof(with_context_result_t *) * match->result_a);
        if(tmp_realloc == NULL) { abort(); }
        match->result_v = tmp_realloc;
    }

    match->result_v[match->result_n] = malloc(sizeof(with_context_result_t));
    if(match->result_v[match->result_n] == NULL) { abort(); }

    ((with_context_result_t**)match->result_v)[match->result_n]->sentence = sentence;

    ((with_context_result_t**)match->result_v)[match->result_n]->pre_context = calloc(wcslen(pre) + 1, sizeof(wchar_t));
    if(((with_context_result_t**)match->result_v)[match->result_n]->pre_context == NULL) { abort(); }
    wcscpy(((with_context_result_t**)match->result_v)[match->result_n]->pre_context, pre);

    ((with_context_result_t**)match->result_v)[match->result_n]->post_context = calloc(wcslen(post) + 1, sizeof(wchar_t));
    if(((with_context_result_t**)match->result_v)[match->result_n]->post_context == NULL) { abort(); }
    wcscpy(((with_context_result_t**)match->result_v)[match->result_n]->post_context, post);

    match->result_n++;

    return;
}

match_t * match_where(section_t * section, const wchar_t * match_verb, bool has_context) {
    match_t ** tmp_realloc;

    for(register size_t i = 0; i < section->match_n; i++) {
        if(wcscmp(section->match_v[i]->match_verb, match_verb) == 0)
            return section->match_v[i];
    }

    if(section->match_n == section->match_a) {
        section->match_a *= 2;
        tmp_realloc = realloc(section->match_v, sizeof(match_t *) * section->match_a);
        if(tmp_realloc == NULL) { abort(); }
        section->match_v = tmp_realloc;
    }

    section->match_v[section->match_n] = malloc(sizeof(match_t));
    if(section->match_v[section->match_n] == NULL) { abort(); }

    section->match_v[section->match_n]->match_verb = calloc(wcslen(match_verb) + 1, sizeof(wchar_t));
    if(section->match_v[section->match_n]->match_verb == NULL) { abort(); }

    wcscpy(section->match_v[section->match_n]->match_verb, match_verb);

    section->match_v[section->match_n]->result_a = 8;
    section->match_v[section->match_n]->result_n = 0;

    section->match_v[section->match_n]->result_v = calloc(section->match_v[section->match_n]->result_a, has_context ? sizeof(no_context_result_t *) : sizeof(with_context_result_t *));

    section->match_n++;

    return section->match_v[section->match_n - 1];
}

section_t * section_where(result_collection_t * collection, const wchar_t * section) {
    section_t ** tmp_realloc;

    for(register size_t i = 0; i < collection->section_n; i++) {
        if(wcscmp(collection->section_v[i]->section_name, section) == 0)
            return collection->section_v[i];
    }

    if(collection->section_n == collection->section_a) {
        collection->section_a *= 2;
        tmp_realloc = realloc(collection->section_v, sizeof(section_t *) * collection->section_a);
        if(tmp_realloc == NULL) { abort(); }
        collection->section_v = tmp_realloc;
    }

    collection->section_v[collection->section_n] = malloc(sizeof(section_t));
    if(collection->section_v[collection->section_n] == NULL) { abort(); }

    collection->section_v[collection->section_n]->section_name = calloc(wcslen(section) + 1, sizeof(wchar_t));
    if(collection->section_v[collection->section_n]->section_name == NULL) { abort(); }

    wcscpy(collection->section_v[collection->section_n]->section_name, section);

    collection->section_v[collection->section_n]->match_a = 8;
    collection->section_v[collection->section_n]->match_n = 0;

    collection->section_v[collection->section_n]->match_v = calloc(collection->section_v[collection->section_n]->match_a, sizeof(match_t*));

    collection->section_n++;

    return collection->section_v[collection->section_n - 1];
}

result_collection_t * result_collection_new(bool has_context) {
    result_collection_t * gen;

    gen = calloc(1, sizeof(result_collection_t));

    if(gen == NULL) return NULL;

    gen->has_context = has_context;
    gen->sorted = false;
    gen->section_n = 0;
    gen->section_a = 8;

    gen->section_v = calloc(gen->section_a, sizeof(section_t));

    if(gen->section_v == NULL) {
        free(gen);
        return NULL;
    }

    return gen;
}


void result_collection_add_result(result_collection_t * collection, wchar_t * section, wchar_t * match_verb, uint16_t sentence_no, wchar_t * pre, wchar_t * post) {
    if(collection->has_context) {
        add_context_result(match_where(section_where(collection, section), match_verb, true), sentence_no, pre, post);
    } else {
        add_no_context_result(match_where(section_where(collection, section), match_verb, false), sentence_no);
    }

    collection->sorted = false;

    return;
}

void result_collection_sort(result_collection_t * collection) {
    for(register size_t i = 0; i < collection->section_n; i++) {
        for(register size_t j = 0; j < collection->section_v[i]->match_n; j++) {
            if(collection->has_context) {
                qsort(collection->section_v[i]->match_v[j]->result_v, collection->section_v[i]->match_v[j]->result_n, sizeof(with_context_result_t *), cmp_ctx_res);
            } else {
                qsort(collection->section_v[i]->match_v[j]->result_v, collection->section_v[i]->match_v[j]->result_n, sizeof(no_context_result_t *), cmp_res);
            }
        }
        qsort(collection->section_v[i]->match_v, collection->section_v[i]->match_n, sizeof(match_t *), cmp_match);
    }
    qsort(collection->section_v, collection->section_n, sizeof(section_t*), cmp_section);

    collection->sorted = true;

    return;
}

void result_collection_fprint_raw(result_collection_t * collection, FILE * f) {
    if(!collection->sorted) {
        result_collection_sort(collection);
    }

    for(register size_t i = 0; i < collection->section_n; i++) {
        fwprintf(f, L"%ls:\n", collection->section_v[i]->section_name);

        for(register size_t j = 0; j < collection->section_v[i]->match_n; j++) {
            fwprintf(f, L"  %ls: ", collection->section_v[i]->match_v[j]->match_verb);
            
            for(register size_t k = 0; k < collection->section_v[i]->match_v[j]->result_n; k++) {
                if(collection->has_context) {
                    fwprintf(f, L"%u", ((with_context_result_t**)collection->section_v[i]->match_v[j]->result_v)[k]->sentence);
                    fwprintf(f, L"(%ls", ((with_context_result_t**)collection->section_v[i]->match_v[j]->result_v)[k]->pre_context);
                    fwprintf(f, L"%ls", collection->section_v[i]->match_v[j]->match_verb);
                    fwprintf(f, L"%ls)\n", ((with_context_result_t**)collection->section_v[i]->match_v[j]->result_v)[k]->post_context);
                }
                else {
                    fwprintf(f, L"%u", ((no_context_result_t**)collection->section_v[i]->match_v[j]->result_v)[k]->sentence);
                    if(k < collection->section_v[i]->match_v[j]->result_n - 1)
                        fwprintf(f, L", ");
                }
            }
            fwprintf(f, L"\n");
        }
    }

    return;
}

void result_collection_free(result_collection_t * collection) {
    for(register size_t i = 0; i < collection->section_n; i++) {
        for(register size_t j = 0; j < collection->section_v[i]->match_n; j++) {
            for(register size_t k = 0; k < collection->section_v[i]->match_v[j]->result_n; k++) {
                if(collection->has_context) {
                    free(((with_context_result_t**)collection->section_v[i]->match_v[j]->result_v)[k]->pre_context);
                    free(((with_context_result_t**)collection->section_v[i]->match_v[j]->result_v)[k]->post_context);
                }
                free(collection->section_v[i]->match_v[j]->result_v[k]);
            }

            free(collection->section_v[i]->match_v[j]->result_v);
            free(collection->section_v[i]->match_v[j]->match_verb);
            free(collection->section_v[i]->match_v[j]);
        }

        free(collection->section_v[i]->match_v);
        free(collection->section_v[i]->section_name);
        free(collection->section_v[i]);
    }

    free(collection->section_v);
    free(collection);
}

/*
void result_collection_fprint_html(result_collection_t * collection, FILE * f, html_fmt_t format) {
    if(!collection->sorted) {
        result_collection_sort(collection);
    }

    fwprintf(f, L"<!DOCTYPE html>\n<html>\n\t<head>\n\t\t<title>%ls</title>\n\t\t", format.generic_fmt.title != NULL ? L"Result" : format.generic_fmt.title); // TODO This expression needs attention

    // format-depending style-sheet (not in existence for printout so far)
    switch(format.html_type) {
        case HTML_PRINTOUT:
        case HTML_SCREEN:
            fwprintf(f, L"<style>\r\n\t\th1 {\r\n\t\t\tfont-family: sans-serif;\r\n\t\t\t"
                        L"margin-bottom: 4px;\r\n\t\t\tfont-size: larger;\r\n\t\t}\r\n\t\t"
                        L"p {\r\n\t\t\tfont-family: sans-serif;\r\n\t\t\tmargin: 0;"
                        L"\r\n\t\t\tline-height: 1.2;\r\n\t\t}\r\n\t\t.content {\r\n\t\t\t"
                        L"width: 95%%;\r\n\t\t\tmax-width: 30em;\r\n\t\t\tmargin: 0 auto;"
                        L"\r\n\t\t}\r\n\t</style>");
            break;
        default:
            abort();    // Should not be possible
            break;
    }

    fwprintf(f, L"\r\n\t<meta name=\"viewport\" content=\""
                L"width=device-width, initial-scale=1.0,user-scalable=no\">"
                L"\n\t</head>\r\n\t<body>\r\n\t<div class=\"content\">\n\t\t");

    switch (format.html_type)
    {
        case HTML_PRINTOUT:
            // NOT IMPLEMENTED
            break;
        case HTML_SCREEN:
            fwprintf(f, L"<marquee direction=\"up\" scrollamount=\"%hu\">\n", format.screen_fmt.marquee);
            break;
        default:
            break;
    }

    for(register size_t i = 0; i < collection->section_n; i++) {
        fwprintf(f, L"\t\t<h1>%ls</h1>\n", collection->section_v[i]->section_name);

        for(register size_t j = 0; j < collection->section_v[i]->match_n; j++) {
            fwprintf(f, L"\t\t<p><em>%ls: </em>", collection->section_v[i]->match_v[j]->match_verb);
            
            for(register size_t k = 0; k < collection->section_v[i]->match_v[j]->result_n; k++) {
                if(collection->has_context) {
                    fwprintf(f, L"%u", ((with_context_result_t**)collection->section_v[i]->match_v[j]->result_v)[k]->sentence);
                    fwprintf(f, L"(%ls", ((with_context_result_t**)collection->section_v[i]->match_v[j]->result_v)[k]->pre_context);
                    fwprintf(f, L"%ls", collection->section_v[i]->match_v[j]->match_verb);
                    fwprintf(f, L"%ls)\n", ((with_context_result_t**)collection->section_v[i]->match_v[j]->result_v)[k]->post_context);
                }
                else {
                    fwprintf(f, L"%u", ((no_context_result_t**)collection->section_v[i]->match_v[j]->result_v)[k]->sentence);
                    if(k < collection->section_v[i]->match_v[j]->result_n - 1)
                        fwprintf(f, L", ");
                }
            }
            fwprintf(f, L"</p>\n");
        }
    }

    fwprintf(f, L"\t\t</div>\n\t</body>\n</html>");

    return;
}
*/