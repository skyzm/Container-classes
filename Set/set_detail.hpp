#ifndef _CONTAINER_SET_DETAIL_HPP_
#define _CONTAINER_SET_DETAIL_HPP_

#include "set_node.hpp"
#include "color.hpp"

namespace containers::avl::detail
{

	/*
	* Function used for calculating height of %set_node
	* relative to its children.
	*/
	template<typename T>
	size_t node_height(set_node<T> *&node)
	{
		size_t height{0};
		if(node)
		{
			size_t left = node_height(node->left);
			size_t right = node_height(node->right);
			height = 1 + std::max(left, right);
		}

		return height;
	}

	/*
	* @brief Calculates balance factor of @node.
	*
	* @param node pointer to %set_node.
	*/
	template<typename Key>
	int get_balance_factor(set_node<Key> *&node)
	{
		if(nullptr == node)
			return 0;

		return node_height(node->left) - node_height(node->right);
	}

	// Will be deleted
	template<typename Key>
	void preodrer(set_node<Key> *&node)
	{
		if(nullptr == node)
			return;

		preodrer(node->left);

		if(node->left && node->right)
			std::cerr << YELLOW;
		else if(node->right)
			std::cerr << BLUE;
		else if(node->left)
			std::cerr << GREEN;
		else
			std::cerr << RED;

		if(get_balance_factor(node) > 1 || get_balance_factor(node) < -1)
			std::cerr << BOLDRED << "OH SHIT FML SMTH IS BROKEN " << get_balance_factor(node) << " ";

		std::cerr << node->key << RESET << " ";

		preodrer(node->right);
	}
	// Will be deleted

	template<typename Key>
	void left_rotate(set_node<Key> *&node, set_node<Key> *&root)
	{
		std::cerr << BOLDRED <<  "\nleft rotation of " << node->key << "\n" << RESET;

		set_node<Key>* tmp{node->right};
		set_node<Key>* tmp2{tmp->left};

		tmp->left = node;
		tmp->parent = node->parent;
		node->parent = tmp;

		if(tmp->parent)
		{
			if(tmp->parent->left == node)
				tmp->parent->left = tmp;
			else
				tmp->parent->right = tmp;
		}
		else
			root = tmp;

		tmp->left->right = tmp2;
		if(tmp2)
			tmp2->parent = tmp->left;
	}

	template<typename Key>
	void right_rotate(set_node<Key> *&node, set_node<Key> *&root)
	{
		std::cerr << BOLDBLUE << "\nright rotation of " << node->key << "\n" << RESET;

		set_node<Key>* 	tmp{node->left};
		set_node<Key>* tmp2{tmp->right};

		tmp->right = node;
		tmp->parent = node->parent;
		node->parent = tmp;

		if(tmp->parent)
		{
			if(tmp->parent->left == node)
				tmp->parent->left = tmp;
			else
				tmp->parent->right = tmp;
		}
		else
			root = tmp;

		tmp->right->left = tmp2;
		if(tmp2)
			tmp2->parent = tmp->right;
	}

	/*
	* @brief AVL balancing function.
	*
	* @param node Node to be balanced.
	* @param root Root of the tree.
	*
	* Balancing function, read included documentation for more information.
	*/
	template<typename Key>
	void balance_tree(set_node<Key> *&node, set_node<Key> *&root)
	{
		int balance{get_balance_factor(node)};

		if(balance > 1) 							// left subtree unbalance
		{
			if(get_balance_factor(node->left) < 0)	// right child of left subtree is the cause
				left_rotate(node->left, root);
			right_rotate(node, root);
		}
		else if(balance < -1) 						// right subtree unbalance
		{
			if(get_balance_factor(node->right) > 0)	// left child of right subtree is the cause
				right_rotate(node->right, root);
			left_rotate(node, root);
		}
	}

	/*
	* Returns pointer to smallest element (ascending) in subtree with root @node.
	*/
	template<typename Key>
	set_node<Key>* minimum(set_node<Key> *node)
	{
		set_node<Key> *tmp{node};
		while(tmp->left)
			tmp = tmp->left;

		return tmp;
	}

