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

struct INT_INFO
{
	int val;
	size_t null_shift;
	bool operator==(const INT_INFO& cmp)
	{
		return (cmp.val == this->val) && (cmp.null_shift == this->null_shift);
	}
	friend std::ostream& operator<<( std::ostream& out, INT_INFO a)
	{
		for (int i = a.null_shift - 1; i >= 0; --i)
		{
			out << get_nth_bit(a.val, i);
		}
		return out;
	}
};


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
	INT_INFO temp_val; temp_val.val = temp_val.null_shift = 0;
	//set<int> val;
	vector<INT_INFO> vals;

	while (!file.eof())
	{
		if (!file.read((char*)&buffer, sizeof(int8_t)))
		{
			break;
		}
		for (int i = sizeof(int8_t) * 8 - 1; i >= 0; --i)
		{
			if (!((i + 1) % 4)) std::cout << ' ';
			std::cout << get_nth_bit(buffer, i);
		}
		do 
		{// Ya kushayu 
			temp_val.val <<= 1;
			temp_val.val += get_nth_bit(buffer, sizeof(int8_t)*8 - left % (sizeof(int8_t)*8) - 1);
			left++;
			++temp_val.null_shift;
			if ( std::find(vals.begin(), vals.end(), temp_val) == vals.end() )
			{
				vals.push_back(temp_val);
				temp_val.val = temp_val.null_shift = 0;
			}
		}while ((left % (sizeof(int8_t) * 8)));
	}

	if(temp_val.null_shift != 0)
		vals.push_back(temp_val);
	std::cout << '\n';
	for (auto i : vals)
	{
		std::cout << i << ' ';
	}
	std::cout << '\n';

	
	return 0;
}