#ifndef __STK_CLI_H__
#define __STK_CLI_H__

namespace Stuffkeeper
{
	// Forward declr.
	class CLI;
	
	class Module
	{
		protected:
			CLI *cli;
		
		Module(CLI *cli):
			cli(cli)
		{

		}


	};

	class List : Module
	{
		public:
		List(CLI *cli):
			Module(cli)
		{

		}

		int run (int argc, char **argv);

	};

    class CLI 
    {
        private:
			// Modules
			List list = List(this);
    
        public:
            int run ( int argc, char **argv);



    };

}

#endif
