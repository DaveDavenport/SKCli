#ifndef __STK_CLI_H__
#define __STK_CLI_H__

#include <string>
#include "stk-module.hpp"
#include "stk-list.hpp"
#include "stk-add.hpp"

namespace Stuffkeeper
{
    class CLI 
    {
        private:
			const int num_modules = 2;
			// Modules
			Module modules[2] = {
				List(this),
				Add(this)
			};
    
        public:
            int run ( int argc, char **argv);
    };
}

#endif
