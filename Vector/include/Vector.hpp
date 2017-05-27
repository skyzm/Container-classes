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
// Learning C++ by usage.
// This is my attempt to implement the std::vector class.
// The code will constantly evolve as I learn new things and apply them.
// So far the class has been tested using the CppUnit framework.
// </description>
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#ifndef _VECTOR_HPP_

#include <iostream>
#include <iterator>
#include <memory>

namespace container
{

// <declaration>
	template <typename T, typename A = std::allocator<T>>
	class vector
	{
		public:
			// <typedefs>
			typedef A allocator_type;
			typedef typename A::size_type size_type;
			typedef typename A::value_type value_type;
			typedef typename A::reference reference;
			typedef typename A::const_reference const_reference;
			typedef typename A::pointer pointer;
			// </typedefs>

			// <iterator - inner class>
			class iterator : public std::iterator<std::random_access_iterator_tag, T>
			{
				public:
					// <typedefs>
					typedef typename A::value_type value_type;
					typedef typename A::reference reference;
					typedef typename A::pointer pointer;
					typedef typename A::difference_type difference_type;
					// </typedefs>

					// <friends>
					friend class vector<T, A>;
					// </friends>

					// <constructors>
					iterator(T *_p = nullptr);
					iterator(const iterator &_it);
					iterator(iterator &&_it);
					~iterator();
					// </constructors>

					// <iteratrion functions>
					iterator& next();
					iterator& prev();
					// </iteration functions>

					// <assignment operators>
					iterator& operator=(const iterator &_it);
					iterator& operator=(iterator &&_it);
					// </assignment operators>

					// <relation operators>
					bool operator==(const iterator &_it) const;
					bool operator!=(const iterator &_it) const;
					bool operator<(const iterator &_it) const;
					bool operator<=(const iterator &_it) const;
					bool operator>(const iterator &_it) const;
					bool operator>=(const iterator &_it) const;
					// </relation operators>

					// <increment operators>
					iterator& operator++();
					iterator operator++(int);
					iterator& operator--();
					iterator operator--(int);
					iterator operator+(const size_type &_d) const;
					iterator& operator+=(const size_type &_d);
					iterator operator-(const size_type &_d) const;
					iterator& operator-=(const size_type &_d);
					difference_type operator-(const iterator &_it) const;
					// </increment operators>

					// <reference operators>
					reference operator*();
					pointer operator->();
					// </reference operators>
				private:
					pointer _current;
			};
			// </iterator - inner class>

			// <const_iterator - inner class>
			class const_iterator : public std::iterator<std::random_access_iterator_tag, const T>
			{
				public:
					// <typedefs>
					typedef typename A::value_type value_type;
					typedef typename A::const_reference reference;
					typedef typename A::difference_type difference_type;
					typedef const T* pointer;
					// </typedefs>

					// <constructors>
					const_iterator(T *_p = nullptr);
					const_iterator(const const_iterator &_cit);
					const_iterator(const iterator &_cit);
					const_iterator(const_iterator &&_cit);
					~const_iterator();
					// </constructors>

					// <iteration functions>
					const_iterator& next();
					const_iterator& prev();
					// </iteration functions>

					// <assignment operators>
					const_iterator& operator=(const const_iterator &_it);
					const_iterator& operator=(const iterator &_it);
					const_iterator& operator=(const_iterator &&_it);
					// </assignment operators>

					// <relation operators>
					bool operator==(const const_iterator &_it) const;
					bool operator!=(const const_iterator &_it) const;
					bool operator<(const const_iterator &_it) const;
					bool operator<=(const const_iterator &_it) const;
					bool operator>(const const_iterator &_it) const;
					bool operator>=(const const_iterator &_it) const;
					// </relation operators>

