#include "CommandInterpreter.h"
#include <iostream>



CommandInterpreter::CommandInterpreter(ArchiveManager& man) : manager(man){}

void CommandInterpreter::Execute(int argc, char** argv)
{
	
	if (!strcmp(argv[ARGS::COMMAND],"--compress"))
	{
		if (!validator.ValidAllC(argc, argv)) return;

		int args = argc - ARGS::TARGET_FILES_FROM;
		vector<string> filenames(args);
		
		for (int i = 0; i < args; ++i)
		{
			filenames[i] = argv[ARGS::TARGET_FILES_FROM + i];
		}
		
		manager.Compress(argv[ARGS::OUT_FILENAME], filenames, args );
	}
	else if (!strcmp(argv[ARGS::COMMAND], "--decompress"))
	{
		if (!validator.ValidAllD(argc, argv)) return;
		manager.Decompress(argv[ARGS::OUT_FILENAME]);
	}
	else
		std::cerr << "Wrong command!\n";
}
