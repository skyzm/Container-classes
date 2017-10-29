#ifndef _CONTAINERS_SET_HPP_
#define _CONTAINERS_SET_HPP_

#include <iostream>
#include <iterator>

#include "set_node.hpp"
#include "set_detail.hpp"

namespace containers
{

	// Set declaration:
	// @@@{
	/*
	*	@brief A standard container made up of unique keys
	*	which can be inserted and retrieved in logarithmic time.
	*
	*	Sets support for bidiercional iterators.
	*
	*	@param Key Type of key objects.
	*	@param Compare Comparison object function type, defaults to std::less<Key>.
	*
	* 	The private tree data is stored as an AVL self balancing tree.
	*/
	template<
			typename Key,
			typename Compare = std::less<Key>
			>
	class set
	{
		// Convenience
		using node_type = set_node<Key>;

		public:
			// Typedefs:
			// @{
			typedef Key key_type;
			typedef Key value_type;
			typedef size_t size_type;
			typedef ptrdiff_t difference_type;
			typedef Compare key_compare;
			typedef Compare value_compare;
			typedef Key& reference;
			typedef Key* pointer;
			typedef const Key& const_reference;
			typedef const Key* const_pointer;
			// @}

			// Inner Classes:
			// @{
			class iterator;
			class const_iterator;
			// @}

			// Iterator:
			// @@{
			/*
			* @brief Iterator used for iteratirng over %set.
			*
			* @inherit std::iterator.
			*
			* @param std::bidirectional_iterator_tag Marks iterator as bidirectional.
			* @param Key Defines %value_type.
			* @param Key* Defines %pointer.
			* @param Key& Defines %reference.
			* @param ptrdiff_t Defines %difference_type.
			*
			* Private data contains current node pointer and const pointer to containing %set.
			*/
			class iterator : public std::iterator<	std::bidirectional_iterator_tag,	// %iterator type
													Key, ptrdiff_t, Key*, Key&>			// %iterator info
			{
				public:
					// Friend
					friend class set;

					// Constructor
					iterator(node_type *ptr = nullptr, const set *superset = nullptr);	// Default
					iterator(const iterator &other);									// Copy
					iterator(iterator &&other);											// Move

					// Destructor
					~iterator(void);

					// Assignment
					iterator& operator=(const iterator &other);	// Copy
					iterator& operator=(iterator &&other);		// Move

					// Operators
					iterator& operator++();		// Preincrement
					iterator operator++(int);	// Postincrement
					iterator& operator--();		// Predecrement
					iterator operator--(int);	// Postdecrement

					// Relation
					bool operator==(const iterator &other) const;
					bool operator==(const const_iterator &other) const;
					bool operator!=(const iterator &other) const;
					bool operator!=(const const_iterator &other) const;

					// Access
					reference operator*() const;
					pointer operator->() const;
				private:
					// Data
					node_type *ptr;
					const set *superset;
			};
			// @@}

			// Const Iterator:
			// @@{
			/*
			* @brief Const iterator used for const iteratirng over %set.
			*
			* @inherit std::iterator.
			*
			* @param std::bidirectional_iterator_tag Marks iterator as bidirectional.
			* @param const Key Defines %value_type.
			* @param const Key* Defines %const_pointer.
			* @param const Key& Defines %const_reference.
			* @param ptrdiff_t Defines %difference_type.
			*
			* Private data contains current node pointer and const pointer to containing %set.
			*/
			class const_iterator : public std::iterator<	std::bidirectional_iterator_tag,				// %iterator type
															const Key, ptrdiff_t, const Key*, const Key&>	// %iterator info
			{
				public:
					// Friend <3
					friend class set;

					// Constructor
					const_iterator(node_type *ptr = nullptr, const set *superset = nullptr);	// Default
					const_iterator(const const_iterator &other);								// Copy
					const_iterator(const_iterator &&other);										// Move
					const_iterator(const iterator &other);										// Convert
					const_iterator(iterator &&other); 											// Convert move

					// Destructor
					~const_iterator(void);

					// Assignment
					const_iterator& operator=(const const_iterator &other);	// Copy
					const_iterator& operator=(const_iterator &&other);		// Move
					const_iterator& operator=(const iterator &other);		// Convert
					const_iterator& operator=(iterator &&other);			// Convert move

					// Operators
					const_iterator& operator++();	// Preincrement
					const_iterator operator++(int);	// Postincrement
					const_iterator& operator--();	// Predecrement
					const_iterator operator--(int);	// Postdecrement

					// Relation
					bool operator==(const const_iterator &other) const;
					bool operator!=(const const_iterator &other) const;

					// Access
					const_reference operator*() const;
					const_pointer operator->() const;
				private:
					// Data
					node_type *ptr;
					const set *superset;
			};
			// @@}

