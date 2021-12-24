#include "day2.h"
#include <iostream>
#include <fstream>

namespace day2 {
    void task1() {
        std::vector<std::pair<std::string, int>> commands;
        ReadInput(commands);

        int hor = 0, depth = 0;
        for(const auto& command : commands) {
            if (command.first == "forward") {
                hor += command.second;
            }
            else if (command.first == "down") {
                depth += command.second;
            }
            else if (command.first == "up") {
                depth -= command.second;
            }
        }

        std::cout << (depth * hor) << std::endl;
        std::cin;
    }

    void task2() {
        std::vector<std::pair<std::string, int>> commands;
        ReadInput(commands);

        int hor = 0, depth = 0, aim = 0;
        for (const auto& command : commands) {
            if (command.first == "forward") {
                hor += command.second;
                depth += aim * command.second;
            }
            else if (command.first == "down") {
                aim += command.second;
            }
            else if (command.first == "up") {
                aim -= command.second;
            }
        }

        std::cout << (depth * hor) << std::endl;
        std::cin;
    }

    void ReadInput(std::vector<std::pair<std::string, int>>& commands) {
        std::ifstream in(".\\Inputs\\day2.txt"); 
        std::string direction;
        int distance;
        while (in >> direction >> distance) {
            commands.push_back({ direction, distance });
        }
    }
}