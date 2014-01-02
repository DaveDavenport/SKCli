#ifndef __STUFFKEEPER_DATABASE_H__
#define __STUFFKEEPER_DATABASE_H__

#include <string>
#include <list>
#include <stdint.h>

// Sqlite
#include <sqlite3.h>

#include <DB/stk-database-type.hpp>
#include <DB/stk-database-tag.hpp>
#include <DB/stk-database-item.hpp>

namespace Stuffkeeper
{
    class Database
    {
        private:
            /** Handle to the sqlite database */
            sqlite3 *db_handle = nullptr;
            /** Precompiled stmts */
            sqlite3_stmt *stmt_tag_list = nullptr;

            // check, and if not exists create tables.
            void validate_tables();
            // Prepare precompiled sqlite stmt.
            void prepare_stmts();
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
             * Get a list of the available tags in the
             * database.
             *
             * @returns a std::list with Tag objects.
             */
            std::list<Tag> get_tags();
    };
}

#endif
