#include "day14.h"
#include <iostream>
#include <fstream>

namespace day14 {

	void Polymer::SetTemplate(const std::string& templ)	{
		occurences[templ[0]] = 1;
		for (int i = 1; i < templ.size(); i++) {
			pairs[{templ[i - 1], templ[i]}]++;
			occurences[templ[i]]++;
		}
	}

	void Polymer::AddRule(const char first, const char second, const char insert) {
		rules.push_back(Rule(first, second, insert));
	}

	void Polymer::PerformSteps(int steps) {
		for(int st = 0; st < steps; st++) {
			std::map<std::pair<char, char>, __int64> new_pairs;

			for (const auto& pair : pairs) {
				char insert = GetRule(pair.first.first, pair.first.second);
				if (insert != '\0') {
					new_pairs[{pair.first.first, insert}] += pair.second;
					new_pairs[{insert, pair.first.second}] += pair.second;

					occurences[insert] += pair.second;
				}
			}

			pairs = new_pairs;
		}
	}

	char Polymer::GetRule(char first, char second) {
		const auto& rule = std::find_if(rules.begin(), rules.end(), [first, second](const Rule& val) { return val.first == first && val.second == second; });
		if (rule == rules.end()) {
			return '\0';
		}
		else {
			return (*rule).insert;
		}
	}

	__int64 Polymer::GetMostCommonCount() {
		__int64 max = INT64_MIN;
		for (auto i : occurences) {
			if (i.second > max) {
				max = i.second;
			}
		}

		return max;
	}

	__int64 Polymer::GetLeastCommonCount() {
		__int64 min = INT64_MAX;
		for (auto i : occurences) {
			if (i.second < min) {
				min = i.second;
			}
		}

		return min;
	}

	void task1() {
		Polymer polymer;
		ReadInput(polymer);
		polymer.PerformSteps(10);
		std::cout << (polymer.GetMostCommonCount() - polymer.GetLeastCommonCount()) << std::endl;
	}

	void task2() {
		Polymer polymer;
		ReadInput(polymer);
		polymer.PerformSteps(40);
		std::cout << (polymer.GetMostCommonCount() - polymer.GetLeastCommonCount()) << std::endl;
	}

	void ReadInput(Polymer& polymer) {
		std::ifstream in(".\\Inputs\\day14.txt");
		std::string line;

		in >> line;
		polymer.SetTemplate(line);
		in.ignore(1, '\n');
		in.ignore(1, '\n');

		char first, second, insert;
		while (!in.eof()) {
			first = in.get();
			second = in.get();
			in.ignore(4);
			insert = in.get();
			in.ignore(1, '\n');

			polymer.AddRule(first, second, insert);
		}
	}
}