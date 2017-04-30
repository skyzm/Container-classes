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
	struct _rand_gen
	{
		static std::random_device _rd;
		_rand_gen()
			:_engine{_rd()}
		{}

		std::random_device::result_type operator() ()
		{
			return _engine();
		}

		std::mt19937 _engine;
	};

	std::random_device _rand_gen::_rd{};

}

// <test declaration>
template <
		typename T,
		typename A = std::allocator<T>,
		size_t _size = 1000000,
		typename _element_generator = detail::_rand_gen,
		typename _BinaryPredicate = detail::_comp<T>
		>
class vector_test_fixture : public CppUnit::TestFixture
{
	public:
		// <implement setUp() and tearDown() for the CppUnit::TestFixture to
		//  use to initialilize and delete variables before and after each test>
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
		// <NOTE: some local variables may be used in functions for testing purposes>
		container::vector<T, A> *_v1, *_v2, *_v3;
		// </variables>

};
// </declaration>


// <convenience aliases>
using def_vect = vector_test_fixture<double, std::allocator<double>, 30000000>;
using boost_def_vect = vector_test_fixture<double, boost::pool_allocator<double>, 30000000>;
using fast_boost_def_vect = vector_test_fixture<double, boost::fast_pool_allocator<double>, 30000000>;
// </convenience aliases>

// <registration>
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(def_vect, "value_type=double, allocator=std::allocator<double>, size=30,000,000");
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(boost_def_vect, "value_type=double, allocator=boost::pool_allocator<double>, size=30,000,000");
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(fast_boost_def_vect, "value_type=double, allocator=boost::fast_pool_allocator<double>, size=30,000,000");
// </registration>

// <init functions>
template <
		typename T,
		typename A,
		size_t _size,
		typename _element_generator,
		typename _BinaryPredicate
		>
void
vector_test_fixture<T, A, _size, _element_generator, _BinaryPredicate>::setUp()
{
	_v1 = new container::vector<T, A>;
	_v2 = new container::vector<T, A>(_size);
	_v3 = nullptr;
}

template <
		typename T,
		typename A,
		size_t _size,
		typename _element_generator,
		typename _BinaryPredicate
		>
void
vector_test_fixture<T, A, _size, _element_generator, _BinaryPredicate>::tearDown()
{
	delete _v1;
	delete _v2;
	if(nullptr != _v3)
		delete _v3;
}
// </init functions>

// <tester functions>

// <constructors>
template <
		typename T,
		typename A,
		size_t _size,
		typename _element_generator,
		typename _BinaryPredicate
		>
void
vector_test_fixture<T, A, _size, _element_generator, _BinaryPredicate>::default_constructor_test(void)
{
	std::vector<T, A> std_vect(_size);

	CPPUNIT_ASSERT_MESSAGE("constructor test - size[init]", _size == _v2->size());
	CPPUNIT_ASSERT_MESSAGE("constructor test - size", std_vect.size() == _v2->size());
	CPPUNIT_ASSERT_MESSAGE("constructor test - default init ",
			std::equal(_v2->begin(), _v2->end(), std_vect.begin(), _BinaryPredicate{}));
}

template <
		typename T,
		typename A,
		size_t _size,
		typename _element_generator,
		typename _BinaryPredicate
		>
void
vector_test_fixture<T, A, _size, _element_generator, _BinaryPredicate>::copy_constructor_test(void)
{
	std::generate(_v2->begin(), _v2->end(), _element_generator{});

	_v3 = new container::vector<T, A>{*_v2};
	CPPUNIT_ASSERT_MESSAGE("copy constructor - size", _v3->size() == _v2->size());
	CPPUNIT_ASSERT_MESSAGE("copy constructor - contents",
			std::equal(_v2->begin(), _v2->end(), _v3->begin(), _BinaryPredicate{}));
}

template <
		typename T,
		typename A,
		size_t _size,
		typename _element_generator,
		typename _BinaryPredicate
		>
void
vector_test_fixture<T, A, _size, _element_generator, _BinaryPredicate>::move_constructor_test(void)
{
	_element_generator gen{};
	std::vector<T, A> std_vect(_size);
	for(size_t i = 0; i < _size; ++i)
		_v2->at(i) = std_vect[i] = gen();

	CPPUNIT_ASSERT_MESSAGE("move constructor - size[before move]", _v2->size() == std_vect.size());
	CPPUNIT_ASSERT_MESSAGE("move constructor - contents[before move]",
			std::equal(_v2->begin(), _v2->end(), std_vect.begin(), _BinaryPredicate{}));

	_v3 = new container::vector<T, A>{std::move(*_v2)};
	std::vector<T, A> std_vect_move{std::move(std_vect)};

	CPPUNIT_ASSERT_MESSAGE("move constructor - size[after move]", _v3->size() == std_vect_move.size());
	CPPUNIT_ASSERT_MESSAGE("move constructor - contents[after move]",
			std::equal(_v3->begin(), _v3->end(), std_vect_move.begin(), _BinaryPredicate{}));
}

