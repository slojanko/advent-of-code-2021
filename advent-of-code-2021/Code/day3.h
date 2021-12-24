#pragma once
#include <vector>
#include <bitset>

namespace day3 {
	static const int bits_count = 12;

	void task1();
	void task2();

	void ReadInput(std::vector<std::bitset<bits_count>>& lines);
}