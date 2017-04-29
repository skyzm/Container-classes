#ifndef _VECTOR_TEST_HPP_
#define _VECTOR_TEST_HPP_

#include <iostream>
#include <vector>
#include <list>
#include <random>
#include <boost/pool/pool_alloc.hpp>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../include/Vector.hpp"

namespace detail
{

	// <default comparator>
	template <typename T1>
	struct _comp
	{
		bool operator()(const T1 &_a, const T1 &_b)
		{
			return (_a == _b);
		}
	};

	// <default element generator>
	struct random_number_device
	{
		random_number_device()
			:_engine{1}
		{}

		std::random_device::result_type operator() ()
		{
			return _engine();
		}

		std::mt19937 _engine;
	};

}

// <test declaration>
template <
		typename T,
		typename A = std::allocator<T>,
		size_t _size = 1000000,
		typename _BinaryPredicate = detail::_comp<T>,
		typename _Rand = detail::random_number_device
		>
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

		// <add test methods>
		CPPUNIT_TEST(default_constructor_test);
		CPPUNIT_TEST(copy_constructor_test);
		CPPUNIT_TEST(move_constructor_test);
		CPPUNIT_TEST(init_list_consturctor_test);
		CPPUNIT_TEST(copy_assignment_test);
		CPPUNIT_TEST(move_assignment_test);
		CPPUNIT_TEST(init_list_assignment_test);
		CPPUNIT_TEST(push_back_test);
		CPPUNIT_TEST(pop_back_test);
		CPPUNIT_TEST(swap_test);
		CPPUNIT_TEST(clear_test);
		CPPUNIT_TEST(find_test);
		CPPUNIT_TEST(access_operator_test);
		CPPUNIT_TEST(iterator_test);
		CPPUNIT_TEST(const_iterator_test);
		CPPUNIT_TEST(reverse_iterator_test);
		CPPUNIT_TEST(const_reverse_iterator_test);
		CPPUNIT_TEST(insert_test);
		CPPUNIT_TEST(erase_test);
		CPPUNIT_TEST(range_erase_test);

		CPPUNIT_TEST_SUITE_END();
		// </add>

		// <tester functions>

		// <constructors>
		void default_constructor_test(void);
		void copy_constructor_test(void);
		void move_constructor_test(void);
		void init_list_consturctor_test(void);
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

// <registration>

// <convenience typedefs>

using def_vect = vector_test_fixture<double, std::allocator<double>, 30000000>;
using boost_def_vect = vector_test_fixture<double, boost::pool_allocator<double>, 30000000>;
using fast_boost_def_vect = vector_test_fixture<double, boost::fast_pool_allocator<double>, 30000000>;

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(def_vect, "value_type=double, allocator=std::allocator<double>, size=30,000,000");
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(boost_def_vect, "value_type=double, allocator=boost::pool_allocator<double>, size=30,000,000");
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(fast_boost_def_vect, "value_type=double, allocator=boost::fast_pool_allocator<double>, size=30,000,000");

// </convenience typedefs>

// </registration>

// <init functions>
template <
		typename T,
		typename A,
		size_t _size,
		typename _BinaryPredicate,
		typename _Rand
		>
void
vector_test_fixture<T, A, _size, _BinaryPredicate, _Rand>::setUp()
{
	v1 = new container::vector<T, A>;
	v2 = new container::vector<T, A>(_size);
	//v3 = new container::vector<T, A>{300000000};
}

template <
		typename T,
		typename A,
		size_t _size,
		typename _BinaryPredicate,
		typename _Rand
		>
void
vector_test_fixture<T, A, _size, _BinaryPredicate, _Rand>::tearDown()
{
	delete v1;
	delete v2;
	//delete v3;
}
// </init functions>

// <tester functions>

// <constructors>
template <
		typename T,
		typename A,
		size_t _size,
		typename _BinaryPredicate,
		typename _Rand
		>
void
vector_test_fixture<T, A, _size, _BinaryPredicate, _Rand>::default_constructor_test(void)
{
	std::vector<T, A> std_vect(_size);

	CPPUNIT_ASSERT_MESSAGE("constructor test ", _size == v2->size());
	CPPUNIT_ASSERT_MESSAGE("constructor test", std_vect.size() == v2->size());
	CPPUNIT_ASSERT_MESSAGE("default init test",
			std::equal(v2->begin(), v2->end(), std_vect.begin(), _BinaryPredicate{}));
}

template <
		typename T,
		typename A,
		size_t _size,
		typename _BinaryPredicate,
		typename _Rand
		>
void
vector_test_fixture<T, A, _size, _BinaryPredicate, _Rand>::copy_constructor_test(void)
{
	std::generate(v2->begin(), v2->end(), _Rand{});

	container::vector<T, A> v_copy(*v2);
	CPPUNIT_ASSERT_MESSAGE("copy constructor", v_copy.size() == v2->size());
	CPPUNIT_ASSERT_MESSAGE("copy constructor",
			std::equal(v2->begin(), v2->end(), v_copy.begin(), _BinaryPredicate{}));
}

template <
		typename T,
		typename A,
		size_t _size,
		typename _BinaryPredicate,
		typename _Rand
		>
