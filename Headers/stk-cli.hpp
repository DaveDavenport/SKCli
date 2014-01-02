#ifndef __STK_CLI_H__
#define __STK_CLI_H__

#include <string>
#include "stk.hpp"

namespace Stuffkeeper
{
    class CLI 
    {
        private:
            Database *database;
			const int num_modules = 3;
			// Modules
			Module *modules[3] = {
				new List(this),
				new Add(this),
                new Tags(this)
			};

        public:
            CLI(Database *db):
                database(db)
            {
            }
    
            int run ( int argc, char **argv);

            Database *get_database() { return database;}
    };
}

#endif
