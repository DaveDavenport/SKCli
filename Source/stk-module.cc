#include "stk-module.hpp"
#include "stk-colors.hpp"

using namespace std;
using namespace Stuffkeeper;


void Module::print_id( const string name )
{
    fprintf( stdout, "%s[%s::%s]%s\n",
             color_blue,
             this->get_name().c_str(),
             name.c_str(),
             color_reset );
}
