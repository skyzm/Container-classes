#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include "graph_algorithm.hpp"
#include "graph_algorithm_detail.hpp"
#include "graph.hpp"


int
main (void)
{
	size_t vertex_count{0}, edge_count{0};
	std::cout << "vertex count: ";
	std::cin >> vertex_count;
	std::cout << "edge count: ";
	std::cin >> edge_count;
	graph::directed_graph G{vertex_count};

	std::cout << "edge input (begin, end, weight):\n";
	int path_start{0};
	int start{0}, end{0}, wgh{0};
	for(size_t i = 0; i < edge_count; ++i)
	{
		std::cin >> start >> end >> wgh;
		G.add_edge(start, end, wgh);
	}

	std::cout << "\ntopological_sort:\n";
	auto top_sort{graph::algorithm::topological_sort(G)};
	std::copy(top_sort.begin(), top_sort.end(), std::ostream_iterator<int>{std::cout, " "});

	std::cout << "\nacyclic_shortest_path:\n";
	std::cout << "starting vertex: ";
	std::cin >> path_start;
	auto acl{graph::algorithm::acyclic_shortest_path(G, path_start)};
	std::copy(acl.begin(), acl.end(), std::ostream_iterator<double>{std::cout, " "});

	std::cout << "\ndijkstra_shortest_path:\n";
	std::cout << "starting vertex: ";
	std::cin >> path_start;
	auto dij{graph::algorithm::dijkstra_shortest_path(G, path_start)};
	std::copy(dij.begin(), dij.end(), std::ostream_iterator<double>{std::cout, " "});

	std::cout << "\nfloyd_warshall_shortest_path:\n";
	auto fw{graph::algorithm::floyd_warshall_shortest_path(G)};
	std::for_each(fw.begin(), fw.end(),
			[] (const auto &v)
			{
				for(auto e : v)
					std::cout << e << " ";
				std::cout << std::endl;
			});

	return 0;
}