	/*
	* Returns pointer to largest element (ascending) in subtree with root @node.
	*/
	template<typename Key>
	set_node<Key>* maximum(set_node<Key> *node)
	{
		set_node<Key> *tmp{node};
		while(tmp->right)
			tmp = tmp->right;

		return tmp;
	}

	/*
	* @brief Standard BST insertion function.
	*
	* @param node pointer to reference of %set_node.
	* @param value Value to insert (& or && not specified, will be deduced at compile time)
	* @param comp Comparator to use for insertion.
	*
	* @return set_node* Pointer to new node or to node that prevented insertion.
	* @return bool Indicator whether insertion was successful.
	*/
	template<typename Key, typename Compare>
	std::pair<set_node<Key>*, bool> bst_insert(set_node<Key> *&node, Key value, Compare comp)
	{
		if(nullptr == node)					// protect the function
			return std::make_pair(nullptr, false);
		else if(comp(value, node->key))		// @value compares less than @node->key
		{
			if(nullptr == node->left)
			{
				node->left = new set_node<Key>{value};
				node->left->parent = node;
				return std::make_pair(node->left, true);
			}

			return bst_insert(node->left, value, comp);
		}
		else if(comp(node->key, value))		// @value compares greater than @node->key
		{
			if(nullptr == node->right)
			{
				node->right = new set_node<Key>{value};
				node->right->parent = node;
				return std::make_pair(node->right, true);
			}

			return bst_insert(node->right, value, comp);
		}
		else								// @value compares equivalent to @node->key, will not be added
			return std::make_pair(node, false);
	}

	/*
	* @brief Standard BST erase function.
	*
	* @param node Pointer to node to be removed.
	*/
	template<typename Key>
	set_node<Key>* bst_erase(set_node<Key> *node)
	{
		if(nullptr == node)											// protect the function
			return nullptr;

		static set_node<Key> *ret{nullptr};								// save a neighbour, we need this for balancing

		if(nullptr == node->left && nullptr == node->right)			// node to remove is a leaf
		{
			if(node->parent)
			{
				ret = node->parent;

				if(node->parent->left == node)
					node->parent->left = nullptr;
				else
					node->parent->right = nullptr;
			}
			delete node;
			node = nullptr;
		}
		else if(nullptr != node->left && nullptr == node->right)	// node has left child only
		{
			ret = node->left;

			set_node<Key> *tmp{node};
			node->left->parent = node->parent;
			if(node->parent)
			{
				if(node->parent->left == node)
					node->parent->left = node->left;
				else
					node->parent->right = node->left;
			}

			delete node;
			node = nullptr;
		}
		else if(nullptr == node->left && nullptr != node->right)	// node has right child only
		{
			ret = node->right;

			set_node<Key> *tmp{node};
			node->right->parent = node->parent;
			if(node->parent)
			{
				if(node->parent->left == node)
					node->parent->left = node->right;
				else
					node->parent->right = node->right;
			}

			delete node;
			node = nullptr;
		}
		else														// node has both children
		{
			set_node<Key> *tmp{minimum(node->right)};
			node->key = std::move(tmp->key);
			bst_erase(tmp);
		}

		return ret;
	}

	/*
	* @brief Standard BST search function.
	*
	* @param root Root of tree to traverse.
	* @param key Key to find.
	* @param comp Comparator to use.
	*/
	template<typename Key, typename Compare>
	set_node<Key>* bst_find(set_node<Key> *root, Key key, Compare comp)
	{
		if(nullptr == root)
			return nullptr;

		if(comp(key, root->key))		// @key compares less than @root->key
			return bst_find(root->left, key, comp);
		else if(comp(root->key, key))	// @key compares greater than @root->key
			return bst_find(root->right, key, comp);
		else							// @key is equivalent to @root->key
			return root;
	}

	/*
	* @brief Standard BST delete function.
	*
	* @param root Root of subtree to delete.
	*/
	template<typename Key>
	void bst_delete(set_node<Key> *&root)
	{
		if(nullptr == root)
			return;

		std::cerr << MAGENTA << "Deleting node: " << root->key << RESET << std::endl;
		bst_delete(root->left);
		bst_delete(root->right);
		delete root;
		root = nullptr;
	}

} // nested namespace container::avl::detail

#endif // _CONTAINER_SET_DETAIL_HPP_
