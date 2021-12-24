#include "day3.h"
#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>

namespace day3 {
    void task1() {
        std::vector<std::bitset<bits_count>> lines;
        ReadInput(lines);

        std::bitset<bits_count> gamma, epsilon;
        for (int i = 0; i < bits_count; i++) {
            int ones = 0;
            for (const auto& bits_row : lines) {
                if (bits_row[i]) {
                    ones++;
                }
            }

            gamma[i] = ones > (lines.size() - ones);
        }

        // Flip operates on itself, so need to duplicate gamma then flip
        epsilon = std::bitset<bits_count>(gamma).flip();

        std::cout << (gamma.to_ulong() * epsilon.to_ulong()) << std::endl;
        std::cin;
    }

    void task2() {
        std::vector<std::bitset<bits_count>> lines;
        ReadInput(lines);

        std::vector<std::bitset<bits_count>> oxygen_bits(lines);
        std::vector<std::bitset<bits_count>> scrubber_bits(lines);

        for (int i = 1; i <= bits_count; i++) {
            int bit_to_check = bits_count - i;
            int ones = 0;
            bool bit_to_keep;

            int size = oxygen_bits.size();
            if (size > 1) {
                for (const auto& bits_row : oxygen_bits) {
                    if (bits_row[bit_to_check]) {
                        ones++;
                    }
                }
                // Keep numbers with bit equal to most common bit
                bit_to_keep = ones >= (size - ones);
                for (int j = size - 1; j >= 0; j--) {
                    if (oxygen_bits[j][bit_to_check] != bit_to_keep) {
                        oxygen_bits.erase(oxygen_bits.begin() + j);
                    }
                }
            }

            size = scrubber_bits.size();
            if (size > 1) {
                ones = 0;
                for (const auto& bits_row : scrubber_bits) {
                    if (bits_row[bit_to_check]) {
                        ones++;
                    }
                }
                // Keep numbers with bit different to most common bit
                bit_to_keep = ones < (size - ones);
                for (int j = size - 1; j >= 0; j--) {
                    if (scrubber_bits[j][bit_to_check] != bit_to_keep) {
                        scrubber_bits.erase(scrubber_bits.begin() + j);
                    }
                }
            }
        }

        std::cout << (oxygen_bits[0].to_ulong() * scrubber_bits[0].to_ulong()) << std::endl;
        std::cin;
    }
    void ReadInput(std::vector<std::bitset<bits_count>>& lines) {
        std::ifstream in(".\\Inputs\\day3.txt");

        std::string line;
        while (in >> line) {
            lines.push_back(std::bitset<bits_count>(line));
        }
    }
}