#include "day12.h"
#include <iostream>
#include <fstream>
#include <cstring>

namespace day12 {
	void Graph::AddConnection(std::string a, std::string b) {
		if (a != "end" && b != "start") {
			if (connections.find(a) != connections.end()) {
				connections[a].push_back(b);
			}
			else {
				std::vector<std::string> first;
				first.push_back(b);
				connections[a] = first;
			}
		}

		if (b != "end" && a != "start") {
			if (connections.find(b) != connections.end()) {
				connections[b].push_back(a);
			}
			else {
				std::vector<std::string> first;
				first.push_back(a);
				connections[b] = first;
			}
		}
	}
	
	int Graph::CalculateUniquePaths(Path& path) {
		if (path.caves.back() == "end") {
			//for (const auto& cave : path.caves) {
			//	std::cout << cave << " ";
			//}
			//std::cout << std::endl;

			return 1;
		}

		int unique_paths = 0;
		int local_revisit_happend = path.revisit_happened;

		for (const auto& connection : connections[path.caves.back()]) {
			if (path.CanAddCave(connection)) {
				path.AddCave(connection);

				unique_paths += CalculateUniquePaths(path);

				path.PopCave();
				path.revisit_happened = local_revisit_happend;
			}
		}

		return unique_paths;
	}

	void Path::AddCave(std::string cave) {
		bool revisit_just_happened = islower(cave[0]) && std::find(caves.begin(), caves.end(), cave) != caves.end();
		caves.push_back(cave);
		revisit_happened |= revisit_just_happened;
	}

	void Path::PopCave() {
		caves.pop_back();
	}

	bool Path::CanAddCave(std::string cave) {
		return isupper(cave[0]) || (revisit_allowed && !revisit_happened) || std::find(caves.begin(), caves.end(), cave) == caves.end();
	}

	void task1() {
		Graph graph;
		ReadInput(graph);
		Path path;
		path.AddCave("start");
		std::cout << graph.CalculateUniquePaths(path) << std::endl;
	}

	void task2() {
		Graph graph;
		ReadInput(graph);
		Path path;
		path.AddCave("start");
		path.revisit_allowed = true;
		std::cout << graph.CalculateUniquePaths(path) << std::endl;
	}

	void ReadInput(Graph& graph) {
		std::ifstream in(".\\Inputs\\day12.txt");
		std::string line, from, to;

		while (!in.eof()) {
			in >> line;
			auto pos = line.find('-');
			from = line.substr(0, pos);
			to = line.substr(pos + 1);

			graph.AddConnection(from, to);
		}
	}
}