#include "day13.h"
#include <iostream>
#include <fstream>
#include <string>

namespace day13 {

	void Paper::AddPoint(const std::pair<int, int> point)	{
		points.push_back(point);
	}

	void Paper::Fold(const std::pair<FoldAlong, int>& fold) {
		if (fold.first == FoldAlong::X) {
			for (auto& point : points) {
				if (point.first > fold.second) {
					point.first = fold.second - (point.first - fold.second);
				}
			}
		} else if (fold.first == FoldAlong::Y) {
			for (auto& point : points) {
				if (point.second > fold.second) {
					point.second = fold.second - (point.second - fold.second);
				}
			}
		}
	}

	int Paper::GetPointCount() {
		return points.size();
	}

	void Paper::PrintCode() {
		int x = 0, y = 0;
		for (const auto& point : points) {
			if (point.first > x) {
				x = point.first;
			}			
			if (point.second > y) {
				y = point.second;
			}
		}

		for (int yy = 0; yy <= y; yy++) {
			for (int xx = 0; xx <= x; xx++) {
				std::pair<int, int> point { xx, yy };
				if (std::find(points.begin(), points.end(), point) == points.end()) {
					std::cout << ".";
				}
				else {
					std::cout << "#";
				}
			}

			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	void Paper::RemoveDuplicates() {
		for (int i = 0; i < points.size(); i++) {
			for (int j = i + 1; j < points.size(); j++) {
				if (points[i] == points[j]) {
					points.erase(points.begin() + j);
				}
			}
		}
	}

	void task1() {
		Paper paper;
		std::vector<std::pair<FoldAlong, int>> folds;

		ReadInput(paper, folds);
		paper.Fold(folds[0]);
		paper.RemoveDuplicates();
		std::cout << paper.GetPointCount() << std::endl;
	}

	void task2() {
		Paper paper;
		std::vector<std::pair<FoldAlong, int>> folds;

		ReadInput(paper, folds);
		for(const auto& fold : folds) {
			paper.Fold(fold);
		}
		paper.RemoveDuplicates();
		paper.PrintCode();
	}

	void ReadInput(Paper& paper, std::vector<std::pair<FoldAlong, int>>& folds) {
		std::ifstream in(".\\Inputs\\day13.txt");
		int px, py, distance;
		FoldAlong fold;

		std::string line;
		while (std::getline(in, line)) {
			if (line[0] != 'f') {
				int pos = line.find(',');
				if (pos == std::string::npos) {
					continue;
				}
				px = std::stoi(line.substr(0, pos));
				py = std::stoi(line.substr(pos + 1));
				paper.AddPoint({ px, py });
			}
			else if (line[0] == 'f') {
				int pos = line.find('=');
				fold = line[pos - 1] == 'x' ? FoldAlong::X : FoldAlong::Y;
				distance = std::stoi(line.substr(pos + 1));
				folds.push_back({ fold, distance });
			}
		}
	}
}