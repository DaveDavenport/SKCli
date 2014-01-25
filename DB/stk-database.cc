#include <iostream>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <DB/stk-database.hpp>

using namespace std;
using namespace Stuffkeeper;

const char *db_name = "STKCli-DB";

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
    this->db_path = ( char * )malloc( sizeof( char )*path_length );
    snprintf( this->db_path, path_length, "%s/%s", homedir, db_name );


    ssize_t tag_path_length = strlen( "Tags" )+2+path_length;
    this->db_tag_path = ( char * )malloc( sizeof( char )*tag_path_length );
    snprintf( this->db_tag_path, tag_path_length, "%s/%s/", this->db_path, "Tags" );

}

Database::~Database()
{
    if ( this->db_path ) {
        free( this->db_path );
    }

    if ( this->db_tag_path ) {
        free( this->db_tag_path );
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
    ssize_t length = strlen( this->db_tag_path )+3+tag_name.length();
    char path[length];
    snprintf( path, length, "%s/%s", this->db_tag_path, tag_name.c_str() );

    // See if directory exists
    struct stat test;

    if ( stat( path,&test ) == -1 ) {
        return nullptr;
    }

    std::string descr;
    length = strlen( this->db_tag_path )+3+tag_name.length()+strlen( "description" );
    char buffer[length];
    snprintf( buffer, length, "%s/%s/description", this->db_tag_path, tag_name.c_str() );
    FILE *fd = fopen( buffer, "r" );

    if ( fd != nullptr ) {
        char data[1024];
        fgets( data, 1024, fd );
        data[strlen( data )-1] = '\0';
        descr = data;
        fclose( fd );
    }

    return new Tag( tag_name, descr );
}

list<Tag> Database::get_tags()
{
    list<Tag> tags;


    DIR *tag_dir = opendir( this->db_tag_path );;

    if ( tag_dir == nullptr ) {
        fprintf( stderr, "Failed to open path: %s\n", this->db_tag_path );
        return tags;
    }

    struct dirent *dir;

    while ( ( dir = readdir( tag_dir ) ) ) {
        if ( dir->d_type == DT_DIR ) {
            if ( dir->d_name[0] != '.' ) {
                Tag *t = this->tag_get( dir->d_name );
                tags.push_back( *t );
                delete t;
            }
        }
    }

    closedir( tag_dir );
    return tags;
}

Tag *Database::tag_add( const string name )
{
    ssize_t length = strlen( this->db_tag_path )+2+name.length();
    char *path = ( char * )malloc( length*sizeof( char ) );
    snprintf( path, length, "%s/%s", this->db_tag_path, name.c_str() );

    mkdir( path, 0700 );
    free( path );
    return new Tag( name, "" );
}

Tag *Database::tag_rename ( const Tag *old, const std::string new_name )
{
    Tag *new_tag = nullptr;

    return new_tag;
}


bool Database::tag_remove ( Tag *old )
{
    struct dirent *dir;
    ssize_t length = strlen( this->db_tag_path )+2+old->get_name().length();
    char path[length];
    snprintf( path, length, "%s/%s", this->db_tag_path, old->get_name().c_str() );
    DIR *tag_dir = opendir( path );;

    if ( tag_dir == nullptr ) {
        fprintf( stderr, "Failed to open path: %s\n", this->db_tag_path );
        return false;
    }

    while ( ( dir = readdir( tag_dir ) ) ) {
        if ( dir->d_type != DT_DIR ) {
            ssize_t str_length = strlen( this->db_tag_path )+3+
                                 old->get_name().length()+strlen( dir->d_name );
            char str_path[str_length];
            snprintf( str_path, str_length, "%s/%s/%s",
                      this->db_tag_path, old->get_name().c_str(),
                      dir->d_name );
            unlink( str_path );
        }
    }

    closedir( tag_dir );

    rmdir( path );
    return true;
}
