#include "day6.h"
#include <iostream>
#include <fstream>
#include <vector>

namespace day6 {
	void task1() {
		std::vector<__int64> fishies(9);
		ReadInput(fishies);
		SimulateDays(fishies, 80);

		__int64 fish_count = 0;
		for (int i = 0; i < 9; i++) {
			fish_count += fishies[i];
		}
		std::cout << fish_count << std::endl;
	}

	void task2() {
		std::vector<__int64> fishies(9);
		ReadInput(fishies);
		SimulateDays(fishies, 256);

		__int64 fish_count = 0;
		for (int i = 0; i < 9; i++) {
			fish_count += fishies[i];
		}
		std::cout << fish_count << std::endl;
	}

	void ReadInput(std::vector<__int64>& fishies) {
		std::ifstream in(".\\Inputs\\day6.txt");
		int fish;
		while (in >> fish) {
			fishies[fish]++;
			in.ignore();
		}
	}

	void SimulateDays(std::vector<__int64>& fishies, const int days) {
		for (int i = 0; i < days; i++) {
			__int64 new_fish = fishies[0];
			fishies.erase(fishies.begin());
			fishies.push_back(new_fish);
			fishies[6] += new_fish;
		}
	}
}