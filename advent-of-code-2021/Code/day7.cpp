#include "day7.h"
#include <iostream>
#include <fstream>
#include <vector>

namespace day7 {
	void task1() {
		std::ifstream in(".\\Inputs\\day7.txt");
		std::vector<int> crabs;

		int min = INT_MAX, max = INT_MIN;
		for (int i; in >> i;) {
			min = std::min(i, min);
			max = std::max(i, max);
			crabs.push_back(i);
			in.ignore();
		}

		int min_pos = -1;
		int min_cost = INT_MAX;
		for (int i = min; i <= max; i++) {
			int temp_cost = 0;
			for (const auto& crab : crabs) {
				temp_cost += std::abs(crab - i);
			}

			if (temp_cost < min_cost) {
				min_pos = i;
				min_cost = temp_cost;
			}
		}

		std::cout << min_pos << " " << min_cost << std::endl;
	}

	void task2() {
		std::ifstream in(".\\Inputs\\day7.txt");
		std::vector<int> crabs;

		int min = INT_MAX, max = INT_MIN;
		for (int i; in >> i;) {
			min = std::min(i, min);
			max = std::max(i, max);
			crabs.push_back(i);
			in.ignore();
		}

		int min_pos = -1;
		int min_cost = INT_MAX;
		for (int i = min; i <= max; i++) {
			int temp_cost = 0;
			for (const auto& crab : crabs) {
				int dist = std::abs(crab - i) + 1;
				temp_cost += dist * (dist - 1) / 2;
			}

			if (temp_cost < min_cost) {
				min_pos = i;
				min_cost = temp_cost;
			}
		}

		std::cout << min_pos << " " << min_cost << std::endl;
	}
}