			// Reverse Iterator
			typedef std::reverse_iterator<iterator> reverse_iterator;

			// Const Reverse Iterator
			typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

			// Constructor
			set(void);										// Default
			set(const set &other);							// Copy
			set(set &&other) noexcept;						// Move
			set(const std::initializer_list<Key> &ilist);	// Init list

			// Destructor
			~set(void);

			// Assignment
			set& operator=(const set &other);							// Copy
			set& operator=(set &&other);								// Move
			set& operator=(const std::initializer_list<Key> &ililst);	// Init list

			// Iterators
			iterator begin(void) noexcept;
			const_iterator begin(void) const noexcept;
			const_iterator cbegin(void) const noexcept;
			iterator end(void) noexcept;
			const_iterator end(void) const noexcept;
			const_iterator cend(void) const noexcept;

			// Reverse Iterators
			reverse_iterator rbegin(void) noexcept;
			const_reverse_iterator rbegin(void) const noexcept;
			const_reverse_iterator crbegin(void) const noexcept;
			reverse_iterator rend(void) noexcept;
			const_reverse_iterator rend(void) const noexcept;
			const_reverse_iterator crend(void) const noexcept;

			// Capacity
			bool empty(void) const noexcept;
			size_type size(void) const noexcept;

			// Modifiers
			void clear(void);

			// Insert
			std::pair<iterator, bool> insert(const value_type &value);
			std::pair<iterator, bool> insert(value_type &&value);
			void insert(const std::initializer_list<Key> &ilist);
			template<typename BidirIt>
			void insert(BidirIt begin, BidirIt end);

			// Emplace
			template<class... Args>
			std::pair<iterator, bool> emplace(Args &&...args);

			// Erase
			const_iterator erase(const_iterator position);
			const_iterator erase(const_iterator begin, const_iterator end);
			size_type erase(const key_type &key);

			// Swap void swap(set &other);

			// Lookup
			size_type count(const key_type &key);

			// Find
			iterator find(const key_type &key);
			const_iterator find(const key_type &key) const;

			// Equal range
			std::pair<iterator, iterator> equal_range(const key_type &key);
			std::pair<const_iterator, const_iterator> equal_range(const key_type &key) const;

			// Bounds
			iterator lower_bound(const key_type &key);
			const_iterator lower_bound(const key_type &key) const;
			iterator upper_bound(const key_type &key);
			const_iterator upper_bound(const key_type &key) const;

