#ifndef __STUFFKEEPER_DATABASE_H__
#define __STUFFKEEPER_DATABASE_H__

#include <string>
#include <list>
#include <stdint.h>


#include <DB/stk-database-type.hpp>
#include <DB/stk-database-tag.hpp>
#include <DB/stk-database-item.hpp>

namespace Stuffkeeper
{
    class Database
    {
        private:
            char *db_path = nullptr;
            char *db_tag_path = nullptr;
        public:
            /**
             * Constructor.
             */
            Database();
            /**
             * Deconstructor.
             */
            ~Database();

            /**
             * Get a list of the available types in the
             * database.
             *
             * @returns a std::list with Type objects.
             */
            std::list<Type*> get_types();

            /**
             * Tags
             */
            /**
             * Get a list of the available tags in the
             * database.
             *
             * @returns a std::list with Tag objects.
             */
            std::list<Tag> get_tags();

            /**
             * @param name Name of the new tag
             *
             * Add tag.
             *
             * @returns the new Tag.
             */
            Tag *tag_add( const std::string name );

            Tag *tag_get ( const std::string name );

            Tag *tag_rename ( const Tag *old, const std::string new_name );

            bool tag_remove ( Tag *old );
    };
}

#endif
