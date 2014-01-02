#ifndef __STK_TAGS_HPP__
#define __STK_TAGS_HPP__

#include "stk-module.hpp"

namespace Stuffkeeper
{
    class CLI;

    class Tags: public Module
    {
        public:
            Tags( CLI *cli ):
                Module( cli, "tags" ) {

            }

            int run ( int argc, char **argv );
        private:
            /**
             * @param argc number of arguments.
             * @param argv list of arguments passed to <cmd> --complete tags
             *
             * Auto complete handler.
             *
             * @returns 0 if success.
             */
            int cmd_complete( int argc, char **argv );

            /**
             * Display a list of tags.
             *
             * @returns 0 if success.
             */
            int list ();

            /**
             * @param argc number of arguments.
             * @param argv list of arguments passed to <cmd> --complete tags
             *
             * add
             *
             * @returns 0 if success.
             */
            int add( int argc, char **argv );
    };
}

#endif