			// Observers
			key_compare key_comp(void) const;
			value_compare value_comp(void) const;
		private:
			// Data
			node_type *root, *first, *last;
			node_type *END;
			size_type _size;
	};
	// @@@}


// Set implementation:
// @@@{
// Iterator
// @@{
// Construction/destruction:
// @{
/*
* @brief Builds %iterator from node pointer and %set pointer.
*
* @param ptr Pointer to %set node.
* @param set Pointer to %set containing node.
*/
template<typename Key, typename Compare>
set<Key, Compare>::iterator::iterator(node_type *ptr, const set *superset)
	:	ptr{ptr},
		superset{superset}
{}

/*
* @brief %iterator Copy constructor.
*
* @param other %iterator reference.
*/
template<typename Key, typename Compare>
set<Key, Compare>::iterator::iterator(const iterator &other)
	:	ptr{other.ptr},
		superset{other.superset}
{}

/*
* @brief %iterator Move constructor.
*
* @param other %iterator rvalue reference.
*/
template<typename Key, typename Compare>
set<Key, Compare>::iterator::iterator(iterator &&other)
	:	ptr{other.ptr},
		superset{other.superset}
{
	other.ptr = nullptr;
	other.superset = nullptr;
}

/*
* Destroys %iterator instance.
*/
template<typename Key, typename Compare>
set<Key, Compare>::iterator::~iterator(void)
{
	ptr = nullptr;
	superset = nullptr;
}
// @}

// Assignment:
// @{
/*
* @brief %iterator Copy assignment.
*
* @param other %iterator reference.
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::iterator&
set<Key, Compare>::iterator::operator=(const iterator &other)
{
	ptr = other.ptr;
	superset = other.superset;
	return *this;
}

/*
* @brief %iterator Move assignment.
*
* @param other %iterator rvalue reference.
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::iterator&
set<Key, Compare>::iterator::operator=(iterator &&other)
{
	ptr = other.ptr;
	superset = other.superset;
	other.ptr = nullptr;
	return *this;
}
// @}

// Operators:
// @{
/*
* @brief Preincrement operator overload for %iterator.
*
* Moves %iterator to first successor (ascending) of Key pointed to by %iterator.
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::iterator&
set<Key, Compare>::iterator::operator++()
{
	if(superset->last == ptr)
		ptr = superset->END;
	else if(ptr->right)
	{
		ptr = ptr->right;
		while(ptr->left)
			ptr = ptr->left;
	}
	else
	{
		node_type *parent_ptr{ptr->parent};
		while(parent_ptr && ptr == parent_ptr->right)
		{
			ptr = parent_ptr;
			parent_ptr = parent_ptr->parent;
		}

		ptr = parent_ptr;
	}

	return *this;
}

/*
* @brief Postincrement operator overload for %iterator.
*
* Returns current %iterator and moves to successor (ascending).
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::iterator
set<Key, Compare>::iterator::operator++(int)
{
	iterator ret{*this};
	++(*this);
	return ret;
}

/*
* @brief Predecrement operator overload for %iterator.
*
* Moves %iterator to first precedessor (descending) of Key pointed to by %iterator.
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::iterator&
set<Key, Compare>::iterator::operator--()
{
	if(ptr == superset->END)
	{
		ptr = superset->last;
	}
	else if(ptr->left)
	{
		ptr = ptr->left;
		while(ptr->right)
			ptr = ptr->right;
	}
	else
	{
		node_type *parentptr{ptr->parent};
		while(parentptr && ptr == parentptr->left)
		{
			ptr = parentptr;
			parentptr = parentptr->parent;
		}

		ptr = parentptr;
	}

	return *this;
}

/*
* @brief Posdecrement operator overload for %iterator.
*
* Returns current %iterator and moves to predecessor (descending).
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::iterator
set<Key, Compare>::iterator::operator--(int)
{
	iterator ret{*this};
	--(*this);
	return ret;
}
// @}

// Relation:
// @{
/*
* Returns bool indicating if passed %iterator comares equal to *this.
*/
template<typename Key, typename Compare>
bool set<Key, Compare>::iterator::operator==(const iterator &other) const
{
	return ptr == other.ptr;
}

/*
* Returns bool indicating if passed %const_iterator comares equal to *this.
*/
template<typename Key, typename Compare>
bool set<Key, Compare>::iterator::operator==(const const_iterator &other) const
{
	return ptr == other.ptr;
}

/*
* Returns bool indicating if passed %iterator compares unequal to *this.
*/
template<typename Key, typename Compare>
bool set<Key, Compare>::iterator::operator!=(const iterator &other) const
{
	return !(*this == other);
}

/*
* Returns bool indicating if passed %const_iterator compares unequal to *this.
*/
template<typename Key, typename Compare>
bool set<Key, Compare>::iterator::operator!=(const const_iterator &other) const
{
	return !(*this == other);
}
// @}

// Access:
// @{
/*
* Dereference operator for %iterator. Returns %reference.
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::reference
set<Key, Compare>::iterator::operator*() const
{
	return ptr->key;
}

/*
* Pointer operator for iterator. Returns %pointer.
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::pointer
set<Key, Compare>::iterator::operator->() const
{
	return &(ptr)->key;
}
// @}
// @@}

// Const Iterator:
// @@{
// Constructor:
// @{
/*
* @brief Builds %const_iterator from node pointer and %set pointer.
*
* @param ptr Pointer to %set node.
* @param set Const ointer to %set containing node.
*/
template<typename Key, typename Compare>
set<Key, Compare>::const_iterator::const_iterator(node_type *ptr, const set *superset)
	:	ptr{ptr},
		superset{superset}
{}

/*
* @brief %const_iterator Copy constructor.
*
* @param other Const %const_iterator reference.
*/
template<typename Key, typename Compare>
set<Key, Compare>::const_iterator::const_iterator(const const_iterator &other)
	:	ptr{other.ptr},
		superset{other.superset}
{}

/*
* @brief %const_iterator Move constructor.
*
* @param other %const_iterator rvalue reference.
*/
template<typename Key, typename Compare>
set<Key, Compare>::const_iterator::const_iterator(const_iterator &&other)
	:	ptr{other.ptr},
		superset{other.superset}
{
	other.ptr = nullptr;
	other.superset = nullptr;
}

/*
* @brief %const_iterator Conversion constructor.
*
* @param other Const %iterator reference.
*/
template<typename Key, typename Compare>
set<Key, Compare>::const_iterator::const_iterator(const iterator &other)
	:	ptr{other.ptr},
		superset{other.superset}
{}

/*
* @brief %const_iterator Conversion move constructor.
*
* @param other %iterator rvalue reference.
*/
template<typename Key, typename Compare>
set<Key, Compare>::const_iterator::const_iterator(iterator &&other)
	:	ptr{other.ptr},
		superset{other.superset}
{
	other.ptr = nullptr;
	other.superset = nullptr;
}
// @}

// Destructor:
// @{
/*
* Destroys %const_iterator.
*/
template<typename Key, typename Compare>
set<Key, Compare>::const_iterator::~const_iterator(void)
{
	ptr = nullptr;
	superset = nullptr;
}
// @}

// Assignment:
// @{
/*
* @brief %const_iterator Copy assignment.
*
* @param other Const %const_iterator reference.
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::const_iterator&
set<Key, Compare>::const_iterator::operator=(const const_iterator &other)
{
	ptr = other.ptr;
	superset = other.superset;
	return *this;
}

/*
* @brief %const_iterator Move assignment.
*
* @param other %const_iterator rvalue reference.
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::const_iterator&
set<Key, Compare>::const_iterator::operator=(const_iterator &&other)
{
	ptr = other.ptr;
	superset = other.superset;
	other.ptr = nullptr;
	other.superset = nullptr;
	return *this;
}

/*
* @brief %const_iterator Convert assignment.
*
* @param other Const %iterator reference.
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::const_iterator&
set<Key, Compare>::const_iterator::operator=(const iterator &other)
{
	ptr = other.ptr;
	superset = other.superset;
	return *this;
}

/*
* @brief %const_iterator Convert move assignment.
*
* @param other %iterator rvalue reference.
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::const_iterator&
set<Key, Compare>::const_iterator::operator=(iterator &&other)
{
	ptr = other.ptr;
	superset = other.superset;
	other.ptr = nullptr;
	other.superset = nullptr;
	return *this;
}
// @}

// Operators:
// @{
/*
* @brief Preincrement operator overload for %const_iterator.
*
* Moves %const_iterator to first successor (ascending) of Key pointed to by %const_iterator.
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::const_iterator&
set<Key, Compare>::const_iterator::operator++()
{
	if(superset->last == ptr)
	{
		ptr = superset->END;
	}
	else if(ptr->right)
	{
		ptr = ptr->right;
		while(ptr->left)
			ptr = ptr->left;
	}
	else
	{
		node_type *parent_ptr{ptr->parent};
		while(parent_ptr && ptr == parent_ptr->right)
		{
			ptr = parent_ptr;
			parent_ptr = parent_ptr->parent;
		}

		ptr = parent_ptr;
	}

	return *this;
}

/*
* @brief Postincrement operator overload for %const_iterator.
*
* Returns current %const_iterator and moves to successor (ascending).
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::const_iterator
set<Key, Compare>::const_iterator::operator++(int)
{
	const_iterator ret{*this};
	++(*this);
	return ret;
}

/*
* @brief Predecrement operator overload for %const_iterator.
*
* Moves %const_iterator to first precedessor (descending) of Key pointed to by %const_iterator.
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::const_iterator&
set<Key, Compare>::const_iterator::operator--()
{
	if(ptr == superset->END)
	{
		ptr = superset->last;
	}
	else if(ptr->left)
	{
		ptr = ptr->left;
		while(ptr->right)
			ptr = ptr->right;
	}
	else
	{
		node_type *parent_ptr{ptr->parent};
		while(parent_ptr && ptr == parent_ptr->left)
		{
			ptr = parent_ptr;
			parent_ptr = parent_ptr->parent;
		}

		ptr = parent_ptr;
	}

	return *this;
}

/*
* @brief Posdecrement operator overload for %const_iterator.
*
* Returns current %const_iterator and moves to predecessor (descending).
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::const_iterator
set<Key, Compare>::const_iterator::operator--(int)
{
	const_iterator ret{*this};
	--(*this);
	return ret;
}
// @}

// Relation:
// @{
/*
* Returns bool indicating if passed %const_iterator comares equal to *this.
*/
template<typename Key, typename Compare>
bool set<Key, Compare>::const_iterator::operator==(const const_iterator &other) const
{
	return ptr == other.ptr;
}

/*
* Returns bool indicating if passed %const_iterator comares unequal to *this.
*/
template<typename Key, typename Compare>
bool set<Key, Compare>::const_iterator::operator!=(const const_iterator &other) const
{
	return !(*this == other);
}
// @}

// Access:
// @{
/*
* Dereference operator for %const_iterator. Returns %const_reference.
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::const_reference
set<Key, Compare>::const_iterator::operator*() const
{
	return ptr->key;
}

/*
* Pointer operator for %const_iterator. Returns %const_pointer.
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::const_pointer
set<Key, Compare>::const_iterator::operator->() const
{
	return &(ptr)->key;
}
// @}
// @@}

// Set:
// @@{
// Construction/destruction:
// @{
/*
* @brief Builds empty %set.
*/
template<typename Key, typename Compare>
set<Key, Compare>::set(void)
	:	root{nullptr},
		first{nullptr},
		last{nullptr},
		END{new node_type},
		_size{0}
{}

/*
* @brief %set Copy constructor.
*
* @param other %set object to copy.
*
* Creates a %set instance from elements in other. This is done in
* linear O(N) time where N is other.size().
*/
template<typename Key, typename Compare>
set<Key, Compare>::set(const set &other)
	:	root{nullptr},
		first{nullptr},
		last{nullptr},
		END{new node_type},
		_size{0}
{
	for(const auto &e : other)
		insert(e);
}

/*
* @brief %set Move constructor.
*
* @param other %set object to move.
*
* Creates an identical %set instance from elements in other. This is done in
* linear O(N) time where N is other.size()
*/
template<typename Key, typename Compare>
set<Key, Compare>::set(set &&other) noexcept
	:	root{other.root},
		first{other.first},
		last{other.last},
		END{other.END},
		_size{std::move(other._size)}
{
	other.root = nullptr;
	other.first = nullptr;
	other.last = nullptr;
	other.END = nullptr;
}

/*
* @brief Builds %set from and std::initializer_list.
*
* @param ilist An std::initializer_list.
*
* Creates %set from elements in ilist. This is O(N) if list is sorted,
* otherwise NlogN where N equals ilist.size().
*/
template<typename Key, typename Compare>
set<Key, Compare>::set(const std::initializer_list<Key> &ilist)
	:	root{nullptr},
		first{nullptr},
		last{nullptr},
		END{new node_type},
		_size{0}
{
	for(const auto &e : ilist)
		insert(e);
}

/*
* @brief Destructor for %set.
*
* Releases all resources held by %set.
*/
template<typename Key, typename Compare>
set<Key, Compare>::~set(void)
{
	clear();
	if(nullptr != END)
		delete END;
}
// @}

// Assignment:
// @{
/*
* @brief %set Copy assignemnt operator overload
*
* @param other %set object to be copied
*
* All elements are copied and any existing are erased.
* This is done in linear time.
*/
template<typename Key, typename Compare>
set<Key, Compare>&
set<Key, Compare>::operator=(const set &other)
{
	clear();
	for(const auto &e : other)
		insert(e);
	return *this;
}

/*
* @brief %set Move assignemnt operator overload
*
* @param other %set object to be moved
*
* All elements are moves and any existing are erased.
* This is done in linear time.
*/
template<typename Key, typename Compare>
set<Key, Compare>&
set<Key, Compare>::operator=(set &&other)
{
	clear();

	root = other.root;
	first = other.first;
	last = other.last;
	END = other.END;
	_size = std::move(other._size);

	other.root = nullptr;
	other.first = nullptr;
	other.last = nullptr;
	other.END = nullptr;

	return *this;
}

/*
* @brief %set list assignment operator overload
*
* @param ilist An std::initializer_list
*
* All elements from ilist are copied into %set. Old data is erased.
* This is done in NlogN time (linear if ilist is sorted)
*/
template<typename Key, typename Compare>
set<Key, Compare>&
set<Key, Compare>::operator=(const std::initializer_list<Key> &ilist)
{
	clear();
	for(const auto &e : ilist)
		insert(e);
	return this;
}
// @}

// Iterators:
// @{
/*
* Returns %iterator that points to the first element in %set.
* Iteration is done in ascending order set by Compare
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::iterator
set<Key, Compare>::begin(void) noexcept
{
	return (empty()) ? iterator{END, this} : iterator{first, this};
}

/*
* Returns const (read-only) %iterator that points to the first element in %set.
* Iteration is done in ascending order set by Compare
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::const_iterator
set<Key, Compare>::begin(void) const noexcept
{
	return (empty()) ? const_iterator{END, this} : const_iterator{first, this};
}

/*
* Returns const (read-only) %const_iterator that points to the first element in %set.
* Iteration is done in ascending order set by Compare
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::const_iterator
set<Key, Compare>::cbegin(void) const noexcept
{
	return (empty()) ? const_iterator{END, this} : const_iterator{first, this};
}

/*
* Returns %iterator that points to one past the last element.
* Iteration is done in ascending order set by Compare
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::iterator
set<Key, Compare>::end(void) noexcept
{
	return iterator{END, this};
}

/*
* Returns const (read-only) %iterator that points to one past the last element.
* Iteration is done in ascending order set by Compare
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::const_iterator
set<Key, Compare>::end(void) const noexcept
{
	return const_iterator{END, this};
}

/*
* Returns const (read-only) %const_iterator that points to one past the last element.
* Iteration is done in ascending order set by Compare
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::const_iterator
set<Key, Compare>::cend(void) const noexcept
{
	return const_iterator{END, this};
}
// @}

// Reverse Iterators:
// @{
/*
* Returns an %iterator that points to the last element in %set.
* Iteration is done in descending order set by Compare.
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::reverse_iterator
set<Key, Compare>::rbegin(void) noexcept
{
	return reverse_iterator{end()};
}

/*
* Returns a const (read-only) %iterator that points to the last element in %set.
* Iteration is done in descending order set by Compare.
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::const_reverse_iterator
set<Key, Compare>::rbegin(void) const noexcept
{
	return const_reverse_iterator{end()};
}

/*
* Returns a const (read-only) %const_iterator that points to the last element in %set.
* Iteration is done in descending order set by Compare.
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::const_reverse_iterator
set<Key, Compare>::crbegin(void) const noexcept
{
	return const_reverse_iterator{cend()};
}

/*
* Returns an %reverse_iterator that points to the first element in %set.
* Iteration is done in descending order.
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::reverse_iterator
set<Key, Compare>::rend(void) noexcept
{
	return reverse_iterator{begin()};
}

/*
* Returns a const (read-only) %reverse_iterator that points to the first element in %set.
* Iteration is done in descending order.
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::const_reverse_iterator
set<Key, Compare>::rend(void) const noexcept
{
	return const_reverse_iterator{begin()};
}

/*
* Returns a const (read-only) %const_reverse_iterator that points to the first element in %set.
* Iteration is done in descending order.
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::const_reverse_iterator
set<Key, Compare>::crend(void) const noexcept
{
	return const_reverse_iterator{cbegin()};
}
// @}

// Capacity:
// @{
/*
* Returns indicator if %set is empty.
*/
template<typename Key, typename Compare>
bool set<Key, Compare>::empty(void) const noexcept
{
	return (0 == size());
}

/*
* Returns number of unique keys in %set.
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::size_type
set<Key, Compare>::size(void) const noexcept
{
	return _size;
}
// @}

// Modifiers:
// @{
/*
* Erase all keys in %set. This is done in linear time.
*/
template<typename Key, typename Compare>
void set<Key, Compare>::clear(void)
{
	avl::detail::bst_delete(root);
	_size = 0;
	root = last = first = nullptr;
}

/*
* @brief Insertion function for %set.
*
* @param value Value to be inserted.
*
* Attempts to insert @value into %set. If insertion succeeds a pair with %iterator to
* the newly inserted element and bool is returned in format (%iterator, true).
* Otherwise (end(), false) is returned.
* Insertion is done in logN time where N is the number of elements in %set.
*/
template<typename Key, typename Compare>
std::pair<typename set<Key, Compare>::iterator, bool>
set<Key, Compare>::insert(const value_type &value)
{
	if(empty())
	{
		root = new node_type{value};
		first = last = root;
		++_size;
		return std::make_pair(iterator{root, this}, true);
	}

	auto istatus{avl::detail::bst_insert(root, value, Compare{})};

	if(!istatus.first)
		return std::make_pair(end(), false);
	else if(!istatus.second)
		return std::make_pair(iterator{istatus.first, this}, false);

	++_size;
	first = avl::detail::minimum(root);
	last = avl::detail::maximum(root);

	node_type *tmp{istatus.first};

	while(tmp)
	{
		tmp = tmp->parent;
		avl::detail::balance_tree(tmp, root);
	}

	return std::make_pair(iterator{istatus.first, this}, true);
}

/*
* @brief Insertion function for %set.
*
* @param value Value to be moved to %set.
*
* Attempts to move insert @value into %set. If insertion succeeds a pair with %iterator to
* the newly inserted element and bool is returned in format (%iterator, true).
* Otherwise (end(), false) is returned.
* Insertion is done in logN time where N is the number of elements in %set.
*/
template<typename Key, typename Compare>
std::pair<typename set<Key, Compare>::iterator, bool>
set<Key, Compare>::insert(value_type &&value)
{
	if(empty())
	{
		root = new node_type{std::move(value)};
		first = last = root;
		++_size;
		return std::make_pair(iterator{root, this}, true);
	}

	auto istatus{avl::detail::bst_insert(root, std::move(value), Compare{})};

	if(!istatus.first)
		return std::make_pair(end(), false);
	else if(!istatus.second)
		return std::make_pair(iterator{istatus.first, this}, false);

	++_size;
	first = avl::detail::minimum(root);
	last = avl::detail::maximum(root);

	node_type *tmp{istatus.first};

	while(tmp)
	{
		tmp = tmp->parent;
		avl::detail::balance_tree(tmp, root);
	}

	return std::make_pair(iterator{istatus.first, this}, true);
}

/*
* @brief Insert function for std::initializer_list.
*
* @param ililst An std::initializer_list.
*
* Inserts all elements from @ilist not already in %set. Insertion is done in
* ilist.size() * logN time where N is the number of elements in %set.
*
*/
template<typename Key, typename Compare>
void set<Key, Compare>::insert(const std::initializer_list<Key> &ilist)
{
	for(auto &e : ilist)
		insert(e);
}

/*
* @brief Range insertion function
*
* @param begin Start of range to be inserted.
* @param end One past the last element to be inserted.
*
* Inserts all elements in range [begin, end) not already in %set.
* Insertion is done in distance(first, last) * logN time where N is the number of elements in %set.
*/
template<typename Key, typename Compare>
template<typename BidirIt>
void set<Key, Compare>::insert(BidirIt begin, BidirIt end)
{
	for(auto it = begin; it != end; ++it)
		insert(*it);
}

// Emplace:
// @{
/*
* @brief Inserts a new element constructed in-place with given @args.
*
* @param ...args Forwarded to costructor of %Key via std::forward<Args>(args)...
*/
template<typename Key, typename Compare>
template<class... Args>
std::pair<typename set<Key, Compare>::iterator, bool>
set<Key, Compare>::emplace(Args &&...args)
{
	return insert(Key{std::forward<Args>(args)...});
}
// @}

/*
* @brief Erase element at @position.
*
* @param position %const_iterator to element to be erased.
*
* Erasing is done in logN time where N is the number of elements in %set.
* Returns %iterator to successor (ascending) of element in %set.
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::const_iterator
set<Key, Compare>::erase(const_iterator position)
{
	if(cend() == position)
		return cend();

	auto ret{position};
	++ret;
	auto par{avl::detail::bst_erase(position.ptr)};

	while(par)
	{
		avl::detail::balance_tree(par, root);
		par = par->parent;
	}

	first = avl::detail::minimum(root);
	last = avl::detail::maximum(root);

	--_size;
	return ret;
}

/*
* @brief Range erase function.
*
* @param begin Start of range to be erased.
* @param end One past the last element to be erased.
*
* Erasing is done in distance(first, last) * logN where N is the number of elements in %set.
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::const_iterator
set<Key, Compare>::erase(const_iterator begin, const_iterator end)
{
	for(auto it = begin; it != end; ++it)
		erase(const_iterator{it.ptr, this});

	return const_iterator{end};
}

/*
* @brief Erase by key.
*
* @param key Value of key to be erased.
*
* If key is in set it will be erased, otherwise nothing happens.
* Complexity is logN where N is the number of elements in %set.
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::size_type
set<Key, Compare>::erase(const key_type &key)
{
	auto node{find(key)};
	if(end() == node)
		return 0;

	erase(node);

	return 1;
}
// @}

// Lookup:
// @{
/*
* Returns number of elements which compare equal to @key in %set (1 or 0 is returned).
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::size_type
set<Key, Compare>::count(const key_type &key)
{
	if(end() == find(key))
		return 0;

	return 1;
}

/*
* @brief Find function.
*
* @param key Key to search for.
*
* Returns %iterator to key, or end() if no such key is found.
* Complexity is logN where N is the number of elements in %set.
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::iterator
set<Key, Compare>::find(const key_type &key)
{
	node_type *tmp{avl::detail::bst_find(root, key, Compare{})};

	if(tmp)
		return iterator{tmp, this};
	else
		return end();
}

/*
* @brief Find function.
*
* @param key Key to search for.
*
* Returns %const_iterator (read-only) to key, or cend() if no such key is found.
* Complexity is logN where N is the number of elements in %set.
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::const_iterator
set<Key, Compare>::find(const key_type &key) const
{
	node_type *tmp{avl::detail::bst_find(root, key, Compare{})};

	if(tmp)
		return const_iterator{tmp, this};
	else
		return cend();
}
//@}

// Equal range:
// @{
template<typename Key, typename Compare>
std::pair<typename set<Key, Compare>::iterator, typename set<Key, Compare>::iterator>
set<Key, Compare>::equal_range(const key_type &key)
{
	return std::make_pair(lower_bound(key), upper_bound(key));
}

template<typename Key, typename Compare>
std::pair<typename set<Key, Compare>::const_iterator, typename set<Key, Compare>::const_iterator>
set<Key, Compare>::equal_range(const key_type &key) const
{
	return std::make_pair(lower_bound(key), upper_bound(key));
}
// @}

// Bounds:
// @{
/*
* @brief Find lower bound of @key in %set.
*
* @param key Key to find bound for.
*
* @return %iterator to element or end() if no such is found.
*
* A lower bound is the first element in %set not less than @key.
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::iterator
set<Key, Compare>::lower_bound(const key_type &key)
{
	node_type *bound{avl::detail::bst_lower_bound(root, key, Compare{})};
	if(bound)
		return iterator{bound, this};

	return end();
}

/*
* @brief Find lower bound of @key in %set.
*
* @param key Key to find bound for.
*
* @return %const_iterator (read-only) to element or end() if no such is found.
*
* A lower bound is the first element in %set not less than @key.
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::const_iterator
set<Key, Compare>::lower_bound(const key_type &key) const
{
	node_type *bound{avl::detail::bst_lower_bound(root, key, Compare{})};
	if(bound)
		return const_iterator{bound, this};

	return cend();
}

/*
* @brief Find upper bound of @key in %set.
*
* @param key Key to find bound for.
*
* @return %iterator to element or end() if no such is found.
*
* An upper bound is the first element in %set greater than @key.
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::iterator
set<Key, Compare>::upper_bound(const key_type &key)
{
	node_type *bound{avl::detail::bst_upper_bound(root, key, Compare{})};
	if(bound)
		return iterator{bound, this};

	return end();
}

/*
* @brief Find upper bound of @key in %set.
*
* @param key Key to find bound for.
*
* @return %const_iterator (read-only) to element or end() if no such is found.
*
* An upper bound is the first element in %set greater than @key.
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::const_iterator
set<Key, Compare>::upper_bound(const key_type &key) const
{
	node_type *bound{avl::detail::bst_upper_bound(root, key, Compare{})};
	if(bound)
		return const_iterator{bound, this};

	return cend();
}
// @}

// Observers:
// @{
/*
* Returns instance of comparator used for comparing keys.
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::key_compare
set<Key, Compare>::key_comp(void) const
{
	return Compare{};
}

/*
* Returns instance of comparator used for comparing values.
*/
template<typename Key, typename Compare>
typename set<Key, Compare>::value_compare
set<Key, Compare>::value_comp(void) const
{
	return Compare{};
}
// @}
// @@}
// @@@}

} // namespace container


#endif // _CONTAINERS_SET_HPP_
