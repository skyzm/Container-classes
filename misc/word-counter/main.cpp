/*
* Author: Stefan Pantic.
* GitHub: https://www.github.com/stefanpantic
*
* Description: 	Using the standard library to make a primitive word occurence counter
* 				for passed file.
* NOTE: C++14 or higher requred.
*/

#include <algorithm>		/* std::for_each */
#include <fstream>			/* std::ifstream */
#include <iostream>	 		/* std::cout, std::endl, std::runtime_error, std::ostream */
#include <iterator>			/* std::istream_iterator */
#include <numeric> 			/* std::acumulate */
#include <regex>			/* std::regex, std::regex_match, std::regex_replace */
#include <string>			/* std::string */
#include <vector>			/* std::vector */
#include <unordered_map>	/* std::unordered_map */

/* Extending the std namespace */
namespace std
{
	/*
	* @brief << operator overload for std::pair<std::string, int>
	*/
	ostream &operator<<(ostream &lhs, const pair<std::string, int> &rhs)
	{ return lhs << '(' << rhs.second << ", " << rhs.first << ')'; }
} /* namespace std */

int
main(const int argc, const char **argv)
{
	/* Check comand line arguments */
	if(2 != argc) {
		throw std::runtime_error("Usage: ./word-counter path/to/file.");
	}

	/* Open input file */
	std::ifstream infile(argv[1]);
	if(!infile.is_open()) {
		throw std::runtime_error("Opening input file failed.");
	}

	/* Read file into map */
	std::unordered_map<std::string, int> word_map;
	std::for_each(	std::istream_iterator<std::string>(infile),
					std::istream_iterator<std::string>(),
					[&word_map, pattern = std::regex("[!?.,;]*(\\w+)[!?.,;]*")] (auto e)
					{
						/* Remove special characters if they are prefixes or suffixes of string */
						if(std::regex_match(e, pattern)) {
							e = std::regex_replace(e, pattern, "$1");
						}

						/* Ingorecase (could also be done with ranged for loop) */
						std::transform(	e.begin(), e.end(),
										e.begin(),
										[] (const auto &c) { return std::tolower(c); });

						/* Add word to map */
						word_map[e] += 1;
					});

	/* Sort word map */
	std::vector<std::pair<std::string, int>> sorted_word_map(word_map.cbegin(), word_map.cend());
	std::sort(	sorted_word_map.begin(), sorted_word_map.end(),
				[] (const auto &lhs, const auto &rhs)
				{ return lhs.second > rhs.second; });

	/* Output word map to console */
	for(const auto &e : sorted_word_map)
	{ std::cout << e << std::endl; }

	/* Get total number of words */
	int total_words{std::accumulate(sorted_word_map.begin(), sorted_word_map.end(),
									0,
									[] (int &sum, const auto &e)
									{ return sum + e.second; })};
	std::cout << "Discint words: " << sorted_word_map.size() << std::endl;
	std::cout << "Total words: " << total_words << std::endl;

	return 0;
}
