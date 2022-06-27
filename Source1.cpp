#include "CommandInterpreter.h"

int main(int argc, char** argv)
{
	
	ArchiveManager manager;
	CommandInterpreter CMND(manager);
	CMND.Execute(argc, argv);

	return 0;
}