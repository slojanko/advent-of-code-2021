#pragma once
#include <vector>

namespace day9 {
	void task1();
	void task2();

	void ReadInput(std::vector<std::vector<int8_t>>& heightmap);
	std::vector<std::pair<int8_t, int8_t>> GetLowPoints(std::vector<std::vector<int8_t>>& heightmap);
	std::vector<int> ComputeBasinSizes(std::vector<std::vector<int8_t>>& heightmap, std::vector<std::pair<int8_t, int8_t>> low_points);
}