#pragma once
#include "IArchive.h"
#include <vector>

using std::string;
using std::vector;

using std::int32_t;

class ArchiveManager
{
	IArchive* Archive;
	/*
	зчитує прембулу
	записує прембулу
	контролює Архів
	*/
public:
	ArchiveManager();
	void Compress(char* out_filename, const vector<string> &filenames, int32_t files_count);
	void Decompress(char* filename);
};

