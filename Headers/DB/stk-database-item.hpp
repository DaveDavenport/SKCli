

#ifndef __STUFFKEEPER_DATABASE_ITEM_H__
#define __STUFFKEEPER_DATABASE_ITEM_H__

#include <string>
#include <list>
#include <stdint.h>

namespace stuffkeeper
{
    class Item
    {
        private:
            // 0 means invalid.
            uint32_t    uid = 0;
        public:
            uint32_t get_uid() {
                return uid;
            }

    };
}

#endif // __STUFFKEEPER_DATABASE_ITEM_H__
