#pragma once

enum ARGS
{
	COMMAND = 1,
	MIN_COMMAND = 2,
	OUT_FILENAME = 2,
	TARGET_FILES_FROM = 3,
	MIN_ARGS_DCOMP = 3,
	MIN_ARGS_COMP = 4
};

class Validator
{
private:
	bool ValidExist(char* file);
	bool ValidName(char* file);
public:
	bool ValidCount(int count, int min);
	bool ValidAllC(int argc, char** argv);
	bool ValidAllD(int argc, char** argv);
};

