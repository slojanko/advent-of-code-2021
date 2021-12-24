#pragma once
#include <vector>
#include <string>
#include <map>

namespace day12 {
	class Path;

	class Graph {
	public:
		void AddConnection(std::string a, std::string b);
		int CalculateUniquePaths(Path& path);

	private:
		std::map<std::string, std::vector<std::string>> connections;
	};

	class Path {
	public:
		void AddCave(std::string cave);
		void PopCave();
		bool CanAddCave(std::string cave);

	public:
		bool revisit_happened = false;
		bool revisit_allowed = false;
		std::vector<std::string> caves;
	};

	void task1();
	void task2();

	void ReadInput(Graph& graph);
}