#include <stdio.h>
#include "stdarg.h"
#include "stk-colors.hpp"


void error_printf( const char *format, ... )
{
    va_list arglist;
    char fbuffer[256];

    va_start ( arglist, format );

    snprintf( fbuffer,256,"%s%s%s",
              color_red_bold,
              format,
              color_reset );
    vfprintf( stderr,fbuffer, arglist );

    va_end( arglist );

}
static int row = 0;
static bool new_row = true;
void table_field_print ( const char *format, ... )
{
    va_list arglist;

    va_start ( arglist, format );

    if ( ( row%2 ) == 0  && new_row ) {
        fputs( color_grey_bg,stdout );
        new_row = false;
    }

    vfprintf( stdout, format, arglist );


    fputs( " ", stdout );

    va_end( arglist );
}
void table_header_field_print ( const char *format, ... )
{
    va_list arglist;

    va_start ( arglist, format );

    fputs( color_underline_bold,stdout );
    vfprintf( stdout, format, arglist );
    fputs( " ", stdout );
    fputs( color_reset,stdout );

    va_end( arglist );
}

void table_row_new ()
{
    if ( ( row%2 ) == 0 && !new_row ) {
        fputs( color_reset,stdout );
    }

    putchar( '\n' );
    new_row = true;
    row++;
}
