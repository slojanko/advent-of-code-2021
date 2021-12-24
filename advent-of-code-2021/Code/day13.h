#pragma once
#include <vector>
#include <utility>

namespace day13 {
	enum class FoldAlong {
		X = 0,
		Y = 1,
	};

	class Paper {
	public:
		void AddPoint(const std::pair<int, int> point);
		void Fold(const std::pair<FoldAlong, int>& fold);
		int GetPointCount();
		void PrintCode();
		void RemoveDuplicates();

	private:
		std::vector<std::pair<int, int>> points;
	};

	void task1();
	void task2();
	void ReadInput(Paper& paper, std::vector<std::pair<FoldAlong, int>>& folds);
}