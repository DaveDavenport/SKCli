#include <iostream>
#include "stk.hpp"

using namespace std;
using namespace Stuffkeeper;


/**
 * Main function.
 */
int main ( int argc, char **argv )
{
    Stuffkeeper::Database db;

    Stuffkeeper::CLI stk(&db);

    return stk.run(argc, argv);
}
