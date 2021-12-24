#pragma once
#include <vector>

namespace day4 {
	struct bingo_board {
		int numbers[5][5];

		int operator [] (int pos) const { return numbers[pos / 5][pos % 5]; }
		int& operator [] (int pos) { return numbers[pos / 5][pos % 5]; }

		void CrossNumber(int num) {
			for (int y = 0; y < 5; y++) {
				for (int x = 0; x < 5; x++) {
					if (numbers[y][x] == num) {
						numbers[y][x] = -1;
					}
				}
			}
		}

		bool IsSolved() {
			for (int y = 0; y < 5; y++) {
				bool hor = true, vert = true;
				for (int x = 0; x < 5; x++) {
					if (numbers[y][x] != -1) {
						hor = false;
					}

					if (numbers[x][y] != -1) {
						vert = false;
					}
				}

				if (hor || vert) {
					return true;
				}
			}

			return false;
		}

		int GetScore() {
			int score = 0;
			for (int y = 0; y < 5; y++) {
				for (int x = 0; x < 5; x++) {
					if (numbers[y][x] != -1) {
						score += numbers[y][x];
					}
				}
			}
			return score;
		}
	};

	void task1();
	void task2();

	void ReadInput(std::vector<int>& numbers, std::vector<bingo_board>& boards);
}