					// <increment operators>
					const_iterator& operator++();
					const_iterator operator++(int);
					const_iterator& operator--();
					const_iterator operator--(int);
					const_iterator operator+(const size_type &_d) const;
					const_iterator& operator+=(const size_type &_d);
					const_iterator operator-(const size_type &_d) const;
					const_iterator& operator-=(const size_type &_d);
					difference_type operator-(const const_iterator &_it) const;
					// </increment operators>

					// <reference operators>
					reference operator*() const;
					pointer operator->() const;
					// </reference operators>
				private:
					pointer _current;

			};
			// </const_iterator - inner class>

			// <reverse iterators>
			typedef std::reverse_iterator<iterator> reverse_iterator;
			typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
			// </reverse iterators>

			// <constructors>
			vector(const size_type &_s = 0, const T &_t = T());
			vector(const vector<T, A> &_v);
			vector(vector &&_v);
			vector(const std::initializer_list<T> &_l);
			~vector();
			// </constructors>

			// <assignment operators>
			vector<T, A>& operator=(const vector<T, A> &_v);
			vector<T, A>& operator=(vector &&_v);
			vector<T, A>& operator=(const std::initializer_list<T> &_l);
			// </assignment operators>

			// <data access/modification>
			void push_back(const T &_t = T());
			void push_back(T &&_t);
			void pop_back(void);
			const_reference front(void) const;
			const_reference back(void) const;
			void swap(vector<T, A> &_v);
			void clear(void);
			iterator find(const T &_t);
			const_iterator find(const T &_t) const;
			inline reference operator[](const size_type &_p) { return _data[_p]; }
			inline reference at(const size_type &_p) { return _data[_p]; };
			inline const_reference operator[](const size_type &_p) const { return _data[_p]; }
			inline const_reference at(const size_type &_p) const { return _data[_p]; }
			// </data access/modification>

			// <iterators>
			// <forward iterators>
			iterator begin();
			const_iterator begin() const;
			const_iterator cbegin() const;
			iterator end();
			const_iterator end() const;
			const_iterator cend() const;
			// <reverse iterators>
			reverse_iterator rbegin();
			const_reverse_iterator rbegin() const;
			const_reverse_iterator crbegin() const;
			reverse_iterator rend();
			const_reverse_iterator rend() const;
			const_reverse_iterator crend() const;
			// <structure modification>
			iterator insert(iterator &_it, const T &_t);
			iterator insert(iterator &&_it, const T &_t);
			iterator insert(iterator &_it, T &&_t);
			iterator insert(iterator &&_it, T &&_t);
			iterator erase(iterator &_it);
			iterator erase(iterator &&_it);
			iterator erase(iterator &_b, iterator &_e);
			iterator erase(iterator &&_b, iterator &&_e);
			// </iterators>

			inline size_type size(void) const { return _size; }
			inline bool empty() const { return (0 == _size) ? true : false; }

		private:
			// <data>
			allocator_type _allocator;
			value_type *_data;
			size_type _size;
			size_type _alloc;
			// </data>
	};
// </declaration>

// <implementation>

// <iterator implementation>

	// <iterator - constructors>

	// <default constructor>
	template <typename T, typename A>
	vector<T, A>::iterator::iterator(T *_p)
	:_current{_p}
	{}

	// <copy constructor>
	template <typename T, typename A>
	vector<T, A>::iterator::iterator(const iterator &_it)
	:_current{_it._current}
	{}

	// <move constructor>
	template <typename T, typename A>
	vector<T, A>::iterator::iterator(iterator &&_it)
	:_current{_it._current}
	{
		_it._current = nullptr;
	}

	// <deconstructor>
	template<typename T, typename A>
	vector<T, A>::iterator::~iterator()
	{
		this->_current = nullptr;
	}
	// </iterator - constructors>

	// <iteration functions>

	// <move forwards>
	template <typename T, typename A>
	typename vector<T, A>::iterator&
	vector<T, A>::iterator::next()
	{
		++_current;

		return *this;
	}

