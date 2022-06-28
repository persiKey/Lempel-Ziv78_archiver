#pragma once

enum ARGS
{
	COMMAND = 1,
	OUT_FILENAME = 2,
	TARGET_FILES_FROM = 3,
	MIN_ARGS_DCOMP = 3,
	MIN_ARGS_COMP = 4
};

class Validator
{
	bool ValidExist(char* file);
	bool ValidName(char* file);
	bool ValidCount(int count, int min);
public:
	bool ValidAllC(int argc, char** argv);
	bool ValidAllD(int argc, char** argv);
};