template <
		typename T,
		typename A,
		size_t _size,
		typename _element_generator,
		typename _BinaryPredicate
		>
void
vector_test_fixture<T, A, _size, _element_generator, _BinaryPredicate>::init_list_consturctor_test(void)
{
	// TODO : think of a way to test this
}
// </constructors>

// <assignment>
template <
		typename T,
		typename A,
		size_t _size,
		typename _element_generator,
		typename _BinaryPredicate
		>
void
vector_test_fixture<T, A, _size, _element_generator, _BinaryPredicate>::copy_assignment_test(void)
{
	std::generate(_v2->begin(), _v2->end(), _element_generator{});

	container::vector<T, A> v_copy_assign = *_v2;
	CPPUNIT_ASSERT_MESSAGE("copy assignment - size", v_copy_assign.size() == _v2->size());
	CPPUNIT_ASSERT_MESSAGE("copy assignment - contents",
			std::equal(_v2->begin(), _v2->end(), v_copy_assign.begin(), _BinaryPredicate{}));
}

template <
		typename T,
		typename A,
		size_t _size,
		typename _element_generator,
		typename _BinaryPredicate
		>
void
vector_test_fixture<T, A, _size, _element_generator, _BinaryPredicate>::move_assignment_test(void)
{
	_element_generator gen{};
	std::vector<T, A> std_vect(_size);
	for(size_t i = 0; i < _size; ++i)
		_v2->at(i) = std_vect[i] = gen();

	CPPUNIT_ASSERT_MESSAGE("move assignment - size[before move]", _v2->size() == std_vect.size());
	CPPUNIT_ASSERT_MESSAGE("move constructor - contents[before move]",
			std::equal(_v2->begin(), _v2->end(), std_vect.begin(), _BinaryPredicate{}));

	container::vector<T, A> v_move_assign = std::move(*_v2);
	std::vector<T, A> std_vect_move = std::move(std_vect);

	CPPUNIT_ASSERT_MESSAGE("move constructor - size[after move]", v_move_assign.size() == std_vect_move.size());
	CPPUNIT_ASSERT_MESSAGE("move constructor - contents[after move]",
			std::equal(v_move_assign.begin(), v_move_assign.end(), std_vect_move.begin(), _BinaryPredicate{}));
}

template <
		typename T,
		typename A,
		size_t _size,
		typename _element_generator,
		typename _BinaryPredicate
		>
void
vector_test_fixture<T, A, _size, _element_generator, _BinaryPredicate>::init_list_assignment_test(void)
{
	// TODO : think of a way to test this
}
// </assignment>

// <data access/modification>
template <
		typename T,
		typename A,
		size_t _size,
		typename _element_generator,
		typename _BinaryPredicate
		>
void
vector_test_fixture<T, A, _size, _element_generator, _BinaryPredicate>::push_back_test(void)
{
	_element_generator _rd{};
	std::vector<T, A> std_vect;
	for(size_t i = 0; i < _size; ++i)
	{
		T tmp(_rd());
		_v1->push_back(tmp);
		std_vect.push_back(tmp);
	}

	CPPUNIT_ASSERT_MESSAGE("push_back - size", _v1->size() == std_vect.size());
	CPPUNIT_ASSERT_MESSAGE("push_back - contents",
			std::equal(_v1->begin(), _v1->end(), std_vect.begin(), _BinaryPredicate{}));
}

template <
		typename T,
		typename A,
		size_t _size,
		typename _element_generator,
		typename _BinaryPredicate
		>
void
vector_test_fixture<T, A, _size, _element_generator, _BinaryPredicate>::pop_back_test(void)
{
	_element_generator gen{};
	std::vector<T, A> std_vect(_size);
	for(size_t i = 0; i < _size; ++i)
		_v2->at(i) = std_vect[i] = gen();

	size_t pop_back_count{gen() % _size};
	for(size_t i = 0; i < pop_back_count; ++i)
	{
		_v2->pop_back();
		std_vect.pop_back();
		CPPUNIT_ASSERT_MESSAGE("pop_back - size", _v2->size() == std_vect.size());
	}

	CPPUNIT_ASSERT_MESSAGE("push_back - contents",
			std::equal(_v2->begin(), _v2->end(), std_vect.begin(), _BinaryPredicate{}));
}

template <
		typename T,
		typename A,
		size_t _size,
		typename _element_generator,
		typename _BinaryPredicate
		>
