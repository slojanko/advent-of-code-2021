#pragma once
#include <string>
#include <vector>

namespace day8 {
	void task1();
	void task2();

	bool ComputeMapping (std::string& mapping, int depth);
	bool CheckMapping(std::string& mapping);
	std::string ApplyMapping(std::string string, std::string& mapping);
	int FindSegment(std::string& string);

	static std::vector<std::string> input_patterns {};
	static std::vector<std::string> digit_segments { "abcefg", "cf", "acdeg", "acdfg", "bcdf", "abdfg", "abdefg", "acf", "abcdefg", "abcdfg" };
}