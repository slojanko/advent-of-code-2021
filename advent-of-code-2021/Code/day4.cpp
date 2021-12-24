#include "day4.h"
#include <iostream>
#include <fstream>
#include <vector>

namespace day4 {
	void task1() {
		std::vector<int> numbers;
		std::vector<bingo_board> boards;
		ReadInput(numbers, boards);

		for (const auto number : numbers) {
			for (auto& board : boards) {
				board.CrossNumber(number);
				if (board.IsSolved()) {
					std::cout << (board.GetScore() * number) << std::endl;
					return;
				}
			}
		}
 	}

	void task2() {
		std::vector<int> numbers;
		std::vector<bingo_board> boards;
		ReadInput(numbers, boards);

		for (const auto number : numbers) {
			for (int i = 0; i < boards.size(); i++) {
				boards[i].CrossNumber(number);
				if (boards[i].IsSolved()) {
					if (boards.size() > 1) {
						boards.erase(boards.begin() + i);
						i--;
					}
					else {
						std::cout << (boards[i].GetScore() * number) << std::endl;
						return;
					}
				}
			}
		}
	}
	void ReadInput(std::vector<int>& numbers, std::vector<bingo_board>& boards) {
		std::ifstream in(".\\Inputs\\day4.txt");
		// Read first line of bingo numbers
		for (int i; in >> i;) {
			numbers.push_back(i);
			if (in.peek() == ',') {
				in.ignore();
			}
			else if (in.peek() == '\n') {
				in.ignore();
				break;
			}
		}

		while (!in.eof()) {
			bingo_board board;
			for (int i = 0; i < 25; i++) {
				in >> board[i];
			}

			boards.emplace_back(board);
		}

	}
}