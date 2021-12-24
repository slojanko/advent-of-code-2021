#include "day11.h" 
#include <stack>
#include <iostream>
#include <fstream>
#include <algorithm>

namespace day11 {
	void task1() {
		std::vector<std::vector<int8_t>> grid;
		ReadInput(grid);
		int highlights = PerformSteps(grid, 100);
		std::cout << highlights << std::endl;
	}

	void task2() {
		std::vector<std::vector<int8_t>> grid;
		ReadInput(grid);

		int step = 0;
		while(true) {
			int highlights = PerformSteps(grid, 1);
			step++;
			if (highlights == width * height) {
				std::cout << step << std::endl;
				break;
			}
		}
	}

	void ReadInput(std::vector<std::vector<int8_t>>& grid) {
		std::ifstream in(".\\Inputs\\day11.txt");

		int digit;
		for(int i = 0; i < height; i++) {
			std::vector<int8_t> row;
			for(int j = 0; j < width; j++) {
				digit = in.get() - '0';
				row.push_back(digit);
			}

			grid.push_back(row);
			in.ignore();
		}
	}

	int PerformSteps(std::vector<std::vector<int8_t>>& grid, int steps) {
		int highlights = 0;
		for (int i = 0; i < steps; i++) {
			std::stack<std::pair<int8_t, int8_t>> need_to_check;

			// Increase all by 1 and potentially put into check stack
			for (int8_t y = 0; y < height; y++) {
				for (int8_t x = 0; x < width; x++) {
					grid[y][x]++;
					if (grid[y][x] > 9) {
						need_to_check.push({ y, x });
						highlights++;
						grid[y][x] = 0;
					}
				}
			}

			while (need_to_check.size() > 0) {
				std::pair<int8_t, int8_t> position = need_to_check.top();
				need_to_check.pop();

				// Increase neighbors if they're valid and potentially put into check stack (inside grid and havent been checked aka stacked yet)
				for (const auto& offset : neighbor_offsets) {
					std::pair<int8_t, int8_t> neighbor{ position.first + offset.first, position.second + offset.second };

					if (neighbor.first < 0 || neighbor.first >= height || neighbor.second < 0 || neighbor.second >= width  
						|| grid[neighbor.first][neighbor.second] == 0) {
						continue;
					}

					grid[neighbor.first][neighbor.second]++;					
					if (grid[neighbor.first][neighbor.second] > 9) {
						need_to_check.push(neighbor);
						highlights++;
						grid[neighbor.first][neighbor.second] = 0;
					}
				}
			}

			// PrintGrid(grid);
		}

		return highlights;
	}

	void PrintGrid(std::vector<std::vector<int8_t>>& grid) {
		for (int8_t y = 0; y < height; y++) {
			for (int8_t x = 0; x < width; x++) {
				std::cout << (int)grid[y][x]; // << ' ';
			}

			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}