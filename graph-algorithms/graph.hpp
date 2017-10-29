#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_

#include <iostream>
#include <vector>
#include <list>

namespace graph
{

	using adjacency_list = std::vector<std::list<std::pair<int, double>>>;
	using size_type = size_t;

	class directed_graph
	{

		public:
			directed_graph(const size_type &v)
				:a_list{v}
			{}

			size_type size(void) const
			{
				return a_list.size();
			}

			std::list<std::pair<int, double>>& operator[](const size_type &n)
			{
				return a_list[n];
			}

			const std::list<std::pair<int, double>>& operator[](const size_type &n) const
			{
				return a_list[n];
			}

			void add_edge(const int &bg, const int &en, const double &we)
			{
				a_list[bg].push_back(std::make_pair(en, we));
			}

		private:
			adjacency_list a_list;
	}; // class directed_graph

} // namespace graph

#endif // _GRAPH_HPP_
