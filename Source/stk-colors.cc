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
