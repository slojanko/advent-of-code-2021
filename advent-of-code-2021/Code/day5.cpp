#include "day5.h"
#include <iostream>
#include <fstream>

namespace day5 {
	void task1() {
		std::vector<line> lines;
		ReadInput(lines);

		int** diagram = static_cast<int**>(calloc(diagram_size, sizeof(int*)));
		for (int i = 0; i < diagram_size; i++) {
			diagram[i] = static_cast<int*>(calloc(diagram_size, sizeof(int)));
		}

		DrawLines(diagram, lines, false);

		int result = 0;
		for (int i = 0; i < diagram_size; i++) {
			for(int j = 0; j < diagram_size; j++) {
				if (diagram[i][j] > 1) {
					result++;
				}
			}
		}

		for (int i = 0; i < diagram_size; i++) {
			free(diagram[i]);
		}
		free(diagram);
		std::cout << result << std::endl;
	}

	void task2() {
		std::vector<line> lines;
		ReadInput(lines);

		int** diagram = static_cast<int**>(calloc(diagram_size, sizeof(int*)));
		for (int i = 0; i < diagram_size; i++) {
			diagram[i] = static_cast<int*>(calloc(diagram_size, sizeof(int)));
		}

		DrawLines(diagram, lines, true);

		int result = 0;
		for (int i = 0; i < diagram_size; i++) {
			for (int j = 0; j < diagram_size; j++) {
				if (diagram[i][j] > 1) {
					result++;
				}
			}
		}

		for (int i = 0; i < diagram_size; i++) {
			free(diagram[i]);
		}
		free(diagram);
		std::cout << result << std::endl;
	}

	void ReadInput(std::vector<line>& lines) {
		std::ifstream in(".\\Inputs\\day5.txt");

		while (!in.eof()) {
			line l;
			in >> l.sx;
			in.ignore();
			in >> l.sy;
			in.ignore(3);
			in >> l.ex;
			in.ignore();
			in >> l.ey;

			lines.push_back(l);
		}
	}

	void DrawLines(int** diagram, std::vector<line>& lines, bool draw_diagonals) {
		for(const auto& l : lines) {
			int xstep = sign(l.ex - l.sx);
			int ystep = sign(l.ey - l.sy);

			// Vertical
			if (xstep != 0 && ystep == 0) {
				int steps = std::abs(l.sx - l.ex);
				for (int i = 0; i <= steps; i++) {
					diagram[l.sy][l.sx + i * xstep]++;
				}
			}
			// Horizontal
			else if (ystep != 0 && xstep == 0) {
				int steps = std::abs(l.sy - l.ey);
				for (int i = 0; i <= steps; i++) {
					diagram[l.sy + i * ystep][l.sx]++;
				}
			}
			else if (draw_diagonals) {
				int steps = std::abs(l.sy - l.ey);
				for (int i = 0; i <= steps; i++) {
					diagram[l.sy + i * ystep][l.sx + i * xstep]++;
				}
			}
		}
	}

	void Print(int** diagram) {
		for (int i = 0; i < diagram_size; i++) {
			for (int j = 0; j < diagram_size; j++) {
				if (diagram[i][j] > 0) {
					std::cout << diagram[i][j];
				}
				else {
					std::cout << '.';
				}
			}
			std::cout << std::endl;
		}
	}

	template<typename T>
	int sign(T val)
	{
		return (T(0) < val) - (val < T(0));
	}
}