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

    if ( command == "show"  && argc == 1) {
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
    printf( "%s[%s::%s]%s\n",
            color_blue,
            this->get_name().c_str(),
            "list",
            color_reset );
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

    // Print header
    printf( "%s%-*s%s %s%-*s%s %s%-*s%s\n",
            color_underline_bold,
            name_length, "Name",
            color_reset,
            color_underline_bold,
            date_length, "Creation time",
            color_reset,
            color_underline_bold,
            date_length, "Modification time",
            color_reset
          );
    int alternate = 0;

    for ( auto tag : tags ) {
        char buffer[64];
        time_t t;

        if ( ( alternate%2 ) == 1 ) printf( color_grey_bg );

        printf( "%-*s ", name_length, tag.get_name().c_str() );
        t = tag.get_ctime();
        strftime( buffer, 64, "%x", localtime( &t ) );
        printf( "%-*s ", date_length,buffer );
        t = tag.get_mtime();
        strftime( buffer, 64, "%x", localtime( &t ) );
        printf( "%-*s", date_length, buffer );

        if ( ( alternate%2 ) == 1 ) printf( color_reset );

        putchar( '\n' );
        alternate++;
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

        } else if ( command == "rename" ) {

        }

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
        fprintf( stderr, "%s%s%s\n",
                 color_red_bold,
                 "The new tag requires a name",
                 color_reset );
        return 1;
    }

    string name = argv[0];

    Tag *t = this->cli->get_database()->tag_add( name );

    if ( t == nullptr  ) {
        fprintf( stderr, "%s%s%s: %s\n",
                 color_red_bold,
                 "Failed to add tag",
                 color_reset,
                 name.c_str() );
        return 1;
    }

    t->print();
    delete t;
    return 0;
}
