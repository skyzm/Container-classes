#ifndef _CONTAINERS_SET_HPP_
#define _CONTAINERS_SET_HPP_

#include <iostream>
#include <iterator>

namespace container
{

	template<typename Key>
	struct set_node
	{
		using ptr = set_node*;

		set_node(const Key &key = Key());
		set_node(Key &&key);

		set_node& operator=(const set_node &other);

		Key key;
		ptr parent, left, right;
	}; // struct set_node

	// class set - declaration
	template<
			typename Key,
			typename Compare = std::less<Key>
			>
	class set
	{
		using node_type = set_node<Key>;

		public:
			// typedef
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
			// /typedef

			// iterator
			class iterator : public std::iterator<	std::bidirectional_iterator_tag,	// iterator type
													Key, ptrdiff_t, Key*, Key&>			// iterator info
			{
				public:
					// constructor
					iterator(const node_type *ptr = nullptr);	// default
					iterator(const iterator &other);			// copy
					iterator(iterator &&other);				// move
					// /constructor

					// destructor
					~iterator(void);
					// /destructor

					// assignment
					iterator& operator=(const iterator &other);	// copy
					iterator& operator=(iterator &&other);			// move
					// /assignment

					// operators
					iterator& operator++();		// preincrement
					iterator operator++(int);	// postincrement
					iterator& operator--();		// predecrement
					iterator operator--(int);	// postdecrement
					// /operators

					// relation
					bool operator==(const iterator &other) const;
					bool operator!=(const iterator &other) const;
					// /relation

					// access
					reference operator*();
					pointer operator->();
					// /access
				private:
					node_type *ptr;
			};
			// /iterator

			// const iterator
			class const_iterator : public std::iterator<	std::bidirectional_iterator_tag,				// iterator type
															const Key, ptrdiff_t, const Key*, const Key&>	// iterator info
			{
				public:
					// constructor
					const_iterator(const node_type *ptr = nullptr);	// default
					const_iterator(const const_iterator &other);	// copy
					const_iterator(const_iterator &&other);			// move
					const_iterator(const iterator &other);			// convert
					const_iterator(iterator &&other); 				// convert move
					// /constructor

					// destructor
					~const_iterator(void);
					// /destructor

					// assignment
					const_iterator& operator=(const const_iterator &other);	// copy
					const_iterator& operator=(const_iterator &&other);		// move
					const_iterator& operator=(const iterator &other);		// convert
					const_iterator& operator=(iterator &&other);			// convert move
					// /assignment

					// operators
					const_iterator& operator++() const;		// preincrement
					const_iterator operator++(int) const;	// postincrement
					const_iterator& operator--() const;		// predecrement
					const_iterator operator--(int) const;	// postdecrement
					// /operators

					// relation
					bool operator==(const const_iterator &other) const;
					bool operator!=(const const_iterator &other) const;
					// /relation

					// access
					const_reference operator*() const;
					const_pointer operator->() const;
					// /access
				private:
					node_type *ptr;
			};
			// /const iterator

			// reverse iterator
			typedef std::reverse_iterator<iterator> reverse_iterator;
			// /reverse iterator

			// const reverse iterator
			typedef std::reverse_iterator<const_pointer> const_reverse_iterator;
			// /const reverse iterator

			// constructor
			set(void);										// default
			set(const set &other);							// copy
			set(set &&other);								// move
			set(const std::initializer_list<Key> &ilist);	// init list
			// /constructor

			// destructor
			~set(void);
			// /destructor

			// assignment
			set& operator=(const set &other);	// copy
			set& operator=(set &&other);		// move
			// /assignment

			// iterators
			iterator begin(void) noexcept;
			const_iterator begin(void) const noexcept;
			const_iterator cbegin(void) const noexcept;
			iterator end(void) noexcept;
			const_iterator end(void) const noexcept;
			const_iterator cend(void) const noexcept;
			// /iterators

			// reverse iterators
			reverse_iterator rbegin(void) noexcept;
			const_reverse_iterator rbegin(void) const noexcept;
			const_reverse_iterator crbegin(void) const noexcept;
			reverse_iterator rend(void) noexcept;
			const_reverse_iterator rend(void) const noexcept;
			const_reverse_iterator crend(void) const noexcept;
			// /reverse iterators

