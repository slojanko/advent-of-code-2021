#pragma once
#include <vector>

namespace day17 {
	// Only works if target area is down right of start
	class TrickShot {
	public:
		void SetTarget(int min_x, int max_x, int min_y, int max_y);
		void ComputeValidShots();
		bool IsShotValid(int vel_x, int vel_y);
		int GetHighestPointOfValidShots();
		int GetNumberOfValidShots();

	private:
		int min_x, max_x, min_y, max_y;
		std::vector<std::pair<int, int>> valid_shots;
	};

	void task1();
	void task2();

	void ReadInput(TrickShot& trickshot);
}