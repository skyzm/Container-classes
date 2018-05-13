/*
* Author: Stefan Pantic.
* GitHub: https://www.github.com/stefanpantic
*
* Description: Example usage of std::variant.
* NOTE: C++17 or higher requred.
*/

#include <iostream>	/* std::cin, std::cout, std::endl, std::ostream */
#include <map>		/* std::map */
#include <string>	/* std::string */
#include <variant>	/* std::variant, std::visit */

/*
* @brief Visitor for variant<int,string,map<string,int>>.
*
* Uses multiple overloads of call operator to exibit diferent behaviour
* based on variant state.
*/
struct Visitor
{
	void operator()(const int &x) const
	{ std::cout << "[Visitor]Variant contains int: " << x << std::endl; }

	void operator()(const std::string &s) const
	{ std::cout << "[Visitor]Variant contains string: \"" << s << '\"' << std::endl; }

	void operator()(const std::map<std::string, int> &m) const
	{
		std::cout << "[Visitor]Variant contains map: " << std::endl;
		std::cout << "{" << std::endl;
		for(const auto &e : m) {
			std::cout << "\t\"" << e.first << '\"' << " : " << e.second << ',' << std::endl;
		}
		std::cout << "}" << std::endl;;
	}
};

int
main(void)
{
	/* Construct an empty variant */
	std::variant<int, std::string, std::map<std::string, int>> v;

	/* Set variant state to int */
	v = 420;

	/* Visit variant */
	std::visit(Visitor(), v);

	/* Set variant state to string */
	v = "N.M is the Zodiac killer";

	/* Visit variant */
	std::visit(Visitor(), v);

	/* Create a simple map */
	std::map<std::string, int> m{
		{"C++", 100},
		{"Java", 68},
		{"C", 82},
		{"Python", 87}
	};

	/* Set variant state to map<string, int> */
	v = m;

	/* Visit variant */
	std::visit(Visitor(), v);

	/* Varant can also bi visited with lambda */
	v = 100;
	std::visit([](auto &&e) {
			using T = std::decay_t<decltype(e)>;
			if constexpr(std::is_same_v<int, T>) {
				std::cout << "[Closure]Variant contains int: " << e << std::endl;
			}}, v);

	return 0;
}