	// <move backwards>
	template <typename T, typename A>
	typename vector<T, A>::iterator&
	vector<T, A>::iterator::prev()
	{
		--_current;

		return *this;
	}
	// </iteration functions>

	// <iterator - assignment operators>

	// <copy assignment>
	template<typename T, typename A>
	typename vector<T, A>::iterator&
	vector<T, A>::iterator::operator=(const iterator &_it)
	{
		_current = _it._current;
		return *this;
	}

	// <move assignment>
	template <typename T, typename A>
	typename vector<T, A>::iterator&
	vector<T, A>::iterator::operator=(iterator &&_it)
	{
		_current = _it._current;
		_it._current = nullptr;

		return *this;
	}
	// </iterator - assingnment operators>

	// <iterator - relation operators>
	template<typename T, typename A>
	bool
	vector<T, A>::iterator::operator==(const iterator &_it) const
	{
		return (_current == _it._current);
	}

	template<typename T, typename A>
	bool
	vector<T, A>::iterator::operator!=(const iterator &_it) const
	{
		return !(*this == _it);
	}

	template <typename T, typename A>
	bool
	vector<T, A>::iterator::operator<(const iterator &_it) const
	{
		return (_current < _it._current);
	}

	template <typename T, typename A>
	bool
	vector<T, A>::iterator::operator<=(const iterator &_it) const
	{
		return (_current <= _it._current);
	}

	template <typename T, typename A>
	bool
	vector<T, A>::iterator::operator>(const iterator &_it) const
	{
		return (_current > _it._current);
	}

	template<typename T, typename A>
	bool
	vector<T, A>::iterator::operator>=(const iterator &_it) const
	{
		return (_current >= _it._current);
	}
	// </iterator - relation operators>

	// <iterator - increment operators>

	// <preincrement operator>
	template<typename T, typename A>
	typename vector<T, A>::iterator&
	vector<T, A>::iterator::operator++()
	{
		this->next();
		return *this;
	}

	// <postincrement operator>
	template<typename T, typename A>
	typename vector<T, A>::iterator
	vector<T, A>::iterator::operator++(int)
	{
		iterator ret{*this};
		this->next();
		return ret;
	}

	// <predecrement operator>
	template<typename T, typename A>
	typename vector<T, A>::iterator&
	vector<T, A>::iterator::operator--()
	{
		this->prev();
		return *this;
	}

	// <postdecrement operator>
	template<typename T, typename A>
	typename vector<T, A>::iterator
	vector<T, A>::iterator::operator--(int)
	{
		iterator ret{*this};
		this->prev();
		return ret;
	}

	// <addition operators>
	template <typename T, typename A>
	typename vector<T, A>::iterator
	vector<T, A>::iterator::operator+(const size_type &_d) const
	{
		return vector<T, A>::iterator{_current + _d};
	}

	template <typename T, typename A>
	typename vector<T, A>::iterator&
	vector<T, A>::iterator::operator+=(const size_type &_d)
	{
		return *this = *this + _d;
	}

	// <subtraction operators>
	template <typename T, typename A>
	typename vector<T, A>::iterator
	vector<T, A>::iterator::operator-(const size_type &_d) const
	{
		return vector<T, A>::iterator{_current - _d};
	}

	template <typename T, typename A>
	typename vector<T, A>::iterator&
	vector<T, A>::iterator::operator-=(const size_type &_d)
	{
		return *this = *this - _d;
	}

	// <difference operator>
	template <typename T, typename A>
	typename vector<T, A>::iterator::difference_type
	vector<T, A>::iterator::operator-(const iterator &_it) const
	{
		return _current - _it._current;
	}
	// </iterator - increment operators>

	// <iterator - reference operators>

	// <dereference operator>
	template <typename T, typename A>
	typename vector<T, A>::iterator::reference
	vector<T, A>::iterator::operator*()
	{
		return *_current;
	}