void
vector_test_fixture<T, A, _size, _element_generator, _BinaryPredicate>::swap_test(void)
{
	_element_generator _rd{};
	std::vector<T, A> std_vect1(_size), std_vect2(_size);
	_v3 = new container::vector<T, A>{*_v2};
	for(size_t i = 0; i < _size; ++i)
	{
		T tmp1(_rd()), tmp2(_rd());
		_v2->at(i) = std_vect1[i] = tmp1;
		_v3->at(i) = std_vect2[i] = tmp2;
	}
	
	CPPUNIT_ASSERT_MESSAGE("swap - size[before swap]", _v2->size() == std_vect1.size());
	CPPUNIT_ASSERT_MESSAGE("swap - contents[before swap]",
			std::equal(_v2->begin(), _v2->end(), std_vect1.begin(), _BinaryPredicate{}));

	CPPUNIT_ASSERT_MESSAGE("swap - size[before swap]", _v3->size() == std_vect2.size());
	CPPUNIT_ASSERT_MESSAGE("swap - contents[before swap]",
			std::equal(_v3->begin(), _v3->end(), std_vect2.begin(), _BinaryPredicate{}));

	_v2->swap(*_v3);

	CPPUNIT_ASSERT_MESSAGE("swap - size[after swap]", _v2->size() == std_vect2.size());
	CPPUNIT_ASSERT_MESSAGE("swap - contents[after swap]",
			std::equal(_v2->begin(), _v2->end(), std_vect2.begin(), _BinaryPredicate{}));

	CPPUNIT_ASSERT_MESSAGE("swap - size[after swap]", _v3->size() == std_vect1.size());
	CPPUNIT_ASSERT_MESSAGE("swap - contents[after swap]",
			std::equal(_v3->begin(), _v3->end(), std_vect1.begin(), _BinaryPredicate{}));
}

template <
		typename T,
		typename A,
		size_t _size,
		typename _element_generator,
		typename _BinaryPredicate
		>
void
vector_test_fixture<T, A, _size, _element_generator, _BinaryPredicate>::clear_test(void)
{
	std::vector<T, A> std_vect(_size);
	CPPUNIT_ASSERT_MESSAGE("clear - size[before clear]", _v2->size() == std_vect.size());
	CPPUNIT_ASSERT_MESSAGE("clear - size[before clear]", _size == _v2->size());

	_v2->clear();
	std_vect.clear();
	CPPUNIT_ASSERT_MESSAGE("clear - size[after clear]", _v2->size() == std_vect.size());
	CPPUNIT_ASSERT_MESSAGE("clear - size[after clear]", 0 == _v2->size());
}

template <
		typename T,
		typename A,
		size_t _size,
		typename _element_generator,
		typename _BinaryPredicate
		>
void
vector_test_fixture<T, A, _size, _element_generator, _BinaryPredicate>::access_operator_test(void)
{
	// TODO : implement
}
// </data access/modification>

// <iterators>
template <
		typename T,
		typename A,
		size_t _size,
		typename _element_generator,
		typename _BinaryPredicate
		>
void
vector_test_fixture<T, A, _size, _element_generator, _BinaryPredicate>::iterator_test(void)
{
	// TODO : implement
}

template <
		typename T,
		typename A,
		size_t _size,
		typename _element_generator,
		typename _BinaryPredicate
		>
void
vector_test_fixture<T, A, _size, _element_generator, _BinaryPredicate>::const_iterator_test(void)
{
	// TODO : implement
}

template <
		typename T,
		typename A,
		size_t _size,
		typename _element_generator,
		typename _BinaryPredicate
		>
void
vector_test_fixture<T, A, _size, _element_generator, _BinaryPredicate>::reverse_iterator_test(void)
{
	// TODO : implement
}

template <
		typename T,
		typename A,
		size_t _size,
		typename _element_generator,
		typename _BinaryPredicate
		>
void
vector_test_fixture<T, A, _size, _element_generator, _BinaryPredicate>::const_reverse_iterator_test(void)
{
	// TODO : implement
}
// </iterators>

// <structure modification>
template <
		typename T,
		typename A,
		size_t _size,
		typename _element_generator,
		typename _BinaryPredicate
		>
void
vector_test_fixture<T, A, _size, _element_generator, _BinaryPredicate>::insert_test(void)
{
	// TODO : implement
}

template <
		typename T,
		typename A,
		size_t _size,
		typename _element_generator,
		typename _BinaryPredicate
		>
void
vector_test_fixture<T, A, _size, _element_generator, _BinaryPredicate>::erase_test(void)
{
	// TODO : implement
}

template <
		typename T,
		typename A,
		size_t _size,
		typename _element_generator,
		typename _BinaryPredicate
		>
void
vector_test_fixture<T, A, _size, _element_generator, _BinaryPredicate>::range_erase_test(void)
{
	// TODO : implement
}
// </structure modification>

// </tester functions>

// </implementation>

#endif /* #ifndef _VECTOR_TEST_HPP_ */