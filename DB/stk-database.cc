#include <iostream>
#include <DB/stk-database.hpp>

using namespace std;
using namespace Stuffkeeper;


/**
 * Create database
 */
Database::Database()
{



}




list<Type*> Database::get_types()
{
    list<Type*> types;
    
    Type *t = new Type(0);

    types.push_back(t);

    return types;
}

list<Tag> Database::get_tags()
{
    list<Tag> tags;
    return tags;
}
