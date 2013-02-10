#ifndef __STK_ADD_HPP__
#define __STK_ADD_HPP__

#include "stk-module.hpp"

namespace Stuffkeeper
{
	class CLI;

	class Add : public Module
	{
		public:
			Add(CLI *cli):
				Module(cli, "add")
			{

			}

		virtual int run ( int argc, char **argv );
	};
}

#endif
