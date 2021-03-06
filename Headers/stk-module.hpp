#ifndef __STK_MODULE_HPP__
#define __STK_MODULE_HPP__
#include <iostream>
#include <string>

/**
 * Declaration of the base class.
 */

namespace Stuffkeeper
{
// Forward declr.
    class CLI;

    class Module
    {
        protected:
            CLI         *cli;
            std::string  name;

            Module( CLI *cli, std::string name ):
                cli( cli ),
                name( name ) {

            }

        public:
            virtual ~Module() {

            }
            /**
             * Get module name.
             */
            std::string &get_name() {
                return name;
            }

            /**
             * Run function.
             */
            virtual int run ( int argc, char **argv ) {
                std::cout << "Module: run not implemented" << std::endl;
                return 0;
            }
            virtual int cmd_complete ( int argc, char **argv ) {
                return 0;
            }

            void print_id( const std::string name );
    };
}

#endif