	// <reference operator>
	template <typename T, typename A>
	typename vector<T, A>::iterator::pointer
	vector<T, A>::iterator::operator->()
	{
		return _current;
	}
	// </iterator - reference operators>

// </iterator implemantation>


// <const_iterator implementation>

	// <const_iterator - constructors>

	// <default constructor>
	template <typename T, typename A>
	vector<T, A>::const_iterator::const_iterator(T *_p)
	:_current{_p}
	{}

	// <copy constructor>
	template <typename T, typename A>
	vector<T, A>::const_iterator::const_iterator(const const_iterator &_cit)
	:_current{_cit._current}
	{}

	// <convert constructor>
	template <typename T, typename A>
	vector<T, A>::const_iterator::const_iterator(const iterator &_it)
	:_current{_it._current}
	{}

	// <move constructor>
	template <typename T, typename A>
	vector<T, A>::const_iterator::const_iterator(const_iterator &&_cit)
	:_current{_cit._current}
	{
		_cit._current = nullptr;
	}

	// <deconstructor>
	template <typename T, typename A>
	vector<T, A>::const_iterator::~const_iterator()
	{
		_current = nullptr;
	}
	// </const_iterator - constructors>

	// <const_iterator -iteration functions>

	// <move forwards>
	template <typename T, typename A>
	typename vector<T, A>::const_iterator&
	vector<T, A>::const_iterator::next()
	{
		++_current;

		return *this;
	}

	// <move backwards>
	template <typename T, typename A>
	typename vector<T, A>::const_iterator&
	vector<T, A>::const_iterator::prev()
	{
		--_current;

		return *this;
	}
	// </const_iterator - iteration functions>

	// <const_iterator - assignment operators>

	// <copy assignment>
	template <typename T, typename A>
	typename vector<T, A>::const_iterator&
	vector<T, A>::const_iterator::operator=(const const_iterator &_it)
	{
		_current = _it._current;

		return *this;
	}

	// <convert assignment>
	template <typename T, typename A>
	typename vector<T, A>::const_iterator&
	vector<T, A>::const_iterator::operator=(const iterator& _it)
	{
		_current = _it._current;

		return *this;
	}

	// <move assignment>
	template <typename T, typename A>
	typename vector<T, A>::const_iterator&
	vector<T, A>::const_iterator::operator=(const_iterator &&_it)
	{
		_current = _it._current;
		_it._current = nullptr;

		return *this;
	}
	// </const_iterator - assignment operators>

	// <const_iterator - relation operators>
	template <typename T, typename A>
	bool
	vector<T, A>::const_iterator::operator==(const const_iterator &_it) const
	{
		return (_current == _it._current);
	}

	template <typename T, typename A>
	bool
	vector<T, A>::const_iterator::operator!=(const const_iterator &_it) const
	{
		return !(*this == _it);
	}

	template <typename T, typename A>
	bool
	vector<T, A>::const_iterator::operator<(const const_iterator &_it) const
	{
		return (_current < _it._current);
	}

	template <typename T, typename A>
	bool
	vector<T, A>::const_iterator::operator<=(const const_iterator &_it) const
	{
		return (_current <= _it._current);
	}

	template <typename T, typename A>
	bool
	vector<T, A>::const_iterator::operator>(const const_iterator &_it) const
	{
		//return (_current > _it._current);
		return !(*this <= _it);
	}

	template<typename T, typename A>
	bool
	vector<T, A>::const_iterator::operator>=(const const_iterator &_it) const
	{
		//return (_current >= _it._current);
		return !(*this < _it);
	}
	// </const_iterator - relation operators>

	// <const_iterator - increment operators>

	// <preincrement operator>
	template <typename T, typename A>
	typename vector<T, A>::const_iterator&
	vector<T, A>::const_iterator::operator++()
	{
		this->next();
		return *this;
	}

	// <postincrement operator>
	template <typename T, typename A>
	typename vector<T, A>::const_iterator
	vector<T, A>::const_iterator::operator++(int)
	{
		const_iterator ret{*this};
		this->next();
		return ret;
	}

