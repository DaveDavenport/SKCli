
#ifndef __STUFFKEEPER_DATABASE_TAG_H__
#define __STUFFKEEPER_DATABASE_TAG_H__

#include <string>
#include <list>
#include <stdint.h>
#include "stk-colors.hpp"

namespace Stuffkeeper
{
    class Tag
    {
        private:
            // 0 means invalid.
            std::string name = "n/a";
            std::string description = "n/a";
        public:
            std::string &get_name() {
                return name;
            }
            std::string &get_description() {
                return description;
            }


            Tag( std::string name, std::string description ):
                name( name ),
                description( description ) {
            }
            void print() {
                int length = 14;
                unsigned long length2 = name.length();

                if ( description.length() > length2 )
                    length2 = description.length();


                table_header_field_print( "%-*s", length, "Key" );
                table_header_field_print( "%-*s", length2, "Value" );
                table_row_new();

                table_field_print ( "%-*s", length, "Name:" );
                table_field_print ( "%-*s", length2, name.c_str() );
                table_row_new();
                table_field_print ( "%-*s", length, "Description:" );
                table_field_print ( "%-*s", length2, description.c_str() );
                table_row_new();
            }

    };

}

#endif // __STUFFKEEPER_DATABASE_TAG_H__
