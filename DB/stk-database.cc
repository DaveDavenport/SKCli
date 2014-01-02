#include <iostream>
#include <string.h>
#include <DB/stk-database.hpp>

using namespace std;
using namespace Stuffkeeper;

const char* db_name = ".stuffkeeper.sqlite3";
/**
 * Create database
 */
Database::Database()
{
    const char *homedir = getenv( "HOME" );

    if ( homedir == nullptr ) {
        // TODO: error message
        exit( -1 );
    }

    ssize_t path_length = strlen( homedir )+1+strlen( db_name )+1;
    char path[path_length];
    snprintf( path, path_length, "%s/%s", homedir, db_name );

    int retv = sqlite3_open( path, &this->db_handle );

    if ( retv != SQLITE_OK ) {
        fprintf( stderr, "Failed to open database: %s\n", path );
        exit( -1 );
    }

}

Database::~Database()
{
    if ( db_handle != nullptr ) {
        sqlite3_close( db_handle );
        db_handle = nullptr;
    }
}




list<Type*> Database::get_types()
{
    list<Type*> types;

    Type *t = new Type( 0 );

    types.push_back( t );

    return types;
}

list<Tag> Database::get_tags()
{
    list<Tag> tags;
    return tags;
}
