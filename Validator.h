#pragma once

enum ARGS
{
	COMMAND = 1,
	OUT_FILENAME = 2,
	TARGET_FILES_FROM = 3,
	MIN_ARGC = 2,
	MIN_ARGS_COMP = 3
};

class Validator
{
	bool ValidExist(char* file);
	bool ValidName(char* file);
public:
	bool ValidAll(int argc, char** argv);
};

