
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
            int32_t    uid = 0;
            time_t      ctime = 0;
            time_t      mtime = 0;
            std::string name = "n/a";
        public:
            std::string &get_name() {
                return name;
            }
            time_t get_mtime() const {
                return mtime;
            }
            time_t get_ctime() const {
                return ctime;
            }

            uint32_t get_uid() const {
                return uid;
            }

            Tag( int32_t uid, time_t ctime, time_t mtime, std::string name ):
                uid( uid ),
                ctime( ctime ),
                mtime( mtime ),
                name( name ) {
            }
            void print() {
                char buffer[64];
                int length = 18;


                table_header_field_print( "%-*s", length, "Field" );
                table_header_field_print( "%-*s", length, "Value" );
                table_row_new();
                table_field_print ( "%-*s", length, "Uid:" );
                table_field_print ( "%-*d", length,uid );
                table_row_new();
                strftime( buffer, 64, "%x %X", localtime( &ctime ) );
                table_field_print ( "%-*s", length, "Creation time:" );
                table_field_print ( "%-*s", length,buffer );
                table_row_new();

                strftime( buffer, 64, "%x %X", localtime( &mtime ) );
                table_field_print ( "%-*s", length, "Modification time:" );
                table_field_print ( "%-*s", length,buffer );
                table_row_new();
                table_field_print ( "%-*s", length, "Name:" );
                table_field_print ( "%-*s", length,name.c_str() );
                table_row_new();
            }

    };

}

#endif // __STUFFKEEPER_DATABASE_TAG_H__
