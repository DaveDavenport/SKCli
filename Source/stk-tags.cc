#include <iostream>
#include <list>
#include <string.h>
#include <time.h>
#include "stk.hpp"
#include "stk-colors.hpp"

using namespace Stuffkeeper;
using namespace std;

int Tags::cmd_complete( int argc, char **argv )
{
    if ( argc == 0 ) {
        // Print out functions this module supports.
        cout << "list"   << endl;
        cout << "add"    << endl;
        cout << "remove" << endl;
        cout << "rename" << endl;
        cout << "show"   << endl;
        return 0;
    }

    string command = argv[0];

    if ( command == "show"  && argc == 1 ) {
        // Print out tags.
        std::list<Tag> tags = this->cli->get_database()->get_tags();

        for ( auto iter : tags ) {
            Tag &tag = iter;
            cout << tag.get_name() << endl;
        }
    }

    return 0;
}


int Tags::list ( )
{
    this->print_id( "list" );
    putchar( '\n' );

    // List all tags.
    auto tags = this->cli->get_database()->get_tags();

    // Get the length of the date
    unsigned int date_length = strlen( "Modification time" );
    {
        char buffer[64];
        time_t t=0;
        strftime( buffer, 64, "%x", localtime( &t ) );

        if ( strlen( buffer ) > date_length ) date_length = strlen( buffer );
    }

    // Get the max length of the tag names.
    int name_length = 4;

    for ( auto tag : tags ) {
        int l = tag.get_name().length();

        if ( l > name_length ) name_length = l;
    }


    table_header_field_print( "%-*s", name_length,"Name" );
    table_header_field_print( "%-*s", date_length,"Creation Time" );
    table_header_field_print( "%-*s", date_length,"Modification Time" );
    table_row_new();

    for ( auto tag : tags ) {
        char buffer[64];
        time_t t;

        table_field_print( "%-*s", name_length, tag.get_name().c_str() );
        t = tag.get_ctime();
        strftime( buffer, 64, "%x", localtime( &t ) );
        table_field_print( "%-*s", date_length,buffer );
        t = tag.get_mtime();
        strftime( buffer, 64, "%x", localtime( &t ) );
        table_field_print( "%-*s", date_length, buffer );

        table_row_new();
    }

    return 0;
}


int Tags::run ( int argc, char **argv )
{
    if ( argc > 0 ) {
        string command = argv[0];

        // completed.
        if ( command == "--complete" ) {
            return this->cmd_complete( argc-1, &argv[1] );
        } else if ( command == "list" ) {
            return this->list();
        } else if ( command == "add" ) {
            return this->add( argc-1, &argv[1] );
        } else if ( command == "remove" ) {

        } else if ( command == "show" ) {
            return this->show( argc-1, &argv[1] );
        } else if ( command == "rename" ) {

        }

    }

    return 0;
}

int Tags::show( int argc, char **argv )
{
    this->print_id( "show" );
    putchar( '\n' );

    if ( argc == 0 ) {
        error_printf( "stkcli tags show <id>" );
        return 1;
    }

    string name = argv[0];

    for ( int j=1; j < argc; j++ ) {
        name += " "+string( argv[j] );
    }

    // Tag
    Tag *t = this->cli->get_database()->tag_get( name );

    if ( t != nullptr ) {
        t->print();
        delete t;
    } else {
        error_printf( "Tag: '%s' not found", name.c_str() );
    }

    return 0;
}

int Tags::add( int argc, char **argv )
{
    printf( "%s[%s::%s]%s\n",
            color_blue,
            this->get_name().c_str(),
            "add",
            color_reset );
    putchar( '\n' );

    if ( argc == 0 ) {
        error_printf( "The new tag requires a name." );
        return 1;
    }

    // Get tag name
    string name = argv[0];
    for ( int j=1; j < argc; j++ ) {
        name += " "+string( argv[j] );
    }

    // Check tag
    Tag *test = this->cli->get_database()->tag_get( name );
    if(test != nullptr) {
        error_printf("Tag with name: '%s' already exists.", name.c_str());
        delete test;
        return -1;
    }

    // Add tag
    Tag *t = this->cli->get_database()->tag_add( name );

    if ( t == nullptr  ) {
        error_printf( "Failed to add tag: " );
        fprintf( stderr, "%s\n",name.c_str() );
        return 1;
    }

    t->print();
    delete t;
    return 0;
}
