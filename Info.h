#pragma once
#include <cstdint>
#include <vector>
#include <list>

using std::uint8_t;
using std::uint32_t;

using std::vector;

constexpr int BITS_IN_BYTE = sizeof(uint8_t) * 8;

typedef std::pair<uint32_t, bool> to_write;
typedef vector<bool> bvector;

template<typename T>
inline void write_to_n_bit(T& dest, size_t bit_num, bool bit)
{
	dest |= (bit << bit_num);
}

template<typename T>
inline bool get_nth_bit(const T& a, size_t n)
{
	return a & (1 << n);
}