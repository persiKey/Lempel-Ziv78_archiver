#pragma once
#include "IArchive.h"
#include "Info.h"

using std::list;

class ArchiveLZ78 : public IArchive
{
private:
	list<to_write> analized;
	vector<bvector> data;

private:
	void GetListToWrite(const string& target_filename);
	int32_t WriteListData(ofstream& out_file);
	void GetUnarchivedData(ifstream& in_file, size_t size);
	void WriteRawData(const string& out_filename);

public:
	int32_t Archive(ofstream& out_file, const string& target_filename);
	void Unarchive(ifstream& in_file, size_t size, const string& out_filename);
};

