#include "day9.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <algorithm>

namespace day9 {
	void task1() {
		std::vector<std::vector<int8_t>> heightmap;
		ReadInput(heightmap);
		std::vector<std::pair<int8_t, int8_t>> low_points = GetLowPoints(heightmap);

		int sum = 0;
		for (const auto& point : low_points) {
			sum += heightmap[point.first][point.second] + 1;
		}

		std::cout << sum << std::endl;
	}

	void task2() {
		std::vector<std::vector<int8_t>> heightmap;
		ReadInput(heightmap);
		std::vector<std::pair<int8_t, int8_t>> low_points = GetLowPoints(heightmap);

		std::vector<int> basin_sizes;
		basin_sizes = ComputeBasinSizes(heightmap, low_points);
		std::sort(basin_sizes.begin(), basin_sizes.end(), [](const auto& lhs, const auto& rhs)
			{
				return lhs > rhs;
		});

		std::cout << (basin_sizes[0] * basin_sizes[1] * basin_sizes[2]) << std::endl;
	}

	void ReadInput(std::vector<std::vector<int8_t>>& heightmap) {
		std::ifstream in(".\\Inputs\\day9.txt");
		int digit;

		while (in.peek() != EOF) {
			std::vector<int8_t> row;

			while (in.peek() != EOF && in.peek() != '\n') {
				digit = in.get() - '0';
				row.push_back(digit);
			}
			if (in.peek() == '\n') {
				in.ignore();
			}

			heightmap.push_back(row);
		}
	}

	std::vector<std::pair<int8_t, int8_t>> GetLowPoints(std::vector<std::vector<int8_t>>& heightmap) {
		std::vector<std::pair<int8_t, int8_t>> low_points;

		for (int y = 0; y < heightmap.size(); y++) {
			for (int x = 0; x < heightmap[y].size(); x++) {
				if (y != 0 && heightmap[y][x] >= heightmap[y - 1][x]) continue;
				if (x != 0 && heightmap[y][x] >= heightmap[y][x - 1]) continue;
				if (y != heightmap.size() - 1 && heightmap[y][x] >= heightmap[y + 1][x]) continue;
				if (x != heightmap[0].size() - 1 && heightmap[y][x] >= heightmap[y][x + 1]) continue;

				low_points.push_back({ y, x });
			}
		}

		return low_points;
	}

	std::vector<int> ComputeBasinSizes(std::vector<std::vector<int8_t>>& heightmap, std::vector<std::pair<int8_t, int8_t>> low_points) {
		std::vector<int> sizes;

		for (const auto& point : low_points) {
			std::vector<std::pair<int8_t, int8_t>> already_checked;
			std::stack<std::pair<int8_t, int8_t>> need_to_check;
			need_to_check.push(point);
			while (need_to_check.size() > 0) {
				const auto& p = need_to_check.top();
				need_to_check.pop();

				if (std::find(already_checked.begin(), already_checked.end(), p) != already_checked.end()) {
					continue;
				}

				already_checked.push_back(p);

				int y = p.first;
				int x = p.second;
				if (y != 0 && heightmap[y - 1][x] < 9 && heightmap[y][x] < heightmap[y - 1][x]) {
					need_to_check.push({ y - 1, x });
				}
				if (x != 0 && heightmap[y][x - 1] < 9 && heightmap[y][x] < heightmap[y][x - 1]) {
					need_to_check.push({ y, x -1 });
				}
				if (y != heightmap.size() - 1 && heightmap[y + 1][x] < 9 && heightmap[y][x] < heightmap[y + 1][x]) {
					need_to_check.push({ y + 1, x });
				}
				if (x != heightmap[0].size() - 1 && heightmap[y][x + 1] < 9 && heightmap[y][x] < heightmap[y][x + 1]) {
					need_to_check.push({ y, x + 1 });
				}
			}

			sizes.push_back(already_checked.size());
		}

		return sizes;
	}
}