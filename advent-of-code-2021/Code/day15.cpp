#include "day15.h"
#include <iostream>
#include <fstream>
#include <algorithm>

namespace day15 {
	void Cavern::AddRow(const std::string& row) {
		std::vector<Field> row_fields;
		for (int x = 0; x < row.size(); x++) {
			Field field(row[x] - '0', { x, area.size() });
			row_fields.push_back(field);
		}

		area.push_back(row_fields);
	}

	void Cavern::ComputeRiskPaths() {
		area[0][0].risk_level = 0;
		area[0][0].lowest_risk_sum = 0;

		queued_fields.push_back(&(area[0][0]));
		area[0][0].queued = true;

		while (queued_fields.size() > 0) {
			Field* field = GetAndRemoveLowestQueuedField();
			visited_fields.push_back(field);
			field->visited = true;

			for (const auto& offset : neighbor_offsets) {
				std::pair<int16_t, int16_t> neighbor_position { field->position.first + offset.first, field->position.second + offset.second };

				if (neighbor_position.first < 0 || neighbor_position.first >= area[0].size() || neighbor_position.second < 0 || neighbor_position.second >= area.size()) {
					continue;
				}

				Field* neighbor = &area[neighbor_position.second][neighbor_position.first];

				// Field was already visited, meaning it was the lowest at some point
				// Better to have flag than check if vector contains it, a lot faster
				if (neighbor->visited) {
					continue;
				}

				if (field->lowest_risk_sum + neighbor->risk_level < neighbor->lowest_risk_sum) {
					neighbor->lowest_risk_sum = field->lowest_risk_sum + neighbor->risk_level;
					neighbor->lowest_risk_predecessor = field;
				}

				// No need to queue twice
				// Better to have flag than check if vector contains it, a lot faster
				if (neighbor->queued == false) {
					queued_fields.push_back(neighbor);
					neighbor->queued = true;
				}
			}
		}
	}

	Field* Cavern::GetAndRemoveLowestQueuedField() {
		if (queued_fields.size() == 0) {
			return nullptr;
		}

		int pos = 0;
		for (int i = 1; i < queued_fields.size(); i++) {
			if (queued_fields[i]->lowest_risk_sum < queued_fields[pos]->lowest_risk_sum) {
				pos = i;
			}
		}

		Field* ret = queued_fields[pos];
		queued_fields.erase(queued_fields.begin() + pos);

		return ret;
	}

	int Cavern::GetBottomRightLowestRiskSum() {
		return area.back().back().lowest_risk_sum;
	}

	void Cavern::ExpandMapFiveTimes() {
		int original_height = area.size();
		int original_width = area[0].size();

		// First duplicate rows down
		for (int i = 1; i < 5; i++) {
			for (int y = 0; y < original_height; y++) {
				std::vector<Field> original_row_copy = area[y];

				for (Field& field : original_row_copy) {
					int new_risk = (field.risk_level + i);
					if (new_risk > 9) {
						new_risk -= 9;
					}
					field.risk_level = new_risk;
					field.position.second += i * original_height;
				}

				area.push_back(original_row_copy);
			}
		}

		// Then duplicate rows right
		for (int y = 0; y < area.size(); y++) {
			std::vector<Field> original_row_copy = area[y];
			for (int i = 1; i < 5; i++) {
				std::vector<Field> insert_row = original_row_copy;

				for (Field& field : insert_row) {
					int new_risk = (field.risk_level + i);
					if (new_risk > 9) {
						new_risk -= 9;
					}
					field.risk_level = new_risk;
					field.position.first += i * original_width;
				}

				area[y].insert(area[y].end(), insert_row.begin(), insert_row.end());
			}
		}
	}

	void Cavern::PrintCavern() {
		for (const auto& row : area) {
			for (const auto& field : row) {
				std::cout << field.risk_level;
			}

			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	void task1() {
		Cavern cavern;
		ReadInput(cavern);

		cavern.ComputeRiskPaths();
		std::cout << cavern.GetBottomRightLowestRiskSum() << std::endl;
	}

	void task2() {
		Cavern cavern;
		ReadInput(cavern);
		cavern.ExpandMapFiveTimes();

		cavern.ComputeRiskPaths();
		std::cout << cavern.GetBottomRightLowestRiskSum() << std::endl;
	}

	void ReadInput(Cavern& cavern) {
		std::ifstream in(".\\Inputs\\day15.txt");
		std::string line;

		while (in >> line) {
			cavern.AddRow(line);
		}
	}
}