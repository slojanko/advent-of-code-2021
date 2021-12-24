#pragma once
#include <string>
#include <vector>

namespace day15 {
	struct Field;

	class Cavern {
	public:
		Cavern() {
			visited_fields.reserve(1000000);
			queued_fields.reserve(1000000);
		}

		void AddRow(const std::string& row);
		void ComputeRiskPaths();
		Field* GetAndRemoveLowestQueuedField();
		int GetBottomRightLowestRiskSum();
		void ExpandMapFiveTimes();
		void PrintCavern();

	private:
		std::vector<Field*> queued_fields;
		std::vector<Field*> visited_fields;
		std::vector<std::vector<Field>> area;
	};

	struct Field {
		Field(int risk_level, std::pair<int16_t, int16_t> position) {
			this->risk_level = risk_level;
			this->position = position;
		}

		int risk_level = 0;
		std::pair<int16_t, int16_t> position;
		int lowest_risk_sum = INT_MAX;
		Field* lowest_risk_predecessor = nullptr;

		bool visited = false;
		bool queued = false;
	};

	void task1();
	void task2();

	void ReadInput(Cavern& cavern);

	static std::vector<std::pair<int16_t, int16_t>> neighbor_offsets{ {-1, 0}, {0, -1}, {0, 1}, {1, 0} };
}