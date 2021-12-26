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
		pair_left->parent = this;
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

	void Pair::Reduce() {
		Explode(0);

		//while (true) {
		//	if (Explode(0)) {
		//		continue;
		//	}
		//	if (Split()) {
		//		continue;
		//	}

		//	break;
		//}
	}

	bool Pair::Explode(int depth) {
		if (IsNumber()) {
			return false;
		}

		if (depth == 3) {
			if (!pair_left->IsNumber()) {
				parent->AddLeft(this, pair_left->pair_left->value);
				AddRight(pair_left, pair_left->pair_right->value);
				delete pair_left->pair_left;
				delete pair_left->pair_right;
				pair_left->value = 0;
				return true;
			}
		
			if (!pair_right->IsNumber()) {
				AddLeft(pair_right, pair_right->pair_left->value);
				parent->AddRight(this, pair_right->pair_right->value);
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
		return false;

	}

	bool Pair::AddLeft(Pair* source, int value) {
		if (IsNumber()) {
			this->value += value;
			return true;
		}

		if (pair_right && pair_right != source) {
			if (pair_right->AddLeft(this, value)) {
				return true;
			}
		}

		if (pair_left && pair_left != source) {
			if (pair_left->AddLeft(this, value)) {
				return true;
			}
		}

		return parent->AddLeft(this, value);
	}

	bool Pair::AddRight(Pair* source, int value) {
		if (IsNumber()) {
			this->value += value;
			return true;
		}

		if (pair_left && pair_left != source) {
			if (pair_left->AddRight(this, value)) {
				return true;
			}
		}

		if (pair_right && pair_right != source) {
			if (pair_right->AddRight(this, value)) {
				return true;
			}
		}

		return parent->AddRight(this, value);
	}

	void task1() {
		Homework homework;;
		ReadInput(homework);
		Pair* result = homework.Solve();
		result->Print();
	}

	void task2() {

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
}