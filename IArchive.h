#pragma once
#include <string>
#include <fstream>

using std::string;
using std::ofstream;
using std::ifstream;

class IArchive
{
	
public:
	virtual ~IArchive();
	virtual int32_t Archive(ofstream& out_file, const string&  target_filename) = 0;
	virtual void Unarchive(ifstream& in_file, size_t size, const string& out_filename) = 0;
};
