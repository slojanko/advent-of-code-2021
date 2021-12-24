#include "day16.h"
#include <iostream>
#include <fstream>

namespace day16 {
	void Packet::Parse(std::vector<bool>& bits, int& offset) {
        version = ReadInt(bits, offset, 3);
        type_id = ReadInt(bits, offset, 3);

        if (type_id == 4) {
            value = ReadLiteral(bits, offset);
        }
        else {
            int length_type_id = ReadInt(bits, offset, 1);

            if (length_type_id == 0) {
                int length = ReadInt(bits, offset, 15);
                int final_offset = offset + length;
                while (offset != final_offset) {
                    Packet child;
                    child.Parse(bits, offset);
                    packets.push_back(child);
                }
            }
            else {
                int child_count = ReadInt(bits, offset, 11);
                for (int i = 0; i < child_count; i++) {
                    Packet child;
                    child.Parse(bits, offset);
                    packets.push_back(child);
                }
            }
        }
	}

    int Packet::GetSumOfVersions() const {
        int version_sum = version;

        if (type_id != 4) {
            for (const auto& child : packets) {
                version_sum += child.GetSumOfVersions();
            }

        }

        return version_sum;
    }

    __int64 Packet::Evaluate() const {
        switch (type_id) {
        case 0: {
            __int64 sum = 0;
            for (const auto& child : packets) {
                sum += child.Evaluate();
            }
            return sum;
        }
        case 1: {
            __int64 product = 1;
            for (const auto& child : packets) {
                product *= child.Evaluate();
            }
            return product;
        }
        case 2: {
            __int64 min = INT64_MAX;
            for (const auto& child : packets) {
                int temp = child.Evaluate();
                if (temp < min) {
                    min = temp;
                }
            }
            return min;
        }
        case 3: {
            __int64 max = INT64_MIN;
            for (const auto& child : packets) {
                int temp = child.Evaluate();
                if (temp > max) {
                    max = temp;
                }
            }
            return max;
        }
        case 4: {
            return value;
        }
        case 5: {
            __int64 first = packets[0].Evaluate();
            __int64 second = packets[1].Evaluate();
            return first > second;
        }
        case 6: {
            __int64 first = packets[0].Evaluate();
            __int64 second = packets[1].Evaluate();
            return first < second;
        }
        case 7: {
            __int64 first = packets[0].Evaluate();
            __int64 second = packets[1].Evaluate();
            return first == second;
        }
        }
    }

    __int64 Packet::ReadInt(std::vector<bool>& bits, int& offset, const int count) {
        int offset_copy = offset;
        __int64 value = 0;
        for (; offset < offset_copy + count; offset++) {
            value = (value << 1) | bits[offset];
        }

        return value;
    }

    __int64 Packet::ReadLiteral(std::vector<bool>& bits, int& offset) {
        int prefix = 1;
        __int64 value = 0;

        while (prefix) {
            prefix = ReadInt(bits, offset, 1);
            int group = ReadInt(bits, offset, 4);
            value = (value << 4) | group;
        }

        return value;
    }

	void task1() {
		Packet packet;
		ReadInput(packet);
        std::cout << packet.GetSumOfVersions() << std::endl;
	}

	void task2() {
        Packet packet;
        ReadInput(packet);
        std::cout << packet.Evaluate() << std::endl;
	}

	void ReadInput(Packet& packet) {
		std::ifstream in(".\\Inputs\\day16.txt");
		std::string line;
		in >> line;

        std::vector<bool> bits;
        for (const auto& ch : line) {
            AppendCharacterBits(bits, ch);
        }

        int offset = 0;
        packet.Parse(bits, offset);
	}

    void AppendCharacterBits(std::vector<bool>& bits, const char c) {
        switch (toupper(c))
        {
        case '0':
            bits.insert(bits.end(), { 0, 0, 0, 0 });
            return;
        case '1':
            bits.insert(bits.end(), { 0, 0, 0, 1 });
            return;
        case '2':
            bits.insert(bits.end(), { 0, 0, 1, 0 });
            return;
        case '3':
            bits.insert(bits.end(), { 0, 0, 1, 1 });
            return;
        case '4':
            bits.insert(bits.end(), { 0, 1, 0, 0 });
            return;
        case '5':
            bits.insert(bits.end(), { 0, 1, 0, 1 });
            return;
        case '6':
            bits.insert(bits.end(), { 0, 1, 1, 0 });
            return;
        case '7':
            bits.insert(bits.end(), { 0, 1, 1, 1 });
            return;
        case '8':
            bits.insert(bits.end(), { 1, 0, 0, 0 });
            return;
        case '9':
            bits.insert(bits.end(), { 1, 0, 0, 1 });
            return;
        case 'A':
            bits.insert(bits.end(), { 1, 0, 1, 0 });
            return;
        case 'B':
            bits.insert(bits.end(), { 1, 0, 1, 1 });
            return;
        case 'C':
            bits.insert(bits.end(), { 1, 1, 0, 0 });
            return;
        case 'D':
            bits.insert(bits.end(), { 1, 1, 0, 1 });
            return;
        case 'E':
            bits.insert(bits.end(), { 1, 1, 1, 0 });
            return;
        case 'F':
            bits.insert(bits.end(), { 1, 1, 1, 1 });
            return;
        }
    }
}