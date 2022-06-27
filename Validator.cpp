#include "Validator.h"
#include <Windows.h>
#include <iostream>

static const char* FORBIDEN_CHARS = "<>:\"/\\|?*";



bool Validator::ValidExist(char* file)
{
	WIN32_FIND_DATAA findData;
	HANDLE findFile = FindFirstFileA(file, &findData);
	if (findFile == INVALID_HANDLE_VALUE)
	{
		if (GetLastError() == ERROR_FILE_NOT_FOUND)
			std::cerr << L"File \"" << file <<"\" not found!\n";
		else
			std::cerr << L"Something went wrong!\n";

		return false;
	}
	return true;
}

bool Validator::ValidName(char* file)
{
	int i = 0;
	while (file[i] != '\0')
	{
		for (int k = 0; k < strlen(FORBIDEN_CHARS); k++)
			if (file[i] == FORBIDEN_CHARS[k])
			{
				std::cerr << "Forbiden char \'" << file[i] << "\' in \"" << file << "\"\n";
				return false;
			}
	}
	return true;
}

bool Validator::ValidAll(int argc, char** argv)
{
	if (argc < ARGS::MIN_ARGC)
	{
		std::cerr << "Not enough arguments!\n"; return false;
	}
	
	if (!ValidName(argv[ARGS::OUT_FILENAME])) return false;

	for (int i = ARGS::TARGET_FILES_FROM; i < argc;++i)
	{
		if (!ValidExist(argv[i]))
			return false;
	}
	return true;
}