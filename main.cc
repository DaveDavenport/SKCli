#include <iostream>
#include "stk.hpp"

using namespace std;
using namespace Stuffkeeper;


/**
 * Main function.
 */
int main ( int argc, char **argv )
{
    Stuffkeeper::CLI stk;

    return stk.run(argc, argv);
}
