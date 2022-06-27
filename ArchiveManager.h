#pragma once
#include "IArchive.h"
#include <vector>

using std::string;
using std::vector;

using std::int32_t;

class ArchiveManager
{
private:
	IArchive* Archive;

private:
	void WritePreambula(std::ofstream& file, const vector<string>& filenames, int32_t& files_count);
	void ReadPreambula(std::ifstream& file, vector<int32_t>& offsets, vector<string>& filenames, int32_t& files_count);

public:
	ArchiveManager();
	~ArchiveManager();
	void Compress(char* out_filename, const vector<string> &filenames, int32_t files_count);
	void Decompress(char* filename);
};

