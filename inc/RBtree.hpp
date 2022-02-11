/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:06:31 by skienzle          #+#    #+#             */
/*   Updated: 2022/02/11 22:49:16 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>

#include "Itree.hpp"
#include "iterator.hpp"

#ifndef nullptr
#define nullptr NULL
#endif

namespace ft
{

enum node_color { black = false, red = true };

template<typename T>
struct RBtree_node
{
	typedef T								value_type;
	typedef RBtree_node<value_type>*		node_ptr;
	typedef const RBtree_node<value_type>*	const_node_ptr;

	void flip_color();

	node_color	_color;
	value_type	_data;
	node_ptr	_parent;
	node_ptr	_left;
	node_ptr	_right;
};

template<typename T>
void
RBtree_node<T>::flip_color()
{
	this->_color = this->_color == red ? black : red;
}



template<typename T>
bool
tree_is_left_child(typename RBtree_node<T>::node_ptr node)
{
	return node == node->_parent->_left;
}

template<typename T>
bool
tree_is_left_child(typename RBtree_node<T>::const_node_ptr node)
{
	return node == node->_parent->_left;
}

template<typename T>
typename RBtree_node<T>::node_ptr
tree_min(typename RBtree_node<T>::node_ptr root)
{
	while (root->_left != nullptr)
		root = root->_left;
	return root;
}

template<typename T>
typename RBtree_node<T>::const_node_ptr
tree_min(typename RBtree_node<T>::const_node_ptr root)
{
	while (root->_left != nullptr)
		root = root->_left;
	return root;
}

template<typename T>
typename RBtree_node<T>::node_ptr
tree_max(typename RBtree_node<T>::node_ptr root)
{
	while (root->_right != nullptr)
		root = root->_right;
	return root;
}

template<typename T>
typename RBtree_node<T>::const_node_ptr
tree_max(typename RBtree_node<T>::const_node_ptr root)
{
	while (root->_right != nullptr)
		root = root->_right;
	return root;
}


template<typename T, typename Compare, typename Alloc>
class RBtree: public Itree<T,Compare,Alloc>
{
private: // types
	typedef Itree<T,Compare,Alloc>						interface_type;
public: // types
	typedef typename interface_type::value_type											value_type;
	typedef typename interface_type::value_compare										value_compare;
	typedef typename interface_type::allocator_type										allocator_type;
	typedef typename allocator_type::template rebind<RBtree_node<value_type> >::other	node_allocator_type;
	typedef typename allocator_type::pointer											pointer;
	typedef typename allocator_type::const_pointer										const_pointer;
	typedef typename allocator_type::size_type											size_type;
	typedef typename allocator_type::difference_type									difference_type;
	typedef typename RBtree_node<T>::node_ptr											node_ptr;
	typedef typename RBtree_node<T>::const_node_ptr										const_node_ptr;

public: // methods
	explicit RBtree(const value_compare& comp, const allocator_type& alloc);
	RBtree(const RBtree& other);

	~RBtree();

	RBtree& operator=(const RBtree& other);

	bool empty() const;
	
	void insert(const value_type& val); // dummy
	// ft::pair<iterator,bool>		insert(const value_type& val);

	
private: // methods
	node_ptr construct_node(const value_type& data);
	void destroy_node(node_ptr node);
	node_ptr insert(node_ptr node, node_ptr new_node);
	node_ptr copy(node_ptr node);
	void destroy(node_ptr node);
	bool equals(const value_type& first, const value_type& second) const;
private: // attributes
	size_type			_size;
	node_ptr			_root;
	value_compare		_comp;
	allocator_type		_allocator;
	node_allocator_type	_node_allocator;
};

template<typename T, typename Compare, typename Alloc>
RBtree<T,Compare,Alloc>::RBtree(const value_compare& comp, const allocator_type& alloc):
	_size(), _root(), _comp(comp), _allocator(alloc), _node_allocator(alloc) {}

template<typename T, typename Compare, typename Alloc>
RBtree<T,Compare,Alloc>::RBtree(const RBtree& other): 
	_size(), _root(this->copy(other._root)), _comp(other._comp),
	_allocator(other._allocator), _node_allocator(other._node_allocator) {}

template<typename T, typename Compare, typename Alloc>
RBtree<T,Compare,Alloc>::~RBtree()
{
	if (this->_root != nullptr)
	{
		this->destroy(this->_root);
		this->_root == nullptr;
	}
}

template<typename T, typename Compare, typename Alloc>
RBtree<T,Compare,Alloc>&
RBtree<T,Compare,Alloc>::operator=(const RBtree& other)
{
	if (this != &other)
	{
		this->destroy(this->_root);
		this->copy(other._root);
		this->_comp = other._comp;
	}
	return *this;
}

template<typename T, typename Compare, typename Alloc>
void
RBtree<T,Compare,Alloc>::insert(const value_type& val)
{
	node_ptr new_node = this->construct_node(val);
	this->_root = insert(this->_root, new_node);
}

template<typename T, typename Compare, typename Alloc>
typename RBtree<T,Compare,Alloc>::node_ptr
RBtree<T,Compare,Alloc>::insert(node_ptr node, node_ptr new_node)
{
	if (node == nullptr)
		return new_node;
	if (this->_comp(node->_data, new_node->_data))
	{
		node->_left = insert(node->_left, new_node);
		node->_left->_parent = node;
	}
	else
	{
		node->_right = insert(node->_right, new_node);
		node->_right->_parent = node;
	}
	return node;
}

// template<typename T, typename Compare, typename Alloc>
// void
// RBtree<T,Compare,Alloc>::erase(const value_type& val)
// {
	
// }


template<typename T, typename Compare, typename Alloc>
bool
RBtree<T,Compare,Alloc>::empty() const
{
	return this->_size == 0;
}






template<typename T, typename Compare, typename Alloc>
typename RBtree<T,Compare,Alloc>::node_ptr
RBtree<T,Compare,Alloc>::construct_node(const value_type& data)
{
	node_ptr new_node = this->_node_allocator.allocate(1);
	this->_allocator.construct(&new_node->_data, data);
	new_node->color = red;
	new_node->_parent = nullptr;
	new_node->_left = nullptr;
	new_node->_right = nullptr;
	++this->_size;
	return new_node;
}

template<typename T, typename Compare, typename Alloc>
void
RBtree<T,Compare,Alloc>::destroy_node(node_ptr node)
{
	this->_allocator.destroy(&node->_data);
	this->_node_allocator.deallocate(node, 1);
	--this->_size;
}

template<typename T, typename Compare, typename Alloc>
typename RBtree<T,Compare,Alloc>::node_ptr
RBtree<T,Compare,Alloc>::copy(node_ptr node)
{
	if (node == nullptr)
		return nullptr;
	node_ptr new_node = this->construct_node(node->_data);
	new_node->_left = copy(node->_left);
	new_node->_right = copy(node->_right);
	return new_node;
}


template<typename T, typename Compare, typename Alloc>
void
RBtree<T,Compare,Alloc>::destroy(node_ptr node)
{
	if (node == nullptr)
		return;
	destroy(node->_left);
	destroy(node->_right);
	this->destroy_node(node);
}

template<typename T, typename Compare, typename Alloc>
bool
RBtree<T,Compare,Alloc>::equals(const value_type& first, const value_type& second) const
{
	return !this->_comp(first, second) && !this->_comp(second, first);
}

} // namespace ft