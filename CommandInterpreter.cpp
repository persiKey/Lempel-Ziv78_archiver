#include "CommandInterpreter.h"
#include <iostream>



CommandInterpreter::CommandInterpreter(ArchiveManager& man) : manager(man){}

void CommandInterpreter::Execute(int argc, char** argv)
{
	if(!validator.ValidAll(argc, argv)) return;

	if (argv[ARGS::COMMAND] == "--compress")
	{
		int args = argc - ARGS::TARGET_FILES_FROM + 1;
		vector<string> filenames;
		
		for (int i = 0; i < argc-args; ++i)
		{
			filenames[i] = argv[ARGS::TARGET_FILES_FROM + i];
		}

		if(argc < MIN_ARGS_COMP){std::cerr << "Not enough arguments!\n"; return;}
		
		manager.Compress(argv[ARGS::OUT_FILENAME], filenames, args );
	}
	else if (argv[ARGS::COMMAND] == "--decompress")
	{
		manager.Decompress(argv[ARGS::OUT_FILENAME]);
	}
	else
		std::cerr << "Wrong command!\n";
}
