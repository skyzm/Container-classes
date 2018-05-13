/*
* Author: Stefan Pantic.
* GitHub: https://www.github.com/stefanpantic
*
* Description: Simple example of templated min() function.
* NOTE: C++14 or higher requred.
*/

#include <iostream> 	/* std::cout, std::endl */
#include <string>		/* std::string */
#include <utility>		/* std::forward */
#include <functional>	/* std::less */

/*
* @brief Templated min function.
*
* @param T Type of values to compare.
* @param Comparator Comparator object to use. Defaults to std::less<T>.
*
* @returns decltype(auto) Return type will be deduced based on T.
*/
template<
	typename T,
	typename Comparator = std::less<T>
		>
decltype(auto) min(T &&lhs, T &&rhs, Comparator c = Comparator())
{ return (c(lhs, rhs)) ? lhs : rhs; }

int
main(void)
{
	/* Pass by rvalue reference. */
	std::cout << min(3.145, 2.718) << std::endl;

	/* Pass by rvalue reference. */
	std::cout << min<char>('x', 'y') << std::endl;

	/* Pass by const reference. */
	std::string lhs{"C++"}, rhs{"C"};
	std::cout << min(lhs, rhs) << std::endl;

	return 0;
}
