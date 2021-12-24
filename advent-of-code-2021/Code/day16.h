#pragma once
#include <vector>
#include <memory>

namespace day16 {
	class Packet {
	public:
		void Parse(std::vector<bool>& bits, int& offset);
		int GetSumOfVersions() const;
		__int64 Evaluate() const;

	private:
		__int64 ReadInt(std::vector<bool>& bits, int& offset, const int count);
		__int64 ReadLiteral(std::vector<bool>& bits, int& offset);

	public:
		uint8_t version, type_id;
		__int64 value;
		std::vector<Packet> packets;
	};

	void task1();
	void task2();

	void ReadInput(Packet& packet);
	void AppendCharacterBits(std::vector<bool>& bits, const char c);
}