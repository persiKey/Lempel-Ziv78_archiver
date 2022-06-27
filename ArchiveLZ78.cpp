#include "ArchiveLZ78.h"
#include <map>
#include <assert.h>

using std::map;

void ArchiveLZ78::GetListToWrite(const string& target_filename)
{
	ifstream file(target_filename, std::ios_base::binary | std::ios_base::in);

	size_t left = 0;
	uint8_t buffer;
	bool nth_bit;

	int global_index = 1;
	int prev_index = 0;

	std::pair<string, uint32_t> temp_val;
	map<string, uint32_t> vals;

	analized.push_back({ 0,0 });
	while (!file.eof())
	{
		if (!file.read((char*)&buffer, sizeof(uint8_t)))
			break;

		do
		{
			nth_bit = get_nth_bit(buffer, BITS_IN_BYTE - left % BITS_IN_BYTE - 1);
			temp_val.first.push_back(char(nth_bit) + '0');

			++left;
			auto a = vals.find(temp_val.first);
			if (a == vals.end())
			{
				temp_val.second = global_index;
				++global_index;
				vals.insert(temp_val);
				temp_val.second = prev_index;
				analized.push_back({ prev_index,nth_bit });
				temp_val.first.clear();
				prev_index = 0;
			}
			else
				prev_index = a->second;

		} while ((left % BITS_IN_BYTE));
	}

	if (!temp_val.first.empty())
	{
		temp_val.second = prev_index;
		analized.push_back({ prev_index,nth_bit });
	}
	file.close();
}

int32_t ArchiveLZ78::WriteListData(ofstream& out_file)
{
	auto start_pos = out_file.tellp();

	uint8_t buffer = 0;
	int op_num = 4;
	int val_num = 2;
	int size = log2(val_num - 1) + 1;

	//index | bit
	//1
	write_to_n_bit(buffer, 0, 0);
	write_to_n_bit(buffer, 1, 0);
	//2
	write_to_n_bit(buffer, 2, (++analized.begin())->first);
	write_to_n_bit(buffer, 3, (++analized.begin())->second);

	for (auto i = ++++analized.begin(); i != analized.end(); ++i, ++val_num)
	{
		size = log2(val_num - 1) + 1;
		for (int k = 0; k < size; ++k)
		{
			if (!(op_num % BITS_IN_BYTE))
			{
				out_file.write((char*)&buffer, sizeof(uint8_t));
				buffer = 0;
			}
			write_to_n_bit(buffer, (op_num++) % BITS_IN_BYTE, get_nth_bit(i->first, k));
		}
		if (!(op_num % BITS_IN_BYTE))
		{
			out_file.write((char*)&buffer, sizeof(uint8_t));
			buffer = 0;
		}
		write_to_n_bit(buffer, (op_num++) % BITS_IN_BYTE, i->second);
	}
	out_file.write((char*)&buffer, sizeof(uint8_t));

	return (out_file.tellp() - start_pos);
}

void ArchiveLZ78::GetUnarchivedData(ifstream& in_file, size_t offset)
{
	auto end_pos = offset + in_file.tellg();

	data.push_back(bvector{ 0 });

	uint8_t in_buf = 0;

	int op_num = 2;
	uint32_t in_pos = 4;

	in_file.read((char*)&in_buf, sizeof(int8_t));

	int size;

	data.push_back({ get_nth_bit(in_buf, 3) });

	uint32_t point = 0;

	while (in_file.tellg() <= end_pos)
	{
		int a = in_file.tellg();

		size = log2(data.size() - 1) + 1;

		for (int i = 0; i < size; ++i)
		{
			if (!(in_pos % BITS_IN_BYTE))
			{
				if (in_file.tellg() == end_pos) break;
				if (!in_file.read((char*)&in_buf, sizeof(int8_t)))
					break;
			}
			write_to_n_bit(point, i, get_nth_bit(in_buf, in_pos++ % BITS_IN_BYTE));

		}
		if (point != 0)
		{
			data.push_back(data[point]);
			point = 0;
		}
		else
			data.push_back({});

		if (!(in_pos % BITS_IN_BYTE))
		{
			if (in_file.tellg() == end_pos) break;
			if (!in_file.read((char*)&in_buf, sizeof(int8_t)))
				break;
		}

		data.back().push_back(get_nth_bit(in_buf, in_pos++ % BITS_IN_BYTE));
	}

}

void ArchiveLZ78::WriteRawData(const string& out_filename)
{

	assert(data.back().size() == 0);
	data.pop_back();
	{
		ofstream Out_file(out_filename, std::ios_base::binary | std::ios_base::out);
		uint8_t buffer = 0;
		int out_pos = 0;

		for (int i = 1; i < data.size() - 1; ++i)
		{
			for (auto k : data[i])
			{
				if (!(out_pos % BITS_IN_BYTE) && out_pos)
				{
					Out_file.write((char*)&buffer, sizeof(uint8_t));
					buffer = 0;
				}
				write_to_n_bit(buffer, BITS_IN_BYTE - 1 - out_pos++ % BITS_IN_BYTE, k);
			}

		}

		for (int k = 0; k < data.back().size() - 0; ++k)
		{
			if (!(out_pos % BITS_IN_BYTE) && out_pos)
			{
				Out_file.write((char*)&buffer, sizeof(uint8_t));
				buffer = 0;
			}
			write_to_n_bit(buffer, BITS_IN_BYTE - 1 - out_pos++ % BITS_IN_BYTE, data.back()[k]);
		}
		if (!(out_pos % BITS_IN_BYTE))
		{
			Out_file.write((char*)&buffer, sizeof(uint8_t));
		}

		Out_file.close();
	}
}

int32_t ArchiveLZ78::Archive(ofstream& out_file, const string& target_filename)
{

	GetListToWrite(target_filename);
	int32_t offset = WriteListData(out_file);
	analized.clear();
	return offset;
}

void ArchiveLZ78::Unarchive(ifstream& in_file, size_t size, const string& out_filename)
{
	GetUnarchivedData(in_file, size);
	WriteRawData(out_filename);
	data.clear();
}
