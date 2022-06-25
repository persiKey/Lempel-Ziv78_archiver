#include <fstream>
#include <iostream>
#include <bitset>
#include <map>
#include <set>
#include <vector>
#include <algorithm>


using std::ofstream;
using std::ifstream;
using std::map;
using std::bitset;
using std::vector;
using std::set;

using std::int8_t;


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



int main(int argc, char** argv)
{
	//short a;
	//int beg;
	//int end;
	//int8_t l;
	//while (true)
	//{
	//	std::cin >> a >> beg >> end;
	//
	//	l = get_bit_range((char)a, beg, end);
	//	for (int i = sizeof(int8_t)*8-1; i >= 0; --i)
	//	{
	//		if (!((i+1) % 4)) std::cout << ' ';
	//		std::cout << get_nth_bit(l, i);
	//	}
	//	printf("\n");
	//	for (int i = sizeof(int8_t) * 8 - 1; i >= 0; --i)
	//	{
	//		if (!((i + 1) % 4)) std::cout << ' ';
	//		std::cout << get_nth_bit(a, i);
	//	}
	//	printf("\n");
	//}

	ifstream file("test.txt",std::ios_base::binary | std::ios_base::in);

	size_t left = 0, right = 0;

	//vector<int8_t> bytes;
	int8_t buffer;
	int temp_val = 0;
	//set<int> val;
	vector<int> val;

	while (!file.eof())
	{
		if (!file.read((char*)&buffer, sizeof(int8_t)))
		{
			break;
		}
		do 
		{
			temp_val <<= 1;
			temp_val += get_nth_bit(buffer, left % sizeof(int8_t));
			left++;
			if ( std::find(val.begin(), val.end(), temp_val) == val.end() )
			{
				val.push_back(temp_val);
				temp_val = 0;
			}
		}while ((left % (sizeof(int8_t) * 8)));
	}
	for (auto i : val)
	{
		std::cout << i << ' ';
	}
	std::cout << '\n';

	
	return 0;
}