#pragma once
#include <vector>

namespace day5 {
	static const int diagram_size = 1000;

	struct line {
		int sx, sy, ex, ey;
	};

	void task1();
	void task2();

	void ReadInput(std::vector<line>& lines);
	void DrawLines(int** diagram, std::vector<line>& lines, bool draw_diagonals = false);
	void Print(int** diagram);
	template <typename T> int sign(T val);
}