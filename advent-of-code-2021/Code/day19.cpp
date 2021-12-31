#include "day19.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

namespace day19 {
	void Scanner::AddPoint(int x, int y, int z) {
		points.push_back(Point(x, y, z));
	}

	void Scanner::Orient(std::vector<std::pair<Axis, Sign>>& orient) {
		for (auto& point : points) {
			point.Orient(orient);
		}
	}

	bool Scanner::TryMatch(Scanner& sc, int threshold) {
		std::map<Vector3, int> matches;

		// Find all matched points between this scanner and an umatched one
		for(const auto& point : points) {
			for (const auto& other : sc.points) {
				Vector3 diff = point.oriented - other.oriented;
				matches[diff]++;
			}
		}

		for (auto& match : matches) {
			if (match.second >= 12) {
				sc.offset = offset + match.first;
				return true;
			}
		}

		return false;
	}

	void task1() {
		std::vector<Point> unique_points;
		std::vector<Scanner> matched_scanners;

		std::vector<Scanner> scanners;
		ReadInput(scanners);

		// All will be oriented relative to scanner 0
		unique_points = scanners[0].points;
		matched_scanners.push_back(scanners[0]);
		scanners.erase(scanners.begin());

		int next_scanner = 0;
		while(scanners.size() > 0) {
			next_scanner = (next_scanner + 1) % scanners.size();
			bool match = false;

			for(auto& matched_scanner : matched_scanners) {
				// Create copy (not &), orientation var gets changed below
				for (std::vector<std::pair<Axis, Sign>> orientation : base_orientations) {
					for (int i = 0; i < 4; i++) {
						RotateOrientationOnce(orientation);
						scanners[next_scanner].Orient(orientation);
						if (matched_scanner.TryMatch(scanners[next_scanner], 12)) {
							match = true;
							goto out_of_loop;
						}
					}
				}
			}

out_of_loop:
			if (match == true) {
				for (Point point : scanners[next_scanner].points) {
					point.oriented += scanners[next_scanner].offset;
					if (std::find(unique_points.begin(), unique_points.end(), point) == unique_points.end()) {
						unique_points.push_back(point);
					}
				}
				
				matched_scanners.push_back(scanners[next_scanner]);
				scanners.erase(scanners.begin() + next_scanner);
			}
		}

		std::cout << unique_points.size() << std::endl;

		// Part 2, not worth duplicating everything just to solve part 2...
		int largest_distance = INT_MIN;
		for (const auto& first : matched_scanners) {
			for (const auto& second : matched_scanners) {
				int current_distance = (first.offset - second.offset).ManhattanLength();
				if (current_distance > largest_distance) {
					largest_distance = current_distance;
				}
			}
		}

		std::cout << largest_distance << std::endl;
	}

	void task2() {

	}

	void ReadInput(std::vector<Scanner>& scanners) {
		std::ifstream in(".\\Inputs\\day19.txt");
		std::string line;
		int x, y, z;

		while (std::getline(in, line)) {
			if (line.size() == 0) {
				continue;
			}

			if (line[1] == '-') {
				Scanner sc;
				scanners.push_back(sc);
				continue;
			}

			std::stringstream ss(line);
			ss >> x;
			ss.ignore();
			ss >> y;
			ss.ignore();
			ss >> z;

			scanners.back().AddPoint(x, y, z);
		}
	}

	void RotateOrientationOnce(std::vector<std::pair<Axis, Sign>>& orientation) {
		std::pair<Axis, Sign> copy = orientation[1];
		orientation[1] = orientation[2];
		orientation[2] = copy;
		orientation[2].second = (Sign)(orientation[2].second * Sign::N);
	}
}