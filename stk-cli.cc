#include <iostream>
#include "stk-cli.hpp"

using namespace std;
using namespace Stuffkeeper;

int Stuffkeeper::CLI::run( int argc, char ** argv )
{
    if( argc < 2)
    {
        // Default action.
    }
    else
    {
        /* get the command */
        std::string command = argv[1];
       
        /**
         * Auto complete.
         */ 
        if(command == "--complete" )
        {
            for(int j = 0; j < this->num_modules; j++)
            {
                cout << this->modules[j]->get_name() << " " << endl;
            }
            return 0;
        }

        /**
         * Command parser
         */
        for(int j = 0; j < this->num_modules; j++)
        {
            if(this->modules[j]->get_name() == command)
            {
                cout << "Module: "<< this->modules[j]->get_name() << endl;
                return this->modules[j]->run(argc-2,&argv[2]);
            }
        }
    }

    return 0;
}

