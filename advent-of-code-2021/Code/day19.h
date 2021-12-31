#pragma once
#include <vector>
#include <cmath>

namespace day19 {
	enum Axis {
		X = 0,
		Y = 1,
		Z = 2,
	};

	enum Sign {
		P = 1,
		N = -1,
	};

	class Vector3 {
	public:
		Vector3() : Vector3(0, 0, 0) {
		
		}

		Vector3(int x, int y, int z) {
			value[Axis::X] = x;
			value[Axis::Y] = y;
			value[Axis::Z] = z;
		}

		int ManhattanLength() {
			return std::abs(value[0]) + std::abs(value[1]) + std::abs(value[2]);
		}

		Vector3& operator+=(const Vector3& rhs) {
			value[Axis::X] += rhs.value[Axis::X];
			value[Axis::Y] += rhs.value[Axis::Y];
			value[Axis::Z] += rhs.value[Axis::Z];
			return *this;
		}

		Vector3 operator+(const Vector3& rhs) const {
			Vector3 v{
				value[Axis::X] + rhs.value[Axis::X],
				value[Axis::Y] + rhs.value[Axis::Y],
				value[Axis::Z] + rhs.value[Axis::Z]
			};
			return v;
		}

		Vector3 operator-(const Vector3& rhs) const {
			Vector3 v{ 
				value[Axis::X] - rhs.value[Axis::X],
				value[Axis::Y] - rhs.value[Axis::Y],
				value[Axis::Z] - rhs.value[Axis::Z]
			};
			return v;
		}

		bool operator==(const Vector3& rhs) const {
			return value[Axis::X] == rhs.value[Axis::X] &&
				value[Axis::Y] == rhs.value[Axis::Y] &&
				value[Axis::Z] == rhs.value[Axis::Z];
		}

		// https://stackoverflow.com/questions/18854198/stdmap-with-vector3-key-versus-stdvector-using-a-composite-index
		bool operator<(const Vector3& rhs) const {
			return value[Axis::X] < rhs.value[Axis::X] ||
				(value[Axis::X] == rhs.value[Axis::X] && (value[Axis::Y] < rhs.value[Axis::Y] ||
				(value[Axis::Y] == rhs.value[Axis::Y] && value[Axis::Z] < rhs.value[Axis::Z])));
		}

		int& operator [] (int i) { return value[i]; }

	public:
		int value[3];
	};

	class Point {
	public:
		Point(int x, int y, int z) {
			local = { x, y, z };
			oriented = { x, y, z };
		}

		bool operator==(Point& rhs) {
			return this->oriented == rhs.oriented;
		}

		bool operator==(const Point& rhs) {
			return this->oriented == rhs.oriented;
		}

		void Orient(std::vector<std::pair<Axis, Sign>>& orient) {
			oriented[0] = GetOrientAxis(orient[0].first, orient[0].second);
			oriented[1] = GetOrientAxis(orient[1].first, orient[1].second);
			oriented[2] = GetOrientAxis(orient[2].first, orient[2].second);
		}

		int GetOrientAxis(Axis axis, Sign sign) {
			return local[axis] * sign;
		}

	public:
		Vector3 local;
		Vector3 oriented;
	};
	
	class Scanner {
	public:
		void AddPoint(int x, int y, int z);
		void Orient(std::vector<std::pair<Axis, Sign>>& orient);
		bool TryMatch(Scanner& other, int threshold);

	public:
		std::vector<Point> points;
		Vector3 offset;
	};

	void task1();
	void task2();

	void ReadInput(std::vector<Scanner>& scanners);
	void RotateOrientationOnce(std::vector<std::pair<Axis, Sign>>& orientation);

	static std::vector<std::vector<std::pair<Axis, Sign>>> base_orientations
	{
		{{Axis::X, Sign::P}, {Axis::Y, Sign::P}, {Axis::Z, Sign::P}}, // Forward X+
		{{Axis::Y, Sign::P}, {Axis::X, Sign::N}, {Axis::Z, Sign::P}}, // Forward Y+
		{{Axis::X, Sign::N}, {Axis::Y, Sign::N}, {Axis::Z, Sign::P}}, // Forward X-
		{{Axis::Y, Sign::N}, {Axis::X, Sign::P}, {Axis::Z, Sign::P}}, // Forward Y-
		{{Axis::Z, Sign::P}, {Axis::Y, Sign::P}, {Axis::X, Sign::N}}, // Forward Z+
		{{Axis::Z, Sign::N}, {Axis::Y, Sign::P}, {Axis::X, Sign::P}}, // Forward Z-
	};
}