#include <iostream>
#include "stk-cli.hpp"

using namespace std;
using namespace Stuffkeeper;



int main ( int argc, char **argv )
{
    Stuffkeeper::CLI stk;

    return stk.run(argc, argv);
}


int Stuffkeeper::List::run( int argc, char **argv )
{

    return 0;
}

int Stuffkeeper::CLI::run( int argc, char ** argv )
{
    if( argc < 2)
    {
        // Default action.
    }
    else
    {
        std::string command = argv[1];

        /**
         * Command parser
         */
        if(command == "list") 
        {
            cout << "Stuffkeeper::list" << endl;
            list.run(argc-1, argv+1);
        }
        else if (command == "add")
        {
          
        }
    }

    return 0;
}
