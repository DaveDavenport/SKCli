#ifndef __STUFFKEEPER_DATABASE_TYPE_H__
#define __STUFFKEEPER_DATABASE_TYPE_H__

#include <string>
#include <list>
#include <stdint.h>

namespace Stuffkeeper
{
    class Type
    {
        private:
            // 0 means invalid.
            uint32_t    uid = 0;
            std::string name = "n/a";

        public:
            std::string &get_name() {
                return name;
            }
            uint32_t get_uid() {
                return uid;
            }
            // Constructor
            Type( uint32_t uid ):
                uid( uid ) {

            }
    };
}

#endif // __STUFFKEEPER_DATABASE_TYPE_H__
