#pragma once
#include <string>
#include <fstream>

using std::string;
using std::ofstream;
using std::ifstream;

class IArchive
{
	
public:
	virtual void Archive(ofstream& out_file, ifstream& target_file) = 0;
	virtual void Unarchive(ifstream& in_file, size_t size, const string& out_filename) = 0;
};
