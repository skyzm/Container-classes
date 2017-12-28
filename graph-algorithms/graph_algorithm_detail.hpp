#ifndef _GRAPH_ALGORITHM_DETAIL_HPP
#define _GRAPH_ALGORITHM_DETAIL_HPP

#include <vector>
#include <list>
#include <unordered_set>
#include "graph.hpp"

namespace graph::algorithm::detail
{

	void
	dfs_traverse(const directed_graph &G, const int &n, std::vector<int> &en_deg)
	{
		struct dfs_helper
		{
			void operator()(const directed_graph &G, const int &n, std::vector<int> &en_deg)
			{
				++en_deg[n];
				if(visited.end() != visited.find(n))
					return;

				visited.emplace(n);

				for(auto e : G[n])
					this->operator()(G, e.first, en_deg);
			}

			private:
				std::unordered_set<int> visited;
		}; /* struct dfs_helper */

		dfs_helper traverse{};
		traverse(G, n, en_deg);
	} /* dfs_traverse */

	std::vector<int>
	get_entry_deg(const directed_graph &G)
	{
		std::vector<int> entry(G.size(), 0);
		entry[0] = -1;
		dfs_traverse(G, 0, entry);

		return entry;
	} /* get_entry_deg */

	const auto dijkstra_comparator
	{
		[] (const auto &a, const auto &b)
		{
			if(a.second && !b.second)
				return false;
			else if(!a.second && b.second)
				return true;

			return a.first < b.first;
		}
	}; /* dijkstra_comparator */


} /* namespace graph::algorithm::detail */

#endif
