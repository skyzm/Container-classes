#ifndef _CONTAINERS_SET_NODE_HPP_
#define _CONTAINERS_SET_NODE_HPP_

#include <iostream>

namespace containers
{

	// Set Node declaration:
	// @@{
	/*
	* @brief A nonde structure used for storing keys in %set.
	*
	* @param T Type of key objects.
	*
	* Stores pointer to left and right child whose keys compare
	* less than and greater than respectively to key.
	* Also stores parent pointer for iteration purposes.
	*/
	template<typename T>
	struct set_node
	{
		// Convenience
		using ptr = set_node*;

		// Constructor
		set_node(void);
		set_node(const T &key);
		set_node(T &&key);
		template<class ...Args>
		set_node(Args &&...args);

		// Assignment
		set_node& operator=(const set_node &other);
		set_node& operator=(set_node &&other);

		// Data
		T key;
		ptr parent, left, right;
	};
	// @@}

	// Set Node implementation:
	// @@{
	// Construction:
	// @{
	/*
	* @brief Builds instance of %set_node
	*/
	template<typename T>
	set_node<T>::set_node(void)
		:	key{},
			parent{nullptr},
			left{nullptr},
			right{nullptr}
	{}

	/*
	* @brief Builds instance of %set_node.
	*
	* @param key Key to be assigned to node.
	*/
	template<typename T>
	set_node<T>::set_node(const T &key)
		:	key{key},
			parent{nullptr},
			left{nullptr},
			right{nullptr}
	{}

	/*
	* @brief Builds instance of %set_node.
	*
	* @param key Key to be moved to node.
	*/
	template<typename T>
	set_node<T>::set_node(T &&key)
		:	key{std::move(key)},
			parent{nullptr},
			left{nullptr},
			right{nullptr}
	{}

	/*
	* @brief Forwarding consturctor.
	* 
	* @param args Arguments to be forwarded to consturctor of %T
	*/
	template<typename T>
	template<class ...Args>
	set_node<T>::set_node(Args &&...args)
		:	key{std::forward<Args>(args)...},
			parent{nullptr},
			left{nullptr},
			right{nullptr}
	{}
	// @}

	// Assignment:
	// @{
	/*
	* Copy assignment operator overload for %set_node.
	*/
	template<typename T>
	set_node<T>&
	set_node<T>::operator=(const set_node &other)
	{
		key = other.key;
		parent = other.parent;
		left = other.left;
		right = other.right;

		return *this;
	}

	/*
	* Move assignment operator overload for %set_node.
	*/
	template<typename T>
	set_node<T>&
	set_node<T>::operator=(set_node &&other)
	{
		key = std::move(other.key);
		parent = other.parent;
		left = other.left;
		right = other.right;

		other.parent = nullptr;
		other.left = nullptr;
		other.right = nullptr;

		return *this;
	}
	// @}
	// @@}

} // namespace containers

#endif // _CONTAINERS_SET_NODE_HPP_
