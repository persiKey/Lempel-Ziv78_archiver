#pragma once
#include "Validator.h"
#include "ArchiveManager.h"


class CommandInterpreter
{
private:
	Validator validator;
	ArchiveManager& manager;
public:
	explicit CommandInterpreter(ArchiveManager& manager);
	void Execute(int argc, char **argv);
};

