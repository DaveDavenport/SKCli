#include <iostream>
#include "stk-add.hpp"

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

			return 0;
		}

	}
	return 0;
}
