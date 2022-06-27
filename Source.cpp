#include <fstream>
#include <iostream>
#include <bitset>
#include <map>
#include <set>
#include <vector>
#include <list>
#include <algorithm>
#include <string>
#include <math.h>

using std::ofstream;
using std::ifstream;
using std::map;
using std::bitset;
using std::vector;
using std::set;
using std::string;
using std::list;
using std::string;

using std::int8_t;

constexpr int BIT_IN_BYTE = sizeof(int8_t) * 8;

typedef std::pair<int, bool> to_write;
typedef vector<bool> bvector;


inline bool get_nth_bit(int a, size_t n)
{
	return a & (1 << n);
}

inline bool get_nth_bit(int8_t a, size_t n)
{
	return a & (1 << n);
}

int8_t get_bit_range(int8_t a, size_t beg, size_t end)
{
	int8_t res = a;
	size_t range = sizeof(int8_t) * 8 - 1;
	for (size_t i = range; i > range - beg; --i)
		res = res & ~(1 << i);
	
	for(int i = range-end;i >= 0;--i)
		res = res & ~(1 << i);

	return res;
}

inline void write_to_n_bit(int8_t& dest,size_t bit_num, bool bit)
{
	dest |= (bit << bit_num);
	//std::cout << bit << ' ';
}

inline void write_to_n_bit(int& dest, size_t bit_num, bool bit)
{
	dest |= (bit << bit_num);
}

void GetListToWrite(string file_name, list<to_write> & list_write)
{
	ifstream file(file_name, std::ios_base::binary | std::ios_base::in);

	size_t left = 0;
	int8_t buffer;
	bool nth_bit;

	int global_index = 1;
	int prev_index = 0;

	std::pair<string, int> temp_val;
	map<string, int> vals;

	list_write.push_back({ 0,0 });
	while (!file.eof())
	{
		if (!file.read((char*)&buffer, sizeof(int8_t)))
			break;
		//for (int i = sizeof(int8_t) * 8 - 1; i >= 0; --i)
		//{
		//	if (!((i + 1) % 4)) std::cout << ' ';
		//	std::cout << get_nth_bit(buffer, i);
		//}
		do
		{
			nth_bit = get_nth_bit(buffer, sizeof(int8_t) * 8 - left % (sizeof(int8_t) * 8) - 1);
			temp_val.first.push_back(char(nth_bit) + '0');

			++left;
			auto a = vals.find(temp_val.first);
			if (a == vals.end())
			{
				temp_val.second = global_index;
				++global_index;
				vals.insert(temp_val);
				temp_val.second = prev_index;
				list_write.push_back({ prev_index,nth_bit });
				temp_val.first.clear();
				prev_index = 0;
			}
			else
				prev_index = a->second;

		} while ((left % (sizeof(int8_t) * 8)));
	}

	if (!temp_val.first.empty())
	{
		temp_val.second = prev_index;
		list_write.push_back({ prev_index,nth_bit });
	}
	file.close();
}
#include <assert.h>

void WriteArchive(list<to_write>& analized)
{

}

