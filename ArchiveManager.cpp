#include "ArchiveManager.h"
#include <fstream>




void ArchiveManager::Compress(char* out_filename, const vector<string>& filenames, int32_t files_count)
{
	//preambula
	ofstream arch_file(out_filename, std::ios_base::binary);
	arch_file.write((char*)&files_count, sizeof(int32_t));
	for (int i = 0; i < files_count; ++i)
	{
		arch_file.write((char*)&files_count, sizeof(int32_t));
	}
	for (int i = 0; i < files_count; ++i)
	{
		size_t str_size = filenames.size();
		arch_file.write((char*)&str_size, sizeof(size_t));
		for (int k = 0; k < str_size; ++k)
		{
			arch_file.write((char*)&filenames[i][k], sizeof(char));
		}
	}
	/*
	*_count int
	* _size_i int
	* _name_leght_i int
	* name_i char*
	*/



}

void ArchiveManager::Decompress(char* filename)
{
}
