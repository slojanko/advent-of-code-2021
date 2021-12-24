#include "day8.h"
#include <iostream>
#include <fstream>

namespace day8 {
	void task1() {
        std::ifstream in(".\\Inputs\\day8.txt");

		std::string segment;
        int count = 0;

		while(!in.eof()) {
			while (in.peek() != '|') {
				in.ignore();
			}
			in.ignore();

			for(int i = 0; i < 4; i++) {
				in >> segment;
				if (segment.length() == 2 || segment.length() == 4 || segment.length() == 3 || segment.length() == 7) {
					count++;
				}
			}
		}

		std::cout << count << std::endl;
	}

	void task2() {
		std::ifstream in(".\\Inputs\\day8.txt");
		int sum = 0;

		while(!in.eof()) {
			int line_sum = 0;
			std::string pattern;
			input_patterns.clear();

			for (int i = 0; i < 10; i++) {
				in >> pattern;
				input_patterns.push_back(pattern);
			}
			in.ignore(2);

			std::string mapping = "abcdefg";
			ComputeMapping(mapping, 0);

			for (int i = 0; i < 4; i++) {
				in >> pattern;
			
				pattern = ApplyMapping(pattern, mapping);
				line_sum = line_sum * 10 + FindSegment(pattern);
			}

			sum += line_sum;
		}

		 std::cout << sum << std::endl;
	}

	bool ComputeMapping(std::string& str, int depth)	{
		if (depth == str.size()) {
			if (CheckMapping(str)) {
				return true;
			}
			return false;
		}

		for (int i = depth; i < str.size(); i++) {
			std::swap(str[i], str[depth]);
			if (ComputeMapping(str, depth + 1)) {
				return true;
			}
			std::swap(str[i], str[depth]);
		}

		return false;
	}

	bool CheckMapping(std::string& mapping)	{
		for (const auto& input : input_patterns) {
			std::string input_pattern_mapped = ApplyMapping(input, mapping);

			bool mapping_valid = FindSegment(input_pattern_mapped) >= 0;

			if (!mapping_valid) {
				return false;
			}
		}

		return true;
	}

	std::string ApplyMapping(std::string string, std::string& mapping) {
		for (int i = 0; i < string.size(); i++) {
			int pos = mapping.find(string[i]);
			string[i] = 'a' + pos;
		}
		return string;
	}

	int FindSegment(std::string& string) {
		for (int i = 0; i < digit_segments.size(); i++) {
			if (string.size() != digit_segments[i].size()) {
				continue;
			}

			bool is_match = true;
			for (const auto& ch : string) {
				if (digit_segments[i].find(ch) == std::string::npos) {
					is_match = false;
					break;
				}
			}

			if (is_match) {
				return i;
			}
		}

		return -1;
	}
}