#include "day17.h"
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

namespace day17 {
	void TrickShot::SetTarget(int min_x, int max_x, int min_y, int max_y) {
		this->min_x = min_x;
		this->max_x = max_x;
		this->min_y = -min_y;
		this->max_y = -max_y;
	}

	void TrickShot::ComputeValidShots() {
		for (int x = 0; x < max_x; x++) {
			for (int y = 0; y < max_y; y++) {
				// (e - s + 1) * (s + e) / 2 = m
				// e = end velocity
				// s = start velocity
				// m = max allowed position
				// Solve for e
				// Find max y velocity before it goes past target
				std::pair<double, double> solutions = SolveQuadratic(1, 1, y - y * y - 2 * max_y);
				int positive_solution = std::max(solutions.first, solutions.second);

				// No positive solution
				if (positive_solution == -1) {
					continue;
				}

				// Steps taken to return back to y=0 + steps taken after
				int steps = (2 * y + 1) + (positive_solution - y + 1);
				
				// Sum is both range inclusive, so for 1 step only return x
				int final_x = GetSumOfNumberRange(std::max(0, x - steps - 1), x);
				int final_y = GetSumOfNumberRange(y, positive_solution);

				bool touches_on_x = final_x >= min_x && final_x <= max_x;
				bool touches_on_y = GetSumOfNumberRange(y, positive_solution) >= min_y;

				if (touches_on_x && touches_on_y) {
					valid_shots.push_back({ x, y });
				}
			}
		}
	}

	int TrickShot::GetHighestPointOfValidShots() {
		int max_y_velocity = INT_MIN;
		for (const auto& shot : valid_shots) {
			if (shot.second > max_y_velocity) {
				max_y_velocity = shot.second;
			}
		}

		return GetSumOfNumberRange(0, max_y_velocity);
	}

	std::pair<double, double> TrickShot::SolveQuadratic(int a, int b, int c) {
		double x1, x2;
		double det = b * b - 4 * a * c;
		if (det < 0) {
			return { -1.0, -1.0 };
		}

		double det_sqrt = sqrt(det);
		x1 = (-b + det_sqrt) / (2 * a);
		x2 = (-b - det_sqrt) / (2 * a);

		return { x1, x2 };
	}

	// https://stackoverflow.com/questions/30386084/sum-all-numbers-between-two-integers/30386168
	int TrickShot::GetSumOfNumberRange(int start, int end) {
		int n = end - start + 1;
		return (n * (start + end)) / 2;
	}

	void task1() {
		TrickShot trickshot;
		ReadInput(trickshot);
		trickshot.ComputeValidShots();
		std::cout << trickshot.GetHighestPointOfValidShots() << std::endl;
	}

	void task2() {

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