void
vector_test_fixture<T, A, _size, _BinaryPredicate, _Rand>::move_constructor_test(void)
{
	// TODO : implement
}

template <
		typename T,
		typename A,
		size_t _size,
		typename _BinaryPredicate,
		typename _Rand
		>
void
vector_test_fixture<T, A, _size, _BinaryPredicate, _Rand>::init_list_consturctor_test(void)
{
	// TODO : implement
}
// </constructors>

// <assignment>
template <
		typename T,
		typename A,
		size_t _size,
		typename _BinaryPredicate,
		typename _Rand
		>
void
vector_test_fixture<T, A, _size, _BinaryPredicate, _Rand>::copy_assignment_test(void)
{
	std::generate(v2->begin(), v2->end(), _Rand{});

	container::vector<T, A> v_copy = *v2;
	CPPUNIT_ASSERT_MESSAGE("copy assignment", v_copy.size() == v2->size());
	CPPUNIT_ASSERT_MESSAGE("copy assignment",
			std::equal(v2->begin(), v2->end(), v_copy.begin(), _BinaryPredicate{}));
}

template <
		typename T,
		typename A,
		size_t _size,
		typename _BinaryPredicate,
		typename _Rand
		>
void
vector_test_fixture<T, A, _size, _BinaryPredicate, _Rand>::move_assignment_test(void)
{
	// TODO : implement
}

template <
		typename T,
		typename A,
		size_t _size,
		typename _BinaryPredicate,
		typename _Rand
		>
void
vector_test_fixture<T, A, _size, _BinaryPredicate, _Rand>::init_list_assignment_test(void)
{
	// TODO : implement
}
// </assignment>

// <data access/modification>
template <
		typename T,
		typename A,
		size_t _size,
		typename _BinaryPredicate,
		typename _Rand
		>
void
vector_test_fixture<T, A, _size, _BinaryPredicate, _Rand>::push_back_test(void)
{
	// TODO : implement
}

template <
		typename T,
		typename A,
		size_t _size,
		typename _BinaryPredicate,
		typename _Rand
		>
void
vector_test_fixture<T, A, _size, _BinaryPredicate, _Rand>::pop_back_test(void)
{
	// TODO : implement
}

template <
		typename T,
		typename A,
		size_t _size,
		typename _BinaryPredicate,
		typename _Rand
		>
void
vector_test_fixture<T, A, _size, _BinaryPredicate, _Rand>::swap_test(void)
{
	// TODO : implement
}

template <
		typename T,
		typename A,
		size_t _size,
		typename _BinaryPredicate,
		typename _Rand
		>
void
vector_test_fixture<T, A, _size, _BinaryPredicate, _Rand>::clear_test(void)
{
	// TODO : implement
}

template <
		typename T,
		typename A,
		size_t _size,
		typename _BinaryPredicate,
		typename _Rand
		>
void
vector_test_fixture<T, A, _size, _BinaryPredicate, _Rand>::find_test(void)
{
	// TODO : implement
}

template <
		typename T,
		typename A,
		size_t _size,
		typename _BinaryPredicate,
		typename _Rand
		>
void
vector_test_fixture<T, A, _size, _BinaryPredicate, _Rand>::access_operator_test(void)
{
	// TODO : implement
}
// </data access/modification>

// <iterators>
template <
		typename T,
		typename A,
		size_t _size,
		typename _BinaryPredicate,
		typename _Rand
		>
void
vector_test_fixture<T, A, _size, _BinaryPredicate, _Rand>::iterator_test(void)
{
	// TODO : implement
}

template <
		typename T,
		typename A,
		size_t _size,
		typename _BinaryPredicate,
		typename _Rand
		>
void
vector_test_fixture<T, A, _size, _BinaryPredicate, _Rand>::const_iterator_test(void)
{
	// TODO : implement
}

template <
		typename T,
		typename A,
		size_t _size,
		typename _BinaryPredicate,
		typename _Rand
		>
void
vector_test_fixture<T, A, _size, _BinaryPredicate, _Rand>::reverse_iterator_test(void)
{
	// TODO : implement
}

template <
		typename T,
		typename A,
		size_t _size,
		typename _BinaryPredicate,
		typename _Rand
		>
void
vector_test_fixture<T, A, _size, _BinaryPredicate, _Rand>::const_reverse_iterator_test(void)
{
	// TODO : implement
}
// </iterators>

// <structure modification>
template <
		typename T,
		typename A,
		size_t _size,
		typename _BinaryPredicate,
		typename _Rand
		>
void
vector_test_fixture<T, A, _size, _BinaryPredicate, _Rand>::insert_test(void)
{
	// TODO : implement
}

template <
		typename T,
		typename A,
		size_t _size,
		typename _BinaryPredicate,
		typename _Rand
		>
void
vector_test_fixture<T, A, _size, _BinaryPredicate, _Rand>::erase_test(void)
{
	// TODO : implement
}

template <
		typename T,
		typename A,
		size_t _size,
		typename _BinaryPredicate,
		typename _Rand
		>
void
vector_test_fixture<T, A, _size, _BinaryPredicate, _Rand>::range_erase_test(void)
{
	// TODO : implement
}
// </structure modification>

// </tester functions>

// </implementation>

#endif /* #ifndef _VECTOR_TEST_HPP_ */
