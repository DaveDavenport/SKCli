#ifndef __STK_COLORS_H__
#define __STK_COLORS_H__

const char * const color_reset          = "\033[0m";
const char * const color_underline      = "\033[4m";
const char * const color_underline_bold = "\033[1;4m";
const char * const color_bold           = "\033[1m";
const char * const color_white_bold     = "\033[1;37m";
const char * const color_blue           = "\033[0;34m";
const char * const color_red_bold       = "\033[1;31m";
const char * const color_grey_bg        = "\033[0;37;40m";
const char * const color_grey_bg_bold   = "\033[1;37;40m";


void error_printf( const char *format, ... );

void table_header_field_print( const char *format, ... );
void table_field_print( const char *format, ... );
void table_row_new ();

#endif // __STK_COLORS_H__
