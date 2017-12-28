#ifndef _GRAPH_ALGORITHM_HPP_
#define _GRAPH_ALGORITHM_HPP_

#include <iostream>
#include <vector>
#include <list>
#include <limits>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include "graph_algorithm_detail.hpp"
#include "graph.hpp"

using path_matrix = std::vector<std::vector<double>>;
using min_heap = std::priority_queue<int, std::vector<int>, std::greater<int>>;
static const double inf = std::numeric_limits<double>::infinity();

namespace graph::algorithm
{

	std::vector<int>
	topological_sort(const directed_graph &G)
	{
		auto entry_degree{detail::get_entry_deg(G)};
		min_heap current;

		for(size_t i = 0; i < G.size(); ++i)
			if(0 == entry_degree[i])
				current.push(i);

		std::vector<int> sorted;
		sorted.reserve(G.size());

		while(!current.empty())
		{
			auto min_vertex{current.top()};
			current.pop();
			sorted.push_back(min_vertex);

			for(auto e : G[min_vertex])
				if(0 == --entry_degree[e.first])
					current.push(e.first);
		}

		return sorted;
	} /* topological_sort */

	std::vector<double>
	acyclic_shortest_path(const directed_graph &G, const int &start_v)
	{
		auto entry_degree{detail::get_entry_deg(G)};
		min_heap current;

		for(size_t i = 0; i < G.size(); ++i)
			if(0 == entry_degree[i])
				current.push(i);

		std::vector<double> path(G.size(), inf);
		path[start_v] = 0;

		while(!current.empty())
		{
			auto min_vertex{current.top()};
			current.pop();

			for(auto e : G[min_vertex])
			{
				int v{e.first};
				double weight{e.second};

				if(weight + path[min_vertex] < path[v])
					path[v] = weight + path[min_vertex];

				if(0 == --entry_degree[v])
					current.push(v);
			}
		}

		return path;
	} /* acyclic_shortest_path */

	std::vector<double>
	dijkstra_shortest_path(const directed_graph &G, const int &start_v)
	{
		std::vector<std::pair<double, bool>> path(G.size(), std::make_pair(inf, false));
		path[start_v].first = 0;

		size_t unvisited{path.size()};
		while(unvisited)
		{
			/* find the minimal unvisited vertex */
			auto min_vertex{std::min_element(path.begin(), path.end(),
					detail::dijkstra_comparator)};

			/* mark vertex as visited */
			min_vertex->second = true;
			--unvisited;

			long u{min_vertex - path.begin()};
			for(auto e : G[u])
			{
				int v{e.first};
				double weight{e.second};

				if(path[v].first > weight + path[u].first)
					path[v].first = weight + path[u].first;
			}
		}

		std::vector<double> result;
		result.reserve(path.size());
		for(auto e : path)
			result.push_back(e.first);

		return result;
	} /* dijkstra_shortest_path */

	path_matrix
	floyd_warshall_shortest_path(const directed_graph &G)
	{
		/* initialize the path matrix */
		path_matrix res(G.size(), std::vector<double>(G.size(), inf));
		for(size_t i = 0; i < G.size(); ++i)
			for(auto e : G[i])
				res[i][e.first] = e.second;

		for(size_t i = 0; i < res.size(); ++i)
			for(size_t j = 0; j < res[i].size(); ++j)
				for(size_t k = 0; k < res[i].size(); ++k)
					if(res[i][k] + res[j][i] < res[j][k])
						res[j][k] = res[i][k] + res[j][i];

		return res;
	} /* floyd_warshall_shortest_path */

} /* nested namespace graph::algorithm */

#endif /* _GRAPH_ALGORITHM_HPP_ */
