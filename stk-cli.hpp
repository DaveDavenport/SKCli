#ifndef __STK_CLI_H__
#define __STK_CLI_H__

#include <string>
#include "stk-module.hpp"
#include "stk-list.hpp"

namespace Stuffkeeper
{
    class CLI 
    {
        private:
			const int num_modules = 1;
			// Modules
			Module modules[1] = {
				List(this)
			};
    
        public:
            int run ( int argc, char **argv);
    };
}

#endif
