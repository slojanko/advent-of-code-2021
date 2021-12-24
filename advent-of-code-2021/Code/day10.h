#pragma once
#include <vector>
#include <string>

namespace day10 {
	void task1();
	void task2();

	void ReadInput(std::vector<std::string>& lines);
	std::vector<char> GetCorruptedCharacters(std::vector<std::string>& lines);
	bool IsCharacterStart(char c);
	char GetCharacterPair(char c);
	std::vector<char> GetMissingCharacters(std::string& line);

	namespace t1 {
		int CharacterToPoints(char c);
	}

	namespace t2 {
		int CharacterToPoints(char c);
	}
}