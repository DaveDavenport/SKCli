
#ifndef __STUFFKEEPER_DATABASE_TAG_H__
#define __STUFFKEEPER_DATABASE_TAG_H__

#include <string>
#include <list>
#include <stdint.h>

namespace Stuffkeeper
{
	class Tag
	{
		private:
			// 0 means invalid.
			uint32_t	uid = 0; 
			std::string	name = "n/a";
		public:
			std::string &get_name() {return name;}

	};

}

#endif // __STUFFKEEPER_DATABASE_TAG_H__
