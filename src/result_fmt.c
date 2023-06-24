#include "result_fmt.h"

static fmt_t format_new_text_generic(uint8_t columns, uint8_t lines) {
    fmt_t new;

    new.text_fmt.columns = columns;
    new.text_fmt.lines = lines;

    return new;
}

fmt_t format_new_esc_p(uint8_t columns, uint8_t lines) {
    fmt_t new;

    new = format_new_text_generic(columns, lines);
    new.format = RESULT_TEXT_ESCP;

    return new;
}

fmt_t format_new_plain(uint8_t columns, uint8_t lines) {
    fmt_t new;

    new = format_new_text_generic(columns, lines);
    new.format = RESULT_TEXT_PLAIN;

    return new;
}

static fmt_t format_new_html_generic(wchar_t * title, uint8_t font_sz, uint8_t head_sz) {
    fmt_t new;

    new.format = RESULT_TEXT_HTML;
    new.html_fmt.generic_fmt.title = title;
    new.html_fmt.generic_fmt.font_sz = font_sz;
    new.html_fmt.generic_fmt.head_sz = head_sz;

    return new;
}

fmt_t format_new_html_marquee(wchar_t * title, uint8_t font_sz, uint8_t head_sz, uint8_t marquee_speed) {
    fmt_t new;

    new = format_new_html_generic(title, font_sz, head_sz);

    new.html_fmt.html_type = HTML_SCREEN;
    new.html_fmt.screen_fmt.marquee = (marquee_speed >= 100 ? marquee_speed : 100);

    return new;
}

fmt_t format_new_html_printout(wchar_t * title, uint8_t font_sz, uint8_t head_sz, uint8_t typographic_columns) {
    fmt_t new;

    new = format_new_html_generic(title, font_sz, head_sz);

    new.html_fmt.html_type = HTML_PRINTOUT;
    new.html_fmt.printout_fmt.columns = (typographic_columns >= 7 ? typographic_columns : 7);

    return new;
}

static void result_write_file_plaintext(FILE * fp_output, result_collection_t * write, fmt_t format) {
    if(!write->sorted) result_collection_sort(write);

    for(register size_t i = 0; i < write->section_n; i++) {
        fwprintf(fp_output, L"%ls\n\n", write->section_v[i]->section_name);
        for(register size_t j = 0; j < write->section_v[i]->match_n; j++) {
            if(!write->has_context) {
                fwprintf(fp_output, L"%ls: ", write->section_v[i]->match_v[j]->match_verb);
                for(register size_t k = 0; k < write->section_v[i]->match_v[j]->result_n; k++) {
                    if(k < write->section_v[i]->match_v[j]->result_n - 1) {
                        fwprintf(fp_output, L"%u, ", ((no_context_result_t**)write->section_v[i]->match_v[j]->result_v)[k]->sentence);
                    } else {
                        fwprintf(fp_output, L"%u\n", ((no_context_result_t**)write->section_v[i]->match_v[j]->result_v)[k]->sentence);
                    }
                }
            } else {
                fwprintf(fp_output, L"%ls\n", write->section_v[i]->match_v[j]->match_verb);
                for(register size_t k = 0; k < write->section_v[i]->match_v[j]->result_n; k++) {
                    fwprintf(fp_output, L"%3u: %ls $ %ls\n", ((with_context_result_t**)write->section_v[i]->match_v[j]->result_v)[k]->sentence,
                    ((with_context_result_t**)write->section_v[i]->match_v[j]->result_v)[k]->pre_context,
                    ((with_context_result_t**)write->section_v[i]->match_v[j]->result_v)[k]->post_context);
                }
            }
        }
        if(i < write->section_n - 1) fwprintf(fp_output, L"\n\n");
    }
}

void result_write_file(FILE * fp_output, result_collection_t * write, fmt_t format) {
    if(fp_output == NULL || write == NULL) abort();

    switch (format.format)
    {
    case RESULT_TEXT_PLAIN:
        result_write_file_plaintext(fp_output, write, format);
        break;
    
    default:
        break;
    }

    return;
}