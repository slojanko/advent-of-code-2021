#pragma once
#include <vector>
#include <string>

namespace day18 {
	class Pair;

	class Homework {
	public:
		void AddPair(Pair* pair);
		Pair* Solve();
		Pair* SolveOnlyTwo(int first, int second);

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
		void Free();
		int GetMagnitude();

	private:
		void Reduce();
		bool Explode(int depth);
		bool Split();

		// came_from - prevent revisiting same Pair
		// can_check_* - prevent visiting other side if recursively check parent
		bool AddLeft(Pair* came_from, bool can_check_right, int value);
		bool AddRight(Pair* came_from, bool can_check_left, int value);

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