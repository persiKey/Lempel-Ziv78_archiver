#pragma once
#include "Validator.h"
#include "ArchiveManager.h"


class CommandInterpreter
{
	Validator validator;
	ArchiveManager& manager;
public:
	CommandInterpreter(ArchiveManager& manager);
	void Execute(int argc, char **argv);
};

