#pragma once
#include <vector>

namespace day11 {
	void task1();
	void task2();

	void ReadInput(std::vector<std::vector<int8_t>>& grid);
	int PerformSteps(std::vector<std::vector<int8_t>>& grid, int steps);
	void PrintGrid(std::vector<std::vector<int8_t>>& grid);

	static std::vector<std::pair<int8_t, int8_t>> neighbor_offsets { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };
	static int width = 10;
	static int height = 10;
}