	// <predecrement operator>
	template <typename T, typename A>
	typename vector<T, A>::const_iterator&
	vector<T, A>::const_iterator::operator--()
	{
		this->prev();
		return *this;
	}

	// <postdecrement operator>
	template <typename T, typename A>
	typename vector<T, A>::const_iterator
	vector<T, A>::const_iterator::operator--(int)
	{
		const_iterator ret{*this};
		this->prev();
		return *this;
	}

	// <addition operators>
	template <typename T, typename A>
	typename vector<T, A>::const_iterator
	vector<T, A>::const_iterator::operator+(const size_type &_d) const
	{
		return vector<T, A>::const_iterator{_current + _d};
	}

	template <typename T, typename A>
	typename vector<T, A>::const_iterator&
	vector<T, A>::const_iterator::operator+=(const size_type &_d)
	{
		return *this = *this + _d;
	}
	// </addition operators>

	// <subtraction operators>
	template <typename T, typename A>
	typename vector<T, A>::const_iterator
	vector<T, A>::const_iterator::operator-(const size_type &_d) const
	{
		return vector<T, A>::const_iterator{_current - _d};
	}

	template <typename T, typename A>
	typename vector<T, A>::const_iterator&
	vector<T, A>::const_iterator::operator-=(const size_type &_d)
	{
		return *this = *this - _d;
	}
	// </subtraction operators>

	// <difference operator>
	template <typename T, typename A>
	typename vector<T, A>::const_iterator::difference_type
	vector<T, A>::const_iterator::operator-(const const_iterator &_it) const
	{
		return _current - _it._current;
	}

	// </const_iterator - increment operators>

	// <const_iterator - reference operators>
	template <typename T, typename A>
	typename vector<T, A>::const_iterator::reference
	vector<T, A>::const_iterator::operator*() const
	{
		return *_current;
	}

	template <typename T, typename A>
	typename vector<T, A>::const_iterator::pointer
	vector<T, A>::const_iterator::operator->() const
	{
		return _current;
	}
	// </const_iterator - reference operators>

// </const_iterator implemantation>


// <vector - implementation>

	// <constructors>

	// <default constructor>
	template <typename T, typename A>
	vector<T, A>::vector(const size_type &_s, const T &_t)
	:_allocator{},_data{nullptr},_size{_s},_alloc{(3 > _s) ? 10 : _s}
	{
		try
		{
			_data = _allocator.allocate(_alloc);
		}
		catch(std::bad_alloc &e)
		{
			std::cerr << e.what() << std::endl;
		}

		for(size_type i = 0; i < _size; ++i)
			_allocator.construct(_data + i, _t);
	}

	// <copy constructor>
	template <typename T, typename A>
	vector<T, A>::vector(const vector<T, A> &_v)
	:_allocator{_v._allocator},_data{nullptr},_size{_v._size},_alloc{_v._alloc}
	{
		try
		{
			_data = _allocator.allocate(_alloc);
		}
		catch (std::bad_alloc &e)
		{
			std::cerr << e.what() << std::endl;
		}

		for(int i = 0; i < _size; ++i)
			_allocator.construct(_data + i, _v[i]);
	}

	// <move constructor>
	template <typename T, typename A>
	vector<T, A>::vector(vector &&_v)
	:_allocator{std::move(_v._allocator)},_data{std::move(_v._data)},_size{_v._size},_alloc{_v._alloc}
	{
		_v._size = 0;
		_v._alloc = 0;
	}

	// <initializer_list constructor>
	template <typename T, typename A>
	vector<T, A>::vector(const std::initializer_list<T> &_l)
	:_allocator{},_data{nullptr},_size{_l.size()},_alloc{_l.size()}
	{
		try
		{
			_data = _allocator.allocate(_alloc);
		}
		catch (std::bad_alloc &e)
		{
			std::cout << e.what() << std::endl;
		}

		for(int i = 0; i < _size; ++i)
			_allocator.construct(_data + i, *(_l.begin() + i));
	}

