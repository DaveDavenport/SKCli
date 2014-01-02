#include <iostream>
#include <list>
#include "stk.hpp"

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

    if ( command == "show" ) {
        // Print out tags.
        std::list<Tag> tags = this->cli->get_database()->get_tags();

        for ( auto iter : tags ) {
            Tag &tag = iter;
            cout << tag.get_name() << endl;
        }
    }

    return 0;
}


void Tags::list ( )
{
    // List all tags.
    cout << "Current tags:" << endl;

    for ( auto tag : this->cli->get_database()->get_tags() ) {
        cout << tag.get_name() << endl;
    }
}


int Tags::run ( int argc, char **argv )
{
    if ( argc > 0 ) {
        string command = argv[0];
        cout << "Tags: " << command << endl;

        // completed.
        if ( command == "--complete" ) {
            return this->cmd_complete( argc-1, &argv[1] );
        } else if ( command == "list" ) {

        } else if ( command == "add" ) {

        } else if ( command == "remove" ) {

        } else if ( command == "show" ) {

        }

    }

    return 0;
}
