#pragma once
#include <vector>
#include <string>
#include <map>

namespace day14 {
	class Rule;

	class Polymer {
	public:
		void SetTemplate(const std::string& templ);
		void AddRule(char first, char second, char insert);
		void PerformSteps(int steps);
		char GetRule(char first, char second);
		__int64 GetMostCommonCount();
		__int64 GetLeastCommonCount();

	private:
		std::map<std::pair<char, char>, __int64> pairs;
		std::map<char, __int64> occurences;
		std::vector<Rule> rules;
	};

	struct Rule {
		Rule(char first, char second, char insert) {
			this->first = first;
			this->second = second;
			this->insert = insert;
		}

		char first;
		char second;
		char insert;
	};

	void task1();
	void task2();

	void ReadInput(Polymer& polymer);
}