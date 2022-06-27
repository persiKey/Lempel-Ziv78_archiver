#include "CommandInterpreter.h"
#include <exception>

int main(int argc, char** argv)
{
	try
	{
		ArchiveManager manager;
		CommandInterpreter CMND(manager);
		CMND.Execute(argc, argv);
	}
	catch (std::exception &e)
	{
		printf("%s", e.what());
	}

	return 0;
}