int main(int argc, char** argv)
{

	list<to_write> analized;
	GetListToWrite("test.txt", analized);
	std::cout << '\n';
	//for (auto i : analized)
	//{
	//	std::cout << i.first << '-' << i.second << ' ';
	//}
	std::cout << "\ndickt: " << analized.size() ;
	std::cout << '\n';
	
	ofstream file("test.out", std::ios_base::binary | std::ios_base::out);
	int8_t buffer = 0;
	int op_num = 4;
	int val_num = 2;
	int size = log2(val_num - 1) + 1;

	//index | bit
	//1
	write_to_n_bit(buffer, 0, 0);
	write_to_n_bit(buffer, 1, 0);
	//2
	write_to_n_bit(buffer, 2,(++analized.begin())->first);
	write_to_n_bit(buffer, 3,(++analized.begin())->second);

	
	for (auto i = ++++analized.begin(); i != analized.end(); ++i,++val_num)
	{
		size = log2(val_num - 1) + 1;
		for (int k = 0; k < size; ++k)
		{
			if (!(op_num % (sizeof(int8_t) * 8)))
			{
				file.write((char*)&buffer, sizeof(int8_t));
				//for (int i = sizeof(int8_t) * 8 - 1; i >= 0; --i)
				//{
				//	if (!((i + 1) % 4)) std::cout << ' ';
				//	std::cout << get_nth_bit(buffer, i);
				//}
				buffer = 0;
			}
			write_to_n_bit(buffer, (op_num++) % (sizeof(int8_t)*8), get_nth_bit(i->first, k));
		}
		if (!(op_num % (sizeof(int8_t) * 8)))
		{
			file.write((char*)&buffer, sizeof(int8_t));
			//for (int i = sizeof(int8_t) * 8 - 1; i >= 0; --i)
			//{
			//if (!((i + 1) % 4)) std::cout << ' ';
			//std::cout << get_nth_bit(buffer, i);
			//}
			buffer = 0;
		}
		write_to_n_bit(buffer, (op_num++) % (sizeof(int8_t) * 8), i->second);
	}
	file.write((char*)&buffer, sizeof(int8_t));
	//for (int i = sizeof(int8_t) * 8 - 1; i >= 0; --i)
	//{
	//	if (!((i + 1) % 4)) std::cout << ' ';
	//	std::cout << get_nth_bit(buffer, i);
	//}
	std::cout << '\n';

	file.close();

	vector<bvector> data;
	{
		data.push_back(bvector{ 0 });
		bvector tmp;

		int8_t in_buf = 0, out_buf = 0;
		ifstream In_file("test.out", std::ios_base::binary | std::ios_base::in);

		int op_num = 2;
		int in_pos = 4;
		
		std::cout << '\n';
		In_file.read((char*)&in_buf, sizeof(int8_t));
		//for (int i = sizeof(int8_t) * 8 - 1; i >= 0; --i)
		//{
		//	if (!((i + 1) % 4)) std::cout << ' ';
		//	std::cout << get_nth_bit(in_buf, i);
		//}

		bool bit = get_nth_bit(in_buf, 3);
		tmp.push_back(bit);
		data.push_back(tmp);
		tmp.clear();
		int point = 0;
		while (!In_file.eof())
		{
			size = log2(data.size() - 1) + 1;

			for (int i = 0; i < size; ++i)
			{
				if (!(in_pos % BIT_IN_BYTE))
				{
					if (!In_file.read((char*)&in_buf, sizeof(int8_t)))
						break;
					//for (int i = sizeof(int8_t) * 8 - 1; i >= 0; --i)
					//{
					//	if (!((i + 1) % 4)) std::cout << ' ';
					//	std::cout << get_nth_bit(in_buf, i);
					//}
				}
				write_to_n_bit(point, i , get_nth_bit(in_buf, in_pos++ % BIT_IN_BYTE));
				
			}
			if (point != 0)
			{
				data.push_back(data[point]);
				point = 0;
			}
			else
				data.push_back({});

			if (!(in_pos % BIT_IN_BYTE))
			{
				if (!In_file.read((char*)&in_buf, sizeof(int8_t)))
					break;
				//for (int i = sizeof(int8_t) * 8 - 1; i >= 0; --i)
				//{
				//	if (!((i + 1) % 4)) std::cout << ' ';
				//	std::cout << get_nth_bit(in_buf, i);
				//}
			}

			data.back().push_back(get_nth_bit(in_buf, in_pos++ % BIT_IN_BYTE));
			

		} 
		std::cout << '\n';
		//for (auto l : data)
		//{
		//	for (auto p : l)
		//		std::cout << p;
		//}
		std::cout << '\n';
		In_file.close();
	}

	assert(data.back().size() == 0);
	data.pop_back();
	//writting
	{
		ofstream Out_file("test_out.out", std::ios_base::binary | std::ios_base::out);
		int8_t buffer = 0;
		int out_pos = 0;

		for (int i = 1; i < data.size() - 1; ++i)
		{
			for (auto k : data[i])
			{
				if (!(out_pos % BIT_IN_BYTE) && out_pos)
				{
					Out_file.write((char*)&buffer, sizeof(int8_t));
					buffer = 0;
				}
				write_to_n_bit(buffer, BIT_IN_BYTE - 1 - out_pos++ % BIT_IN_BYTE, k);
			}
			

		}

		for (int k = 0; k < data.back().size() - 1; ++k)
		{
			if (!(out_pos % BIT_IN_BYTE) && out_pos)
			{
				Out_file.write((char*)&buffer, sizeof(int8_t));
				buffer = 0;
			}
			write_to_n_bit(buffer, BIT_IN_BYTE - 1 - out_pos++ % BIT_IN_BYTE, data.back()[k]);
		}
		if (data.back().size() != 1)
		{
			Out_file.write((char*)&buffer, sizeof(int8_t));
		}


		Out_file.close();
	}
	std::cin.get();
	return 0;
}