			// capacity
			bool empty(void) const noexcept;
			size_type size(void) const noexcept;
			size_type max_size(void) const noexcept;
			// /capacity

			// modifiers
			void clear(void) noexcept;

			// insert
			std::pair<iterator, bool> insert(value_type &&value);
			iterator insert(const_iterator _hint, const value_type &value);
			iterator insert(const_iterator _hint, value_type &&value);
			void insert(const std::initializer_list<Key> &ilist);
			template<typename BidirIt>
			void insert(BidirIt begin, BidirIt end);

			// emplace
			template<class... Args>
			std::pair<iterator, bool> emplace(Args &&...args);

			// erase
			iterator erase(const_iterator position);
			iterator erase(const_iterator begin, const_iterator end);
			size_type erase(const key_type &key);

			void swap(set &other);
			// /modifiers

			// lookup
			size_type count(const key_type &key);

			// find
			iterator find(const key_type &key);
			const_iterator find(const key_type &key) const;

			// equal range
			std::pair<iterator, iterator> equal_range(const key_type &key);

			// bounds
			std::pair<const_iterator, const_iterator> equal_range(const key_type &key) const;
			iterator lower_bound(const key_type &key);
			const_iterator lower_bound(const key_type &key) const;
			iterator upper_bound(const key_type &key);
			const_iterator upper_bound(const key_type &key) const;
			// /lookup

			// observers
			key_compare key_comp(void) const;
			value_compare value_comp(void) const;
			// /observers

