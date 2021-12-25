#pragma once
#include <vector>

namespace day17 {
	// Only works if target area is down right of start
	class TrickShot {
	public:
		void SetTarget(int min_x, int max_x, int min_y, int max_y);
		void ComputeValidShots();
		int GetSumOfNumberRange(int start, int end);
		int GetHighestPointOfValidShots();
		std::pair<double, double> SolveQuadratic(int a, int b, int c);

	private:
		int min_x, max_x, min_y, max_y;
		std::vector<std::pair<int, int>> valid_shots;
	};

	void task1();
	void task2();

	void ReadInput(TrickShot& trickshot);
}