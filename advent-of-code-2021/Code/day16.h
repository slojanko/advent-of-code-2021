#pragma once
#include <vector>
#include <memory>

namespace day16 {
	class Packet {
		uint8_t version, type_id;
		int value;
		std::vector<Packet> packets;
	};

	void task1();
	void task2();

	void ReadInput(Packet& packet);
}