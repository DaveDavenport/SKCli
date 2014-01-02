
#ifndef __STUFFKEEPER_DATABASE_TAG_H__
#define __STUFFKEEPER_DATABASE_TAG_H__

#include <string>
#include <list>
#include <stdint.h>

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
            time_t get_mtime() {
                return mtime;
            }
            time_t get_ctime() {
                return ctime;
            }

            uint32_t get_uid() {
                return uid;
            }

            Tag( int32_t uid, time_t ctime, time_t mtime, std::string name ):
                uid( uid ),
                ctime( ctime ),
                mtime( mtime ),
                name( name ) {
            }

    };

}

#endif // __STUFFKEEPER_DATABASE_TAG_H__
