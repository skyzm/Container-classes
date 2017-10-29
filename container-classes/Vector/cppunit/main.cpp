// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// <author info>
// 	<name>
// 		Stefan Pantic 
// 	<github>
// 		https://github.com/syIar/Container-classes
// 	<university>
// 		University of Belgrade, Faculty of Mathematics, second year student
// 	<year>
// 		Second
// 	<email>
// 		stefanpantic13@gmail.com
// </author info>
// 
// <description>
// Here, I'm testing my template vector class using the CppUnit framework.
// The CppUnit::TextTestRunner class uses the factory pattern to fetch 
// registered tests from the named test registry, instance, and run them.
// The results will be printed to the console.
// 
// The tester class has been made so that it can be used to test the vector
// of any type, with any allocator, and of any size.
// NOTE : the element generator and comparator may need to be provided if
// the default ones do not apply to the desired type.
// </description>
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#include <iostream>
#include <boost/pool/pool_alloc.hpp>
#include <cppunit/ui/text/TextTestRunner.h>
#include "vector.test.hpp"
#include "test_info/info.hpp"

int
main (void)
{
	CppUnit::TextTestRunner runner1, runner2, runner3;

	test_info("double", "std::allocator", 30000000);
	runner1.addTest(CppUnit::TestFactoryRegistry::getRegistry("value_type=double, allocator=std::allocator<double>, size=30,000,000").makeTest());
	runner1.run();

	test_info("double", "boost::pool_allocator", 30000000);
	runner2.addTest(CppUnit::TestFactoryRegistry::getRegistry("value_type=double, allocator=boost::pool_allocator<double>, size=30,000,000").makeTest());
	runner2.run();

	test_info("double", "boost::fast_pool_allocator", 30000000);
	runner3.addTest(CppUnit::TestFactoryRegistry::getRegistry("value_type=double, allocator=boost::fast_pool_allocator<double>, size=30,000,000").makeTest());
	runner3.run();

	return 0;
}
