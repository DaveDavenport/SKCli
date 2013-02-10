#ifndef __STUFFKEEPER_DATABASE_H__
#define __STUFFKEEPER_DATABASE_H__

#include <string>
#include <list>
#include <stdint.h>

namespace Stuffkeeper
{
	class Type
	{
		private:
			// 0 means invalid.
			uint32_t	uid = 0; 
			std::string	name = "n/a";

		public:
			std::string &get_name() {return name;}

	};
	class Tag
	{
		private:
			// 0 means invalid.
			uint32_t	uid = 0; 
			std::string	name = "n/a";
		public:
			std::string &get_name() {return name;}

	};

	class Item 
	{
		private:
			// 0 means invalid.
			uint32_t	uid = 0; 
		public:

	};

	class Database
	{

		public:
		/**
		 * Get a list of the available types in the 
		 * database.
		 * 
		 * @returns a std::list with Type objects.
		 */
		std::list<Type&> &get_types();

		/**
		 * Get a list of the available tags in the 
		 * database.
		 * 
		 * @returns a std::list with Tag objects.
		 */
		std::list<Tag&> &get_tags();


	};
}

#endif
