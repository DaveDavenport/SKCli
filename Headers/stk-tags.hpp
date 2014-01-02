#ifndef __STK_TAGS_HPP__
#define __STK_TAGS_HPP__

#include "stk-module.hpp"

namespace Stuffkeeper
{
	class CLI;

	class Tags: public Module
	{
		public:
			Tags(CLI *cli):
				Module(cli, "tags")
			{

			}

            int run ( int argc, char **argv );
        private:
            int cmd_complete( int argc, char **argv );
            /**
             * Display a list of tags.
             */
            void list ();
	};
}

#endif
