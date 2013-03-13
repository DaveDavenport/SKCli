#include <iostream>
#include <list>
#include "stk.hpp"

using namespace Stuffkeeper;
using namespace std;


int Stuffkeeper::Add::run ( int argc, char **argv )
{
	if(argc > 0) {
		string command = argv[0];
		cout << "Add: " << command << endl;

		// completed.
		if(command == "--complete") {
			// Print out types.
            std::list<Type*> types = this->cli->get_database()->get_types();
            for(auto iter = types.begin(); iter != types.end(); iter++)
            {
                Type *type = *iter;
                cout << type->get_name() << endl;
            }

			return 0;
		}

	}
	return 0;
}
