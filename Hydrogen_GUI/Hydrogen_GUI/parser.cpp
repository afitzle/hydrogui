#include <iostream>
#include <fstream>
#include <string>
#include <regex>

typedef struct Count{
	unsigned num_nodes;
	unsigned num_edges;
	unsigned paths_added;
	unsigned paths_removed;
}count_t;

count_t parse_dot_file(std::string filename);

int main() {

	count_t result = parse_dot_file("mydot.dot");
	std::cout << "num nodes: " << result.num_nodes << std::endl
		<< "num edges: " << result.num_edges << std::endl
		<< "paths added: " << result.paths_added << std::endl
		<< "paths removed: " << result.paths_removed << std::endl;
	return 0;
}

count_t parse_dot_file(std::string filename) {

	count_t count;
	count.num_edges = 0;
	count.num_nodes = 0;
	count.paths_added = 0;
	count.paths_removed = 0;
	std::string line;
	std::ifstream file(filename);
	std::regex node_regex("\"[0-9]+\" \\[label=");
	std::regex edge_regex("->");
	std::regex path_add_regex("V2::Branch");
	std::regex path_sub_regex("V1::Branch");
	if (file.is_open()) {
		
		while (std::getline(file, line)) {
			if (std::regex_search(line, node_regex)) {
				count.num_nodes += 1;
			}
			if (std::regex_search(line, edge_regex)) {
				count.num_edges += 1;
			}
			if (std::regex_search(line, path_add_regex)) {
				count.paths_added += 1;
			}
			if (std::regex_search(line, path_sub_regex)) {
				count.paths_removed += 1;
			}
		}
	}
	return count;
}