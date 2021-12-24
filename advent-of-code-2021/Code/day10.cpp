#include "day10.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <algorithm>

namespace day10 {
	void task1() {
		std::vector<std::string> lines;
		ReadInput(lines);
		std::vector<char> corrupted_characters = GetCorruptedCharacters(lines);

		int points = 0;
		for (const auto& c : corrupted_characters) {
			points += t1::CharacterToPoints(c);
		}
		std::cout << points << std::endl;
	}

	void task2() {
		std::vector<std::string> lines;
		ReadInput(lines);

		std::vector<__int64> points;
		for (auto& line : lines) {
			__int64 point = 0;
			std::vector<char> missing_characters = GetMissingCharacters(line);
			if (missing_characters.size() == 0) {
				continue;
			}

			for (const auto& ch : missing_characters) {
				point = point * 5 + t2::CharacterToPoints(ch);
			}

			points.push_back(point);
		}

		std::sort(points.begin(), points.end());
		std::cout << points[points.size() / 2] << std::endl;
	}

	void ReadInput(std::vector<std::string>& lines) {
		std::ifstream in(".\\Inputs\\day10.txt");
		while (!in.eof()) {
			std::string line;
			in >> line;
			lines.push_back(line);
		}
	}

	std::vector<char> GetCorruptedCharacters(std::vector<std::string>& lines) {
		std::vector<char> corrupted_characters;

		for(const auto& line : lines) {
			std::stack<char> stack;
			for (const auto& ch : line) {
				if (IsCharacterStart(ch)) {
					stack.push(ch);
				}
				else {
					if (GetCharacterPair(stack.top()) == ch) {
						stack.pop();
					}
					else {
						corrupted_characters.push_back(ch);
						break;
					}
				}
			}
		}

		return corrupted_characters;
	}

	bool IsCharacterStart(char c) {
		return c == '(' || c == '[' || c == '{' || c == '<';
	}

	char GetCharacterPair(char c) {
		switch (c) {
		case '(': return ')';
		case '[': return ']';
		case '{': return '}';
		case '<': return '>';
		}

		return '0';
	}

	std::vector<char> GetMissingCharacters(std::string& line) {
		std::vector<char> missing_characters;
		std::vector<char> stack;

		for (const auto& ch : line) {
			if (IsCharacterStart(ch)) {
				stack.push_back(ch);
			}
			else {
				if (GetCharacterPair(stack.back()) == ch) {
					stack.pop_back();
				}
				else {
					return missing_characters; // Empty
				}
			}
		}

		// Insert backwards, so <{ would become }>
		for (const auto& ch : stack) {
			missing_characters.insert(missing_characters.begin(), GetCharacterPair(ch));
		}

		return missing_characters;
	}

	namespace t1 {
		int CharacterToPoints(char c) {
			switch (c) {
			case ')': return 3;
			case ']': return 57;
			case '}': return 1197;
			case '>': return 25137;
			}

			return -1;
		}
	}

	namespace t2 {
		int CharacterToPoints(char c) {
			switch (c) {
			case ')': return 1;
			case ']': return 2;
			case '}': return 3;
			case '>': return 4;
			}

			return -1;
		}
	}
}