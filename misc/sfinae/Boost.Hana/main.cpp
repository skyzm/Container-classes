/*
* Author: Stefan Pantic.
* GitHub: https://www.github.com/stefanpantic
*
* Description: Example usage of boost::hana::is_valid.
* NOTE: C++14 or higher requred.
*/

#include <boost/hana.hpp> 	/* boost::hana */
#include <iostream> 		/* std::cout, std::endl */
#include <string>			/* std::string */

/* Type %Foo with a serialize member function */
struct Foo
{
	std::string serialize(void) const
	{ return "Foo::serialize()"; }
}; /* struct Foo */

/* Type %Bar without a serialize member function */
struct Bar
{}; /* struct Bar */

/* Extending the std namespace with a to_string overload for %Bar */
namespace std
{
	string to_string(const Bar&)
	{ return "std::to_string(Bar)"; }
} /* namespace std */

/* Check if object has a serialize member function */
auto has_serialize{boost::hana::is_valid([] (auto && e) -> decltype(e.serialize()) {})};

/* Serialize any type */
template<class T>
std::string serialize(T &&obj)
{
	/* TODO: Read documentation for Boost.Hana */
	return boost::hana::if_(has_serialize(obj),
							[] (auto &&e) { return e.serialize(); },
							[] (auto &&e) { return std::to_string(e); }
							)(obj);
}

/* Main function */
int
main(void)
{
	/* Declare some variables */
	Foo foo;
	Bar bar;

	/* Serialize @foo and @bar */
	std::cout << serialize(foo) << std::endl;
	std::cout << serialize(bar) << std::endl;

	return 0;
}