	// <deconstructor>
	template <typename T, typename A>
	vector<T, A>::~vector()
	{
		if(_alloc)
		{
			for(int i = 0; i < _size; ++i)
				_allocator.destroy(_data + i);

			_allocator.deallocate(_data, _alloc);
		}
	}
	// </constructors>

	// <assignment operators>

	// <copy assignment>
	template <typename T, typename A>
	vector<T, A>&
	vector<T, A>::operator=(const vector<T, A> &_v)
	{
		this->clear();
		_alloc = _v._alloc;
		_size = _v._size;
		try
		{
			_data = _allocator.allocate(_alloc);
		}
		catch (std::bad_alloc &e)
		{
			std::cout << e.what() << std::endl;
		}

		for(int i = 0; i < _size; ++i)
			_allocator.construct(_data + i, _v[i]);

		return *this;
	}

	// <move assignment>
	template <typename T, typename A>
	vector<T, A>&
	vector<T, A>::operator=(vector &&_v)
	{
		this->clear();
		_data = _v._data;
		_alloc = _v._allocator;
		_size = _v._size;

		_v._data = nullptr;
		_v._alloc = 0;
		_v._size = 0;

		return *this;
	}

	// <initializer_list assignment>
	template <typename T, typename A>
	vector<T, A>&
	vector<T, A>::operator=(const std::initializer_list<T> &_l)
	{
		this->clear();
		_alloc = _size = _l.size();
		try
		{
			_data = _allocator.allocate(_alloc);
		}
		catch (std::bad_alloc &e)
		{
			std::cout << e.what() << std::endl;
		}

		for(int i = 0; i < _size; ++i)
			_allocator.construct(_data + i, *(_l.begin() + i));

		return *this;
	}
	// </assignment operators>

	// <data access/modification>
	template <typename T, typename A>
	void
	vector<T, A>::push_back(const T &_t)
	{
		if(_alloc == _size)
		{
			T *tmp{nullptr};
			_alloc *= (1.5);
			try
			{
				tmp = _allocator.allocate(_alloc);
			}
			catch (std::bad_alloc &e)
			{
				std::cout << e.what() << std::endl;
			}

			std::move(this->begin(), this->end(), tmp);
			_allocator.deallocate(_data, _size);
			_data = tmp;
			tmp = nullptr;
		}

		_allocator.construct(_data + _size++, _t);
	}

	template <typename T, typename A>
	void
	vector<T, A>::push_back(T &&_t)
	{
		if(_alloc == _size)
		{
			T *tmp{nullptr};
			_alloc *= (1.5);
			try
			{
				tmp = _allocator.allocate(_alloc);
			}
			catch (std::bad_alloc &e)
			{
				std::cout << e.what() << std::endl;
			}

			std::move(this->begin(), this->end(), tmp);
			_allocator.deallocate(_data, _size);
			_data = tmp;
			tmp = nullptr;
		}

		_allocator.construct(_data + _size++, std::move(_t));
	}


	template <typename T, typename A>
	void
	vector<T, A>::pop_back(void)
	{
		--_size;
	}

	template <typename T, typename A>
	typename vector<T, A>::const_reference
	vector<T, A>::front(void) const
	{
		return *this->cbegin();
	}

	template <typename T, typename A>
	typename vector<T, A>::const_reference
	vector<T, A>::back(void) const
	{
		return *std::prev(this->cend());
	}

	// <swap>
	template <typename T, typename A>
	void
	vector<T, A>::swap(vector<T, A> &_v)
	{
		std::swap(_data, _v._data);
		std::swap(_alloc, _v._alloc);
		std::swap(_size, _v._size);
		std::swap(_allocator, _v._allocator);
	}

