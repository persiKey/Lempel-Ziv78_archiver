#include "ArchiveManager.h"
#include <fstream>
#include "ArchiveLZ78.h"
#include <iostream>

ArchiveManager::ArchiveManager()
{
	Archive = new ArchiveLZ78;
}

ArchiveManager::~ArchiveManager()
{
	delete Archive;
}

void ArchiveManager::WritePreambula(std::ofstream& file, const vector<string>& filenames, int32_t& files_count)
{
	file.write((char*)&files_count, sizeof(int32_t));
	for (int i = 0; i < files_count; ++i)
		file.write((char*)&files_count, sizeof(int32_t));

	for (int i = 0; i < files_count; ++i)
	{
		size_t str_size = filenames[i].size();
		file.write((char*)&str_size, sizeof(size_t));
		for (int k = 0; k < str_size; ++k)
			file.write((char*)&filenames[i][k], sizeof(char));
	}
	/*
	*_count int
	* _size_i int
	* _name_leght_i int
	* name_i char*
	*/
}

void ArchiveManager::ReadPreambula(std::ifstream& file, vector<int32_t>& offsets, vector<string>& filenames, int32_t& file_count)
{

	file.read((char*)&file_count, sizeof(int32_t));

	for (int i = 0; i < file_count; ++i)
	{
		offsets.push_back({});
		file.read((char*)&offsets[i], sizeof(int32_t));
	}

	for (int i = 0; i < file_count; ++i)
	{
		filenames.push_back({});
		size_t str_size;
		file.read((char*)&str_size, sizeof(size_t));
		for (int k = 0; k < str_size; ++k)
		{
			char ch;
			file.read((char*)&ch, sizeof(char));
			filenames.back().push_back(ch);
		}
	}
}


void ArchiveManager::Compress(char* out_filename, const vector<string>& filenames, int32_t files_count)
{
	ofstream arch_file(out_filename, std::ios_base::binary);

	WritePreambula(arch_file, filenames, files_count);

	for (int i = 0; i < files_count; ++i)
	{
		std::cout << "Archiving " << filenames[i] << "...";
		int32_t offset = Archive->Archive(arch_file, filenames[i]);
		auto save_pos = arch_file.tellp();
		arch_file.seekp(((long long(i) + 1) * sizeof(int32_t)));
		arch_file.write((char*)&offset, sizeof(int32_t));
		arch_file.seekp(save_pos);
		std::cout << "Done\n";
	}
	arch_file.close();
}

void ArchiveManager::Decompress(char* filename)
{
	ifstream arch_file(filename, std::ios_base::binary);
	
	int32_t file_count;
	vector<int32_t> offsets;
	vector<string> filenames;

	ReadPreambula(arch_file, offsets, filenames, file_count);

	for (int i = 0; i < file_count; ++i)
	{
		std::cout << "Unarchiving " << filenames[i] << "...";
		Archive->Unarchive(arch_file, offsets[i], filenames[i]);
		std::cout << "Done\n";
	}

	arch_file.close();
}
