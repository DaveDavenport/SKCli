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

		virtual int run ( int argc, char **argv );
	};
}

#endif
