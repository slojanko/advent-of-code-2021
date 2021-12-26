#include "day18.h"
#include <iostream>
#include <fstream>

namespace day18 {
	void Homework::AddPair(Pair* pair) {
		pairs.push_back(pair);
	}

	Pair* Homework::Solve() {
		Pair* sum = pairs[0];

		for (int i = 1; i < pairs.size(); i++) {
			Pair* old_sum = sum;
			sum = new Pair();
			sum->pair_left = old_sum;
			sum->pair_right = pairs[i];

			sum->pair_left->parent = sum;
			sum->pair_right->parent = sum;

			sum->Reduce();
		}

		return sum;
	}

	void Pair::Parse(std::string& input, int& offset) {
		// We are at a number
		if (input[offset] != '[') {
			value = input[offset] - '0';
			offset++;
			return;
		}

		// [
		offset++;

		// Left
		pair_left = new Pair();
		pair_left->parent = this;
		pair_left->Parse(input, offset);

		// Comma
		offset++;

		// Right
		pair_right = new Pair();
		pair_right->parent = this;
		pair_right->Parse(input, offset);

		// ]
		offset++;
	}

	void Pair::Print() const {
		if (IsNumber()) {
			std::cout << value;
			return;
		}

		std::cout << '[';
		pair_left->Print();
		std::cout << ',';
		pair_right->Print();
		std::cout << ']';
	}

	void Pair::Free() {
		if (!IsNumber()) {
			pair_left->Free();
			pair_right->Free();

			delete pair_left;
			delete pair_right;
		}
	}

	int Pair::GetMagnitude() {
		if (IsNumber()) {
			return value;
		}

		return 3 * pair_left->GetMagnitude() + 2 * pair_right->GetMagnitude();
	}

	void Pair::Reduce() {
		while (true) {
			if (Explode(0)) {
				continue;
			}
			if (Split()) {
				continue;
			}

			break;
		}
	}

	bool Pair::Explode(int depth) {
		if (IsNumber()) {
			return false;
		}

		if (depth == 3) {
			if (!pair_left->IsNumber()) {
				AddLeft(pair_left, false, pair_left->pair_left->value);
				AddRight(pair_left, false, pair_left->pair_right->value);
				delete pair_left->pair_left;
				delete pair_left->pair_right;
				pair_left->value = 0;
				return true;
			}
		
			if (!pair_right->IsNumber()) {
				AddLeft(pair_right, false, pair_right->pair_left->value);
				AddRight(pair_right, false, pair_right->pair_right->value);
				delete pair_right->pair_left;
				delete pair_right->pair_right;
				pair_right->value = 0;
				return true;
			}
		}

		if (pair_left->Explode(depth + 1)) {
			return true;
		}

		return pair_right->Explode(depth + 1);
	}

	bool Pair::Split() {
		if (IsNumber()) {
			if (value >= 10) {
				pair_left = new Pair();
				pair_left->parent = this;
				pair_left->value = value / 2;

				pair_right = new Pair();
				pair_right->parent = this;
				pair_right->value = (value + 1) / 2;

				value = -1;
				return true;
			}

			return false;
		}

		if (pair_left->Split()) {
			return true;
		}

		return pair_right->Split();
	}

	bool Pair::AddLeft(Pair* came_from, bool can_check_right, int value) {
		if (IsNumber()) {
			this->value += value;
			return true;
		}

		if (can_check_right && pair_right != came_from && pair_right->AddLeft(this, true, value)) {
			return true;
		}

		if (pair_left != came_from && pair_left->AddLeft(this, true, value)) {
			return true;
		}

		return parent && parent->AddLeft(this, false, value);
	}

	bool Pair::AddRight(Pair* came_from, bool can_check_left, int value) {
		if (IsNumber()) {
			this->value += value;
			return true;
		}

		if (can_check_left && pair_left != came_from && pair_left->AddRight(this, true, value)) {
			return true;
		}

		if (pair_right != came_from && pair_right->AddRight(this, true, value)) {
			return true;
		}

		return parent && parent->AddRight(this, false, value);
	}

	void task1() {
		Homework homework;
		ReadInput(homework);
		Pair* result = homework.Solve();
		std::cout << result->GetMagnitude() << std::endl;

		result->Free();
		delete result;
	}

	void task2() {
		std::vector<std::string> lines;
		ReadInput(lines);

		int max_magnitude = 0;
		for(int i = 0; i < lines.size(); i++) {
			for (int j = 0; j < lines.size(); j++) {
				if (i == j) {
					continue;
				}

				int offset;
				Homework homework;

				Pair* pair = new Pair();
				offset = 0;
				pair->Parse(lines[i], offset);
				homework.AddPair(pair);

				pair = new Pair();
				offset = 0;
				pair->Parse(lines[j], offset);
				homework.AddPair(pair);

				Pair* result = homework.Solve();
				int current_max = result->GetMagnitude();
				if (current_max > max_magnitude) {
					max_magnitude = current_max;
				}

				result->Free();
				delete pair;
			}
		}

		std::cout << max_magnitude << std::endl;
	}

	void ReadInput(Homework& homework) {
		std::ifstream in(".\\Inputs\\day18.txt");
		std::string line;

		while (in >> line) {
			int offset = 0;
			Pair* pair = new Pair();
			pair->Parse(line, offset);
			homework.AddPair(pair);
		}
	}

	void ReadInput(std::vector<std::string>& lines) {
		std::ifstream in(".\\Inputs\\day18.txt");
		std::string line;

		while (in >> line) {
			lines.push_back(line);
		}
	}
}