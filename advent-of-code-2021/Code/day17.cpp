#include "day17.h"
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

namespace day17 {
	void TrickShot::SetTarget(int min_x, int max_x, int min_y, int max_y) {
		this->min_x = min_x;
		this->max_x = max_x;
		this->min_y = min_y;
		this->max_y = max_y;
	}

	void TrickShot::ComputeValidShots() {
		for (int x = 0; x <= max_x; x++) {
			for (int y = max_y; y <= -max_y; y++) {
				if (IsShotValid(x, y)) {
					valid_shots.push_back({ x, y });
				}
			}
		}
	}

	bool TrickShot::IsShotValid(int vel_x, int vel_y) {
		int pos_x = 0, pos_y = 0;
		while (pos_y >= max_y) {
			pos_x += vel_x;
			pos_y += vel_y;
			if (vel_x > 0) {
				vel_x--;
			}
			vel_y--;

			if (pos_x >= min_x && pos_x <= max_x) {
				if (pos_y <= min_y && pos_y >= max_y) {
					return true;
				}
			}
		}

		return false;
	}

	int TrickShot::GetHighestPointOfValidShots() {
		int max_y_velocity = INT_MIN;
		for (const auto& shot : valid_shots) {
			if (shot.second > max_y_velocity) {
				max_y_velocity = shot.second;
			}
		}

		return max_y_velocity * (max_y_velocity + 1) / 2;
	}
	
	int TrickShot::GetNumberOfValidShots() {
		return valid_shots.size();
	}

	void task1() {
		TrickShot trickshot;
		ReadInput(trickshot);
		trickshot.ComputeValidShots();
		std::cout << trickshot.GetHighestPointOfValidShots() << std::endl;
	}

	void task2() {
		TrickShot trickshot;
		ReadInput(trickshot);
		trickshot.ComputeValidShots();
		std::cout << trickshot.GetNumberOfValidShots() << std::endl;
	}

	void ReadInput(TrickShot& trickshot) {
		std::ifstream in(".\\Inputs\\day17.txt");
		int min_x, max_x, min_y, max_y;

		in.ignore(32, '=');
		in >> min_x;
		in.ignore(2);
		in >> max_x;

		in.ignore(32, '=');
		in >> max_y;
		in.ignore(2);
		in >> min_y;

		trickshot.SetTarget(min_x, max_x, min_y, max_y);
	}
}