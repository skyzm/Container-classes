#include <iostream>
#include <boost/pool/pool_alloc.hpp>
#include <cppunit/ui/text/TextTestRunner.h>
#include "Vector.test.hpp"
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
