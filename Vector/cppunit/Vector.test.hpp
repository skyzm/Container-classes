#ifndef _VECTOR_TEST_HPP_
#define _VECTOR_TEST_HPP_

#include <iostream>
#include <vector>
#include <list>
#include <boost/pool/pool_alloc.hpp>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../include/Vector.hpp"

// <test class declaration>
template <typename T, typename A = std::allocator<T>>
class vector_test_fixture : public CppUnit::TestFixture
{
	public:
		// <implement setUp() and tearDown() for the CppUnit::TestFixture to
		//  use to initialilize and delete vars before and after each test>
		void setUp();
		void tearDown();
	private:
		// <add vector_test_fixture<T, A> to CppUnit::TestSuite>
		CPPUNIT_TEST_SUITE(vector_test_fixture);

		CPPUNIT_TEST_SUITE_END();
		// </add>

		// <tester functions>

		// <constructors>
		void default_constructor_test(void);
		void copy_constructor_test(void);
		void move_constructor_test(void);
		void init_list_consturctor(void);
		// </constructors>

		// <assignment>
		void copy_assignment_test(void);
		void move_assignment_test(void);
		void init_list_assignment_test(void);
		// </assignment>

		// <data access/modification>
		void push_back_test(void);
		void pop_back_test(void);
		void swap_test(void);
		void clear_test(void);
		void find_test(void);
		void access_operator_test(void);
		// </data access/modification>

		// <iterators>
		void iterator_test(void);
		void const_iterator_test(void);
		void reverse_iterator_test(void);
		void const_reverse_iterator_test(void);
		// </iterators>

		// <structure modification>
		void insert_test(void);
		void erase_test(void);
		void range_erase_test(void);
		// </structure modification>

		// </tester functions>

		// <local variables to use durring testing>
		// <NOTE: some fuction tmp variables may be used for testing purposes>
		container::vector<T, A> *v1, *v2, *v3;
		// </variables>

};
// </declaration>

// <conveniance aliases>
template <typename T1>
using pool_alloc_vector = vector_test_fixture<T1, boost::pool_allocator<T1>>;

template <typename T1>
using fast_pool_alloc_vector = container::vector<T1, boost::fast_pool_allocator<T1>>;

template <typename T1>
using pool_alloc_vector_test = vector_test_fixture<T1, boost::pool_allocator<T1>>;

template <typename T1>
using fast_pool_alloc_vector_test = vector_test_fixture<T1, boost::fast_pool_allocator<T1>>;
// </aliases>

// <named test registration - total: 12>
// <std::allocator>
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(vector_test_fixture<double>,
		"container::vector<int, std::allocator<int>>");
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(vector_test_fixture<std::string>,
		"container::vector<std::string, std::allocator<std::string>>");
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(vector_test_fixture<std::list<double>>,
		"container::vector<std::list<int>, std::allocator<std::list<int>>>");
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(vector_test_fixture<container::vector<double>>,
		"container::vector<container::vector<double>>, std::allocator<container::vector<double>>>");

// <boost::pool:allocator>
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(pool_alloc_vector_test<double>,
		"container::vector<int, std::allocator<int>>");
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(pool_alloc_vector_test<std::string>,
		"container::vector<std::string, std::allocator<std::string>>");
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(pool_alloc_vector_test<std::list<double>>,
		"container::vector<std::list<int>, std::allocator<std::list<int>>>");
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(pool_alloc_vector_test<pool_alloc_vector<double>>,
		"container::vector<container::vector<double>>, std::allocator<container::vector<double>>>");

// <boost::fast_pool_allocator>
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(fast_pool_alloc_vector_test<double>,
		"container::vector<int, std::allocator<int>>");
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(fast_pool_alloc_vector_test<std::string>,
		"container::vector<std::string, std::allocator<std::string>>");
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(fast_pool_alloc_vector_test<std::list<double>>,
		"container::vector<std::list<int>, std::allocator<std::list<int>>>");
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(fast_pool_alloc_vector_test<fast_pool_alloc_vector<double>>,
		"container::vector<container::vector<double>>, std::allocator<container::vector<double>>>");
// </registration>

// <test class implementation>

// </implementation>

#endif /* #ifndef _VECTOR_TEST_HPP_ */
