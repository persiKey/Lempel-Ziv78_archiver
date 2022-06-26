#include <fstream>
#include <iostream>
#include <bitset>
#include <map>
#include <set>
#include <vector>
#include <list>
#include <algorithm>
#include <string>

using std::ofstream;
using std::ifstream;
using std::map;
using std::bitset;
using std::vector;
using std::set;
using std::string;
using std::list;

using std::int8_t;

typedef vector<bool> b_vector;


struct Node
{
	string bits;
	int index;

};

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
	bool operator<(const INT_INFO& cmp)
	{
		return (cmp.val > this->val) && (cmp.null_shift > this->null_shift);
	}
	friend bool operator<(const INT_INFO& A, const INT_INFO& B)
	{
		return (A.val > B.val) && (A.null_shift > B.null_shift);
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


	//int8_t buffer;
	//INT_INFO temp_val; temp_val.val = temp_val.null_shift = 0;

	//vector<INT_INFO> vals;
	//set<INT_INFO> search_vals;

	//while (!file.eof())
	//{
	//	int a;

	//	if (!file.read((char*)&buffer, sizeof(int8_t)))
	//	{
	//		break;
	//	}
	//	for (int i = sizeof(int8_t) * 8 - 1; i >= 0; --i)
	//	{
	//		if (!((i + 1) % 4)) std::cout << ' ';
	//		std::cout << get_nth_bit(buffer, i);
	//	}
	//	do 
	//	{// Ya kushayu 
	//		temp_val.val <<= 1;
	//		temp_val.val += get_nth_bit(buffer, sizeof(int8_t)*8 - left % (sizeof(int8_t)*8) - 1);
	//		left++;
	//		++temp_val.null_shift;
	//		
	//		if ( search_vals.find(temp_val) == search_vals.end() )
	//		{
	//			search_vals.insert(temp_val);
	//			vals.push_back(temp_val);
	//			temp_val.val = temp_val.null_shift = 0;
	//		}
	//	}while ((left % (sizeof(int8_t) * 8)));
	//}

	//if(temp_val.null_shift != 0)
	//	vals.push_back(temp_val);
	//std::cout << '\n';
	//for (auto i : vals)
	//{
	//	std::cout << i << ' ';
	//}
	//std::cout << '\n';

	int8_t buffer;
	list<std::pair<b_vector, int>> analized;
	
	int global_index = 1;
	int prev_index = 0;
	map<b_vector, int> vals;
	std::pair<b_vector, int> temp_val;

	while (!file.eof())
	{
		if (!file.read((char*)&buffer, sizeof(int8_t)))
		{
			break;
		}
		//for (int i = sizeof(int8_t) * 8 - 1; i >= 0; --i)
		//{
		//	if (!((i + 1) % 4)) std::cout << ' ';
		//	std::cout << get_nth_bit(buffer, i);
		//}
		do
		{
			temp_val.first.push_back(get_nth_bit(buffer, sizeof(int8_t) * 8 - left % (sizeof(int8_t) * 8) - 1));
			
			left++;
			auto a = vals.find(temp_val.first);
			if (a == vals.end())
			{
				temp_val.second = global_index;
				++global_index;
				vals.insert(temp_val);
				temp_val.second = prev_index;
				analized.push_back(temp_val);
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
		analized.push_back(temp_val);
	}
	std::cout << '\n';
	for (auto i : analized)
	{
		for (auto k : i.first)
			std::cout << k;
		std::cout << '-' << i.second << ' ';
	}
	std::cout << '\n';
	return 0;
}