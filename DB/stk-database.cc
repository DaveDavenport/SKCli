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

    this->validate_tables();
    this->prepare_stmts();
}

Database::~Database()
{
    if ( stmt_tag_list != nullptr ) {
        sqlite3_finalize( stmt_tag_list );
        stmt_tag_list = nullptr;
    }

    if ( stmt_tag_add != nullptr ) {
        sqlite3_finalize( stmt_tag_add );
        stmt_tag_add = nullptr;
    }

    if ( stmt_tag_get != nullptr ) {
        sqlite3_finalize( stmt_tag_get );
        stmt_tag_get = nullptr;
    }

    if ( stmt_tag_rename != nullptr ) {
        sqlite3_finalize( stmt_tag_rename );
        stmt_tag_rename = nullptr;
    }

    if ( stmt_tag_remove != nullptr ) {
        sqlite3_finalize( stmt_tag_remove );
        stmt_tag_remove = nullptr;
    }

    if ( db_handle != nullptr ) {
        sqlite3_close( db_handle );
        db_handle = nullptr;
    }
}

void Database::prepare_stmts()
{
    const char * const stmt_tag_list_str = "SELECT * FROM tags";
    int retv = sqlite3_prepare_v2( this->db_handle,
                                   stmt_tag_list_str, -1,
                                   &( this->stmt_tag_list ),nullptr );

    if ( retv != SQLITE_OK ) {
        fprintf( stderr, "Failed to prepare statement: %s:%i\n", stmt_tag_list_str,retv );
    }

    const char * const stmt_tag_add_str = "INSERT INTO tags VALUES(null, ?, ?, ?)";
    retv = sqlite3_prepare_v2( this->db_handle,
                               stmt_tag_add_str, -1,
                               &( this->stmt_tag_add ),nullptr );

    if ( retv != SQLITE_OK ) {
        fprintf( stderr, "Failed to prepare statement: %s:%i\n", stmt_tag_add_str,retv );
    }

    const char * const stmt_tag_get_str = "SELECT * FROM tags WHERE name=?";
    retv = sqlite3_prepare_v2( this->db_handle,
                               stmt_tag_get_str, -1,
                               &( this->stmt_tag_get ), nullptr );

    if ( retv != SQLITE_OK ) {
        fprintf( stderr, "Failed to prepare statement: %s:%i\n", stmt_tag_get_str,retv );
    }

    const char * const stmt_tag_rename_str = "UPDATE OR ABORT tags SET name=?,mtime=? WHERE uid=?";
    retv = sqlite3_prepare_v2( this->db_handle,
                               stmt_tag_rename_str, -1,
                               &( this->stmt_tag_rename ), nullptr );

    if ( retv != SQLITE_OK ) {
        fprintf( stderr, "Failed to prepare statement: %s:%i\n", stmt_tag_rename_str,retv );
    }

    const char * const stmt_tag_remove_str = "DELETE FROM tags WHERE uid=?";
    retv = sqlite3_prepare_v2( this->db_handle,
                               stmt_tag_remove_str, -1,
                               &( this->stmt_tag_remove ), nullptr );

    if ( retv != SQLITE_OK ) {
        fprintf( stderr, "Failed to prepare statement: %s:%i\n", stmt_tag_remove_str,retv );
    }
}

void Database::validate_tables()
{
    char *errmsg = nullptr;
    const char *stmt = "CREATE TABLE IF NOT EXISTS tags ("
                       "uid INTEGER UNIQUE PRIMARY KEY AUTOINCREMENT,"
                       "ctime INTEGER,"
                       "mtime INTEGER,"
                       "name  INTEGER UNIQUE);";
    int retv = sqlite3_exec( this->db_handle, stmt, nullptr, nullptr, &errmsg );

    if ( retv!= SQLITE_OK ) {
        fprintf( stderr, "Failed to create table: %s\n", errmsg );
    }


}



list<Type*> Database::get_types()
{
    list<Type*> types;

    Type *t = new Type( 0 );

    types.push_back( t );

    return types;
}

Tag *Database::tag_get( const std::string tag_name )
{
    sqlite3_bind_text( this->stmt_tag_get, 1,
                       tag_name.c_str(), strlen( tag_name.c_str() ), SQLITE_TRANSIENT );

    int rc = sqlite3_step( this->stmt_tag_get );

    if ( rc == SQLITE_ROW ) {
        string name = reinterpret_cast<const
                      char*>( sqlite3_column_text( this->stmt_tag_get, 3 ) );
        Tag *t = new Tag(
            sqlite3_column_int( this->stmt_tag_get, 0 ),
            sqlite3_column_int64( this->stmt_tag_get, 1 ),
            sqlite3_column_int64( this->stmt_tag_get, 2 ),
            name );

        sqlite3_reset( this->stmt_tag_get );
        return t;
    }

    sqlite3_reset( this->stmt_tag_get );
    return nullptr;
}

list<Tag> Database::get_tags()
{
    list<Tag> tags;
    int rc;

    do {
        rc = sqlite3_step( this->stmt_tag_list );

        switch ( rc )  {
            case SQLITE_DONE:
                break;

            case SQLITE_ROW: {
                string name = reinterpret_cast<const
                              char*>( sqlite3_column_text( this->stmt_tag_list, 3 ) );
                Tag tag(
                    sqlite3_column_int( this->stmt_tag_list, 0 ),
                    sqlite3_column_int64( this->stmt_tag_list, 1 ),
                    sqlite3_column_int64( this->stmt_tag_list, 2 ),
                    name );
                tags.push_back( tag );
            }
            break;

            default:
                fprintf( stderr, "Error iterating table: %s\n",
                         sqlite3_errmsg( this->db_handle ) );
                break;
        }

    } while ( rc == SQLITE_ROW );

    // Reset the query.
    sqlite3_reset( this->stmt_tag_list );
    return tags;
}

Tag *Database::tag_add( const string name )
{
    time_t now = time( nullptr );

    sqlite3_bind_int64( this->stmt_tag_add, 1, now );
    sqlite3_bind_int64( this->stmt_tag_add, 2, now );
    sqlite3_bind_text( this->stmt_tag_add, 3, name.c_str(), strlen( name.c_str() ), SQLITE_TRANSIENT );

    int rc = sqlite3_step( this->stmt_tag_add );

    if ( rc == SQLITE_CONSTRAINT ) {
        return nullptr;
    }

    if ( rc != SQLITE_DONE ) {
        fprintf( stderr, "Error %d: %s\n",rc,
                 sqlite3_errmsg( this->db_handle ) );
        return nullptr;
    }

    uint32_t id = sqlite3_last_insert_rowid( this->db_handle );

    sqlite3_reset( stmt_tag_add );

    return new Tag( id, now, now, name );
}

Tag *Database::tag_rename ( const Tag *old, const std::string new_name )
{
    Tag *new_tag = nullptr;

    time_t now= time( nullptr );
    sqlite3_bind_text( this->stmt_tag_rename, 1,
                       new_name.c_str(), strlen( new_name.c_str() ), SQLITE_TRANSIENT );
    sqlite3_bind_int64( this->stmt_tag_rename, 2, now );
    sqlite3_bind_int( this->stmt_tag_rename, 3, old->get_uid() );

    int rc = sqlite3_step( this->stmt_tag_rename );

    if ( rc == SQLITE_DONE ) {
        new_tag = this->tag_get( new_name );
    } else {
        fprintf( stderr, "Error %d: %s\n",rc,
                 sqlite3_errmsg( this->db_handle ) );
    }

    sqlite3_reset( this->stmt_tag_rename );
    return new_tag;
}


bool Database::tag_remove ( const Tag *old )
{
    sqlite3_bind_int( this->stmt_tag_remove, 1, old->get_uid() );

    int rc = sqlite3_step( this->stmt_tag_remove );

    if ( rc != SQLITE_DONE ) {
        sqlite3_reset( this->stmt_tag_remove );
        return false;
    }

    sqlite3_reset( this->stmt_tag_remove );
    return true;
}
