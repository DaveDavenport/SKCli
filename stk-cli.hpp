#ifndef __STK_CLI_H__
#define __STK_CLI_H__

#include <string>
#include "stk-module.hpp"

namespace Stuffkeeper
{
	// Forward declr.
	class CLI;
	

	class List : public Module
	{
		public:
		List(CLI *cli):
			Module(cli, "list")
		{

		}

		int run (int argc, char **argv);

	};

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
