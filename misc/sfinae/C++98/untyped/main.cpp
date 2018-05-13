/*
* Author: Stefan Pantic.
* GitHub: https://www.github.com/stefanpantic
*
* Description: Example showcasing weak typeness of variadic argument functions.
*/

#include <iostream>	/* std::cout, std::endl */

/*
* @brief A templated function that takes a const reference to T.
*/
template<class T>
void foo(const T&)
{ std::cout << "foo(T&&)" << std::endl; }

/*
* @brief A variadic argument function.
*/
void foo(...)
{ std::cout << "foo(...)" << std::endl; }

int
main(void)
{
	/* Templated function will get precedence */
	foo(1);

	/* Variadic argument function will get called */
	foo(2.718, "string", 3.14);

	return 0;
}
