#include "day1.h"
#include <iostream>
#include <fstream>

namespace day1 {
    void task1() {
        std::vector<int> numbers;
        ReadInput(numbers);

        int increments = 0;
        for (int i = 0; i < numbers.size() - 1; i++) {
            if (numbers[i] < numbers[i + 1]) {
                increments++;
            }
        }

        std::cout << increments << std::endl;
        std::cin;
    }

    void task2() {
        std::vector<int> numbers;
        ReadInput(numbers);

        // Compare sums of sequential 3 numbers, B C will always be part of sum, so they don't impact result
        // A B C D
        // A B C
        //   B C D
        int increments = 0;
        for (int i = 0; i < numbers.size() - 3; i++) {
            if (numbers[i] < numbers[i + 3]) {
                increments++;
            }
        }

        std::cout << increments << std::endl;
        std::cin;
    }

    void ReadInput(std::vector<int>& numbers) {
        std::ifstream in(".\\Inputs\\day1.txt");
        int num;
        while (in >> num) {
            numbers.push_back(num);
        }
    }
}