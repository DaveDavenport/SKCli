#include <iostream>
#include "stk-cli.hpp"
#include "stk-colors.hpp"

using namespace std;
using namespace Stuffkeeper;

int Stuffkeeper::CLI::run( int argc, char ** argv )
{
    if ( argc < 2 ) {
        // Default action.
    } else {
        /* get the command */
        std::string command = argv[1];

        /**
         * Auto complete.
         */
        if ( command == "--complete" ) {
            if ( argc > 2 ) {
                command = argv[2];

                for ( int j = 0; j < this->num_modules; j++ ) {
                    if ( this->modules[j]->get_name() == command ) {
                        this->modules[j]->cmd_complete( argc-3, &argv[3] );
                    }
                }

            } else {
                for ( int j = 0; j < this->num_modules; j++ ) {
                    cout << this->modules[j]->get_name() << " " << endl;
                }
            }

            return 0;
        }

        /**
         * Command parser
         */
        for ( int j = 0; j < this->num_modules; j++ ) {
            if ( this->modules[j]->get_name() == command ) {
                return this->modules[j]->run( argc-2,&argv[2] );
            }
        }

        error_printf( "Failed to parse argument." );
    }

    return 0;
}