		private:
			node_type *root, *first, *last;
			const node_type *END = new node_type;
			size_type _size;
	}; // /class set - declaration

// class set - implementation

// iterator
// constructor
template<typename Key, typename Compare>
set<Key, Compare>::iterator::iterator(const node_type *ptr)		// default
	:	ptr{ptr}
{}

template<typename Key, typename Compare>
set<Key, Compare>::iterator::iterator(const iterator &other)	// copy
	:	ptr{other.ptr}
{}

template<typename Key, typename Compare>
set<Key, Compare>::iterator::iterator(iterator &&other)			// move
	:	ptr{other.ptr}
{
	other.ptr = nullptr;
}
// /constructor

// destructor
template<typename Key, typename Compare>
set<Key, Compare>::iterator::~iterator(void)
{
	ptr = nullptr;
}
// /destructor
// assignment
template<typename Key, typename Compare>
typename set<Key, Compare>::iterator&
set<Key, Compare>::iterator::operator=(const iterator &other)	// copy
{
	ptr = other.ptr;
	return *this;
}

template<typename Key, typename Compare>
typename set<Key, Compare>::iterator&
set<Key, Compare>::iterator::operator=(iterator &&other)		// move
{
	ptr = other.ptr;
	other.ptr = nullptr;
	return *this;
}
// /assignment

// operators
template<typename Key, typename Compare>
typename set<Key, Compare>::iterator&
set<Key, Compare>::iterator::operator++()		// preincrement
{
	if(ptr->right)
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

template<typename Key, typename Compare>
typename set<Key, Compare>::iterator
set<Key, Compare>::iterator::operator++(int)	// postincrement
{
	iterator ret{*this};
	++(*this);
	return ret;
}

template<typename Key, typename Compare>
typename set<Key, Compare>::iterator&
set<Key, Compare>::iterator::operator--()		// predecrement
{
	if(ptr == END)
	{
		ptr = last;
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

template<typename Key, typename Compare>
typename set<Key, Compare>::iterator
set<Key, Compare>::iterator::operator--(int)	// postdecrement
{
	iterator ret{*this};
	--(*this);
	return ret;
}
// /operators

// relation
template<typename Key, typename Compare>
bool set<Key, Compare>::iterator::operator==(const iterator &other) const
{
	return ptr == other.ptr;
}

template<typename Key, typename Compare>
bool set<Key, Compare>::iterator::operator!=(const iterator &other) const
{
	return !(*this == other);
}
// /relation

// access
template<typename Key, typename Compare>
typename set<Key, Compare>::reference
set<Key, Compare>::iterator::operator*()
{
	return ptr->key;
}

template<typename Key, typename Compare>
typename set<Key, Compare>::pointer
set<Key, Compare>::iterator::operator->()
{
	return &(ptr)->key;
}
// /access
// /iterator


// const iterator
// constructor
template<typename Key, typename Compare>
set<Key, Compare>::const_iterator::const_iterator(const node_type *ptr)			// default
	:	ptr{ptr}
{}

template<typename Key, typename Compare>
set<Key, Compare>::const_iterator::const_iterator(const const_iterator &other)	// copy
	:	ptr{other.ptr}
{}

template<typename Key, typename Compare>
set<Key, Compare>::const_iterator::const_iterator(const_iterator &&other)		// move
	:	ptr{other.ptr}
{
	other.ptr = nullptr;
}

template<typename Key, typename Compare>
set<Key, Compare>::const_iterator::const_iterator(const iterator &other)		// convert
	:	ptr{other.ptr}
{}

template<typename Key, typename Compare>
set<Key, Compare>::const_iterator::const_iterator(iterator &&other)				// convert move
	:	ptr{other.ptr}
{
	other.ptr = nullptr;
}
// /constructor

// destructor
template<typename Key, typename Compare>
set<Key, Compare>::const_iterator::~const_iterator(void)
{
	ptr = nullptr;
}
// /destructor

// assignment
template<typename Key, typename Compare>
typename set<Key, Compare>::const_iterator&
set<Key, Compare>::const_iterator::operator=(const const_iterator &other)	// copy
{
	ptr = other.ptr;
	return *this;
}

template<typename Key, typename Compare>
typename set<Key, Compare>::const_iterator&
set<Key, Compare>::const_iterator::operator=(const_iterator &&other)		// move
{
	ptr = other.ptr;
	other.ptr = nullptr;
	return *this;
}

template<typename Key, typename Compare>
typename set<Key, Compare>::const_iterator&
set<Key, Compare>::const_iterator::operator=(const iterator &other)			// convert
{
	ptr = other.ptr;
	return *this;
}

template<typename Key, typename Compare>
typename set<Key, Compare>::const_iterator&
set<Key, Compare>::const_iterator::operator=(iterator &&other)				// convert move
{
	ptr = other.ptr;
	other.ptr = nullptr;
	return *this;
}
// /assignment

// operators
template<typename Key, typename Compare>
typename set<Key, Compare>::const_iterator&
set<Key, Compare>::const_iterator::operator++() const		// preincrement
{
	if(ptr->right)
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

template<typename Key, typename Compare>
typename set<Key, Compare>::const_iterator
set<Key, Compare>::const_iterator::operator++(int) const	// postincrement
{
	const_iterator ret{*this};
	++(*this);
	return ret;
}

template<typename Key, typename Compare>
typename set<Key, Compare>::const_iterator&
set<Key, Compare>::const_iterator::operator--() const		// predecrement
{
	if(ptr == END)
	{
		ptr = last;
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

template<typename Key, typename Compare>
typename set<Key, Compare>::const_iterator
set<Key, Compare>::const_iterator::operator--(int) const	// postdecrement
{
	const_iterator ret{*this};
	--(*this);
	return ret;
}
// /operators

// relation
template<typename Key, typename Compare>
bool set<Key, Compare>::const_iterator::operator==(const const_iterator &other) const
{
	return ptr == other.ptr;
}

template<typename Key, typename Compare>
bool set<Key, Compare>::const_iterator::operator!=(const const_iterator &other) const
{
	return !(*this == other);
}
// /relation

// access
template<typename Key, typename Compare>
typename set<Key, Compare>::const_reference
set<Key, Compare>::const_iterator::operator*() const
{
	return ptr->key;
}

template<typename Key, typename Compare>
typename set<Key, Compare>::const_pointer
set<Key, Compare>::const_iterator::operator->() const
{
	return &(ptr)->key;
}
// /access
// /const iterator

// /class set - implementation

} // namespace container


#endif // _CONTAINERS_SET_HPP_