	// <clear>
	template <typename T, typename A>
	void
	vector<T, A>::clear(void)
	{
		_allocator.deallocate(_data, _alloc);
		for(int i = 0; i < _size; ++i)
			_allocator.destroy(_data + i);

		_size = 0;
		_alloc = 10;
		try
		{
			_data = _allocator.allocate(_alloc);
		}
		catch (std::bad_alloc &e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	// <find>
	template <typename T, typename A>
	typename vector<T, A>::iterator
	vector<T, A>::find(const T &_t)
	{
		for(auto it = this->begin(); it != this->end(); ++it)
			if(*it == _t)
				return vector<T, A>::iterator{it};

		return this->end();
	}

	template <typename T, typename A>
	typename vector<T, A>::const_iterator
	vector <T, A>::find(const T &_t) const
	{
		for(auto it = this->cbegin(); it != this->cend(); ++it)
			if(*it == _t)
				return vector<T, A>::const_iterator{it};

		return this->cend();
	}
	// </find>

	// </data access/modification>

	// <iterators>

	// <forward iterators>
	template <typename T, typename A>
	typename vector<T, A>::iterator
	vector<T, A>::begin()
	{
		return vector<T, A>::iterator{_data};
	}

	template <typename T, typename A>
	typename vector<T, A>::const_iterator
	vector<T, A>::begin() const
	{
		return vector<T, A>::const_iterator{_data};
	}

	template <typename T, typename A>
	typename vector<T, A>::const_iterator
	vector<T, A>::cbegin() const
	{
		return vector<T, A>::const_iterator{_data};
	}

	template <typename T, typename A>
	typename vector<T, A>::iterator
	vector<T, A>::end()
	{
		return vector<T, A>::iterator{_data + _size};
	}

	template <typename T, typename A>
	typename vector<T, A>::const_iterator
	vector<T, A>::end() const
	{
		return vector<T, A>::const_iterator{_data + _size};
	}

	template <typename T, typename A>
	typename vector<T, A>::const_iterator
	vector<T, A>::cend() const
	{
		return vector<T, A>::const_iterator{_data + _size};
	}

	// <reverse iterators>
	template <typename T, typename A>
	typename vector<T, A>::reverse_iterator
	vector<T, A>::rbegin()
	{
		return vector<T, A>::reverse_iterator{this->end()};
	}

	template <typename T, typename A>
	typename vector<T, A>::const_reverse_iterator
	vector<T, A>::rbegin() const
	{
		return vector<T, A>::const_reverse_iterator{this->end()};
	}

	template <typename T, typename A>
	typename vector<T, A>::const_reverse_iterator
	vector<T, A>::crbegin() const
	{
		return vector<T, A>::const_reverse_iterator{this->cend()};
	}

	template <typename T, typename A>
	typename vector<T, A>::reverse_iterator
	vector<T, A>::rend()
	{
		return vector<T, A>::reverse_iterator{this->begin()};
	}

	template <typename T, typename A>
	typename vector<T, A>::const_reverse_iterator
	vector<T, A>::rend() const
	{
		return vector<T, A>::const_reverse_iterator{this->begin()};
	}

	template <typename T, typename A>
	typename vector<T, A>::const_reverse_iterator
	vector<T, A>::crend() const
	{
		return vector<T, A>::const_reverse_iterator{this->cbegin()};
	}

	// <structure modification>

	// <insert>
	template <typename T, typename A>
	typename vector<T, A>::iterator
	vector<T, A>::insert(iterator &_it, const T &_t)
	{
		if(_alloc == _size)
		{
			long base{_it._current - _data};
			T *tmp{nullptr};
			_alloc *= (1.5);
			try
			{
				tmp = _allocator.allocate(_alloc);
			}
			catch (std::bad_alloc &e)
			{
				std::cout << e.what() << std::endl;
			}

			std::move(this->begin(), this->end(), tmp);
			_allocator.deallocate(_data, _size);
			_data = tmp;
			_it._current = _data + base;
			tmp = nullptr;
		}

		std::move_backward(_it, this->end(), std::next(this->end()));
		_allocator.construct(_it._current, _t);
		++_size;

		return _it;
	}

	// <insert - move iterator>
	template <typename T, typename A>
	typename vector<T, A>::iterator
	vector<T, A>::insert(iterator &&_it, const T &_t)
	{
		if(_alloc == _size)
		{
			long base{_it._current - _data};
			T *tmp{nullptr};
			_alloc *= (1.5);
			try
			{
				tmp = _allocator.allocate(_alloc);
			}
			catch (std::bad_alloc &e)
			{
				std::cout << e.what() << std::endl;
			}

			std::move(this->begin(), this->end(), tmp);
			_allocator.deallocate(_data, _size);
			_data = tmp;
			_it._current = _data + base;
			tmp = nullptr;
		}

		std::move_backward(_it, this->end(), std::next(this->end()));
		_allocator.construct(_it._current, _t);
		++_size;

		return _it;
	}

	// <insert - move argument>
	template <typename T, typename A>
	typename vector<T, A>::iterator
	vector<T, A>::insert(iterator &_it, T &&_t)
	{
		if(_alloc == _size)
		{
			long base{_it._current - _data};
			T *tmp{nullptr};
			_alloc *= (1.5);
			try
			{
				tmp = _allocator.allocate(_alloc);
			}
			catch (std::bad_alloc &e)
			{
				std::cout << e.what() << std::endl;
			}

			std::move(this->begin(), this->end(), tmp);
			_allocator.deallocate(_data, _size);
			_data = tmp;
			_it._current = _data + base;
			tmp = nullptr;
		}

		std::move_backward(_it, this->end(), std::next(this->end()));
		_allocator.construct(_it._current, std::move(_t));
		++_size;

		return _it;
	}

	// <insert - move iterator, move argument>
	template <typename T, typename A>
	typename vector<T, A>::iterator
	vector<T, A>::insert(iterator &&_it, T &&_t)
	{
		if(_alloc == _size)
		{
			long base{_it._current - _data};
			T *tmp{nullptr};
			_alloc *= (1.5);
			try
			{
				tmp = _allocator.allocate(_alloc);
			}
			catch (std::bad_alloc &e)
			{
				std::cout << e.what() << std::endl;
			}

			std::move(this->begin(), this->end(), tmp);
			_allocator.deallocate(_data, _size);
			_data = tmp;
			_it._current = _data + base;
			tmp = nullptr;
		}

		std::move_backward(_it, this->end(), std::next(this->end()));
		_allocator.construct(_it._current, std::move(_t));
		++_size;

		return _it;
	}


	// <erase>
	template <typename T, typename A>
	typename vector<T, A>::iterator
	vector<T, A>::erase(iterator &_it)
	{
		if(_it == this->end())
			return _it;

		std::move(_it + 1, this->end(), _it);
		--_size;

		return _it;
	}

	// <erase - move iterator>
	template <typename T, typename A>
	typename vector<T, A>::iterator
	vector<T, A>::erase(iterator &&_it)
	{
		if(_it == this->end())
			return _it;

		std::move(_it + 1, this->end(), _it);
		--_size;

		return _it;
	}

	// <erase ranged>
	template <typename T, typename A>
	typename vector<T, A>::iterator
	vector<T, A>::erase(iterator &_b, iterator &_e)
	{
		if(_b == _e)
			return _b;

		long len{_e - _b};
		std::move(_e, this->end(), _b);
		_size -= len;

		return _b;
	}

	// <erase ranged - move iterators>
	template <typename T, typename A>
	typename vector<T, A>::iterator
	vector<T, A>::erase(iterator &&_b, iterator &&_e)
	{
		if(_b == _e)
			return _b;

		long len{_e - _b};
		std::move(_e, this->end(), _b);
		_size -= len;

		return _b;
	}
	// </iterators>

// </vector - implementation>

// </implementation>

}

#endif

