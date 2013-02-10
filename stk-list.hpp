#ifndef __STK_LIST_HPP__
#define __STK_LIST_HPP__

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
}
#endif
