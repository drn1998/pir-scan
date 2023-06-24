#ifndef RESULT_FMT_H
#define RESULT_FMT_H

#include <stdlib.h>
#include <stdint.h>
#include <wchar.h>

#include "result.h"

// TODO Add markdown!
typedef enum {
    RESULT_TEXT_PLAIN, RESULT_TEXT_ESCP, RESULT_TEXT_HTML
} format_e;

typedef enum {
    HTML_SCREEN, HTML_PRINTOUT
} html_type_e;

typedef struct {
	uint8_t marquee : 7;
} html_screen_fmt_t;

typedef struct {
    uint8_t columns : 3;
} html_printout_fmt_t;

typedef struct {
    wchar_t * title;
	uint8_t font_sz : 6;
    uint8_t head_sz : 6;
} html_generic_fmt_t;

typedef struct {
    html_generic_fmt_t generic_fmt;
    html_type_e html_type;
    union
    {
        html_printout_fmt_t printout_fmt;
        html_screen_fmt_t screen_fmt;
    };
} html_fmt_t;

typedef struct {
    uint8_t lines;
    uint8_t columns;
} text_fmt_t;

typedef struct {
    format_e format;
    union
    {
        html_fmt_t html_fmt;
        text_fmt_t text_fmt;
    };
} fmt_t;

fmt_t format_new_esc_p(uint8_t columns, uint8_t lines);
fmt_t format_new_plain(uint8_t columns, uint8_t lines);
fmt_t format_new_html_marquee(wchar_t * title, uint8_t font_sz, uint8_t head_sz, uint8_t marquee_speed);
fmt_t format_new_html_printout(wchar_t * title, uint8_t font_sz, uint8_t head_sz, uint8_t typographic_columns);

void result_write_file(FILE * fp_output, result_collection_t * write, fmt_t format);

#endif // RESULT_FMT_H