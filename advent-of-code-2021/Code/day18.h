#pragma once
#include <vector>
#include <string>

namespace day18 {
	class Pair;

	class Homework {
	public:
		void AddPair(Pair* pair);
		Pair* Solve();

	private:
		std::vector<Pair*> pairs;
	};

	class Pair {
		friend class Homework;

	public:
		void Parse(std::string& input, int& offset);
		void Print() const;
		bool IsNumber() const {
			return value != -1;
		}

	private:
		void Reduce();
		bool Explode(int depth);
		bool Split();

		bool AddLeft(Pair* source, int value);
		bool AddRight(Pair* source, int value);

	private:
		int value = -1;
		Pair* parent = nullptr;
		Pair* pair_left = nullptr;
		Pair* pair_right = nullptr;;
	};

	void task1();
	void task2();

	void ReadInput(Homework& pair);
}