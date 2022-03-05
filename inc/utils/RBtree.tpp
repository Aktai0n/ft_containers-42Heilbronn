/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBtree.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 16:50:18 by skienzle          #+#    #+#             */
/*   Updated: 2022/03/05 17:32:27 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{


//		RBtree_node

// public methods

template<typename T>
RBtree_node<T>::RBtree_node(): _color(black), _data(), _parent(), _left(), _right() {}

template<typename T>
RBtree_node<T>::RBtree_node(const RBtree_node& other):
	_color(other._color), _data(other._data), _parent(other._parent),
	_left(other._left), _right(other._right) {}

template<typename T>
RBtree_node<T>::~RBtree_node() {}

template<typename T>
RBtree_node<T>&
RBtree_node<T>::operator=(const RBtree_node& other)
{
	if (this != &other)
	{
		this->_color = other._color;
		this->_data = other._data;
		this->_parent = other._parent;
		this->_left = other._left;
		this->_right = other._right;
	}
	return *this;
}

template<typename T>
void
RBtree_node<T>::flip_color()
{
	this->_color = this->_color == red ? black : red;
}


//		tree utility functions

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


//		tree_iterator

// public methods

template<typename Node_ptr, typename Value>
tree_iterator<Node_ptr,Value>::tree_iterator(): _current_node() {}

template<typename Node_ptr, typename Value>
tree_iterator<Node_ptr,Value>::tree_iterator(const tree_iterator& other):
	_current_node(other._current_node) {}

template<typename Node_ptr, typename Value>
tree_iterator<Node_ptr,Value>::tree_iterator(const Node_ptr& val):
	_current_node(val) {}

template<typename Node_ptr, typename Value>
tree_iterator<Node_ptr,Value>&
tree_iterator<Node_ptr,Value>::operator=(const tree_iterator& other)
{
	if (this != &other)
		this->_current_node = other._current_node;
	return *this;
}

template<typename Node_ptr, typename Value>
tree_iterator<Node_ptr,Value>&
tree_iterator<Node_ptr,Value>::operator=(const Node_ptr& ptr)
{
	this->_current_node = ptr;
	return *this;
}

template<typename Node_ptr, typename Value>
typename tree_iterator<Node_ptr,Value>::reference
tree_iterator<Node_ptr,Value>::operator*() const
{
	return _current_node->_data;
}

template<typename Node_ptr, typename Value>
typename tree_iterator<Node_ptr,Value>::pointer
tree_iterator<Node_ptr,Value>::operator->() const
{
	return &_current_node->_data;
}

template<typename Node_ptr, typename Value>
tree_iterator<Node_ptr,Value>&
tree_iterator<Node_ptr,Value>::operator++()
{
	if (_current_node->_right != nullptr)
		_current_node = tree_min<value_type>(_current_node->_right);
	else
	{
		while (!tree_is_left_child<value_type>(_current_node))
		{
			_current_node = _current_node->_parent;
		}
		_current_node = _current_node->_parent;
	}
	return *this;
}

template<typename Node_ptr, typename Value>
tree_iterator<Node_ptr,Value>
tree_iterator<Node_ptr,Value>::operator++(int)
{
	tree_iterator ret(*this);
	++(*this);
	return ret;
}

template<typename Node_ptr, typename Value>
tree_iterator<Node_ptr,Value>&
tree_iterator<Node_ptr,Value>::operator--()
{
	if (_current_node->_left != nullptr)
		_current_node = tree_max<value_type>(_current_node->_left);
	else
	{
		while (tree_is_left_child<value_type>(_current_node))
			_current_node = _current_node->_parent;
		_current_node = _current_node->_parent;
	}
	return *this;
}

template<typename Node_ptr, typename Value>
tree_iterator<Node_ptr,Value>
tree_iterator<Node_ptr,Value>::operator--(int)
{
	tree_iterator ret(*this);
	--(*this);
	return ret;
}

template<typename Node_ptr, typename Value>
Node_ptr
tree_iterator<Node_ptr,Value>::base() const
{
	return _current_node;
}


//		const_tree_iterator

// public methods

template<typename Const_node_ptr, typename Value>
const_tree_iterator<Const_node_ptr,Value>::const_tree_iterator(): _current_node() {}

template<typename Const_node_ptr, typename Value>
const_tree_iterator<Const_node_ptr,Value>::const_tree_iterator(const const_tree_iterator& other):
	_current_node(other._current_node) {}

template<typename Const_node_ptr, typename Value>
const_tree_iterator<Const_node_ptr,Value>::const_tree_iterator(const normal_tree_iterator& other):
	_current_node(other.base()) {}

template<typename Const_node_ptr, typename Value>
const_tree_iterator<Const_node_ptr,Value>::const_tree_iterator(const Const_node_ptr& val):
	_current_node(val) {}

template<typename Const_node_ptr, typename Value>
const_tree_iterator<Const_node_ptr,Value>&
const_tree_iterator<Const_node_ptr,Value>::operator=(const const_tree_iterator& other)
{
	if (this != &other)
		this->_current_node = other._current_node;
	return *this;
}

// template<typename Const_node_ptr, typename Value>
// const_tree_iterator<Const_node_ptr,Value>&
// const_tree_iterator<Const_node_ptr,Value>::operator=(const normal_tree_iterator& other)
// {
// 	this->_current_node = other._current_node;
// 	return *this;
// }

template<typename Const_node_ptr, typename Value>
const_tree_iterator<Const_node_ptr,Value>&
const_tree_iterator<Const_node_ptr,Value>::operator=(const Const_node_ptr& ptr)
{
	this->_current_node = ptr;
	return *this;
}

template<typename Const_node_ptr, typename Value>
typename const_tree_iterator<Const_node_ptr,Value>::reference
const_tree_iterator<Const_node_ptr,Value>::operator*() const
{
	return _current_node->_data;
}

template<typename Const_node_ptr, typename Value>
typename const_tree_iterator<Const_node_ptr,Value>::pointer
const_tree_iterator<Const_node_ptr,Value>::operator->() const
{
	return &_current_node->_data;
}

template<typename Const_node_ptr, typename Value>
const_tree_iterator<Const_node_ptr,Value>&
const_tree_iterator<Const_node_ptr,Value>::operator++()
{
	if (_current_node->_right != nullptr)
		_current_node = tree_min<value_type>(_current_node->_right);
	else
	{
		while (!tree_is_left_child<value_type>(_current_node))
		{
			_current_node = _current_node->_parent;
		}
		_current_node = _current_node->_parent;
	}
	return *this;
}

template<typename Const_node_ptr, typename Value>
const_tree_iterator<Const_node_ptr,Value>
const_tree_iterator<Const_node_ptr,Value>::operator++(int)
{
	const_tree_iterator ret(*this);
	++(*this);
	return ret;
}

template<typename Const_node_ptr, typename Value>
const_tree_iterator<Const_node_ptr,Value>&
const_tree_iterator<Const_node_ptr,Value>::operator--()
{
	if (_current_node->_left != nullptr)
		_current_node = tree_max<value_type>(_current_node->_left);
	else
	{
		while (tree_is_left_child<value_type>(_current_node))
			_current_node = _current_node->_parent;
		_current_node = _current_node->_parent;
	}
	return *this;
}

template<typename Const_node_ptr, typename Value>
const_tree_iterator<Const_node_ptr,Value>
const_tree_iterator<Const_node_ptr,Value>::operator--(int)
{
	const_tree_iterator ret(*this);
	--(*this);
	return ret;
}

template<typename Const_node_ptr, typename Value>
Const_node_ptr
const_tree_iterator<Const_node_ptr,Value>::base() const
{
	return _current_node;
}


//		RBtree

// public methods

// constructors / destructor

template<typename T, typename Compare, typename Alloc>
RBtree<T,Compare,Alloc>::RBtree(const value_compare& comp, const allocator_type& alloc):
	_size(), _parent(), _begin_node(&_parent), _comp(comp),
	_allocator(alloc), _node_allocator(alloc) {}

template<typename T, typename Compare, typename Alloc>
RBtree<T,Compare,Alloc>::RBtree(const RBtree& other):
	_size(), _parent(), _begin_node(&_parent), _comp(other._comp),
	_allocator(other._allocator), _node_allocator(other._node_allocator)
{
	if (other._root() != nullptr)
	{
		this->_root() = this->_copy(other._root());
		this->_root()->_parent = &this->_parent;
	}
}

template<typename T, typename Compare, typename Alloc>
RBtree<T,Compare,Alloc>::~RBtree()
{
	if (this->_root() != nullptr)
	{
		this->_destroy(this->_root());
		this->_root() = nullptr;
		this->_begin_node = this->_end_node();
	}
}


// operator overload

template<typename T, typename Compare, typename Alloc>
RBtree<T,Compare,Alloc>&
RBtree<T,Compare,Alloc>::operator=(const RBtree& other)
{
	if (this != &other)
	{
		this->clear();
		this->_comp = other._comp;
		if (other._root() != nullptr)
		{
			this->_root() = this->_copy(other._root());
			this->_root()->_parent = &this->_parent;
		}
	}
	return *this;
}


// iterators

template<typename T, typename Compare, typename Alloc>
typename RBtree<T,Compare,Alloc>::iterator
RBtree<T,Compare,Alloc>::begin()
{
	return iterator(this->_begin_node);
}

template<typename T, typename Compare, typename Alloc>
typename RBtree<T,Compare,Alloc>::const_iterator
RBtree<T,Compare,Alloc>::begin() const
{
	return const_iterator(this->_begin_node);
}

template<typename T, typename Compare, typename Alloc>
typename RBtree<T,Compare,Alloc>::iterator
RBtree<T,Compare,Alloc>::end()
{

	return iterator(&this->_parent);
}

template<typename T, typename Compare, typename Alloc>
typename RBtree<T,Compare,Alloc>::const_iterator
RBtree<T,Compare,Alloc>::end() const
{
	return const_iterator(&this->_parent);
}

template<typename T, typename Compare, typename Alloc>
typename RBtree<T,Compare,Alloc>::reverse_iterator
RBtree<T,Compare,Alloc>::rbegin()
{
	return reverse_iterator(this->end());
}

template<typename T, typename Compare, typename Alloc>
typename RBtree<T,Compare,Alloc>::const_reverse_iterator
RBtree<T,Compare,Alloc>::rbegin() const
{
	return const_reverse_iterator(this->end());
}

template<typename T, typename Compare, typename Alloc>
typename RBtree<T,Compare,Alloc>::reverse_iterator
RBtree<T,Compare,Alloc>::rend()
{
	return reverse_iterator(this->begin());
}

template<typename T, typename Compare, typename Alloc>
typename RBtree<T,Compare,Alloc>::const_reverse_iterator
RBtree<T,Compare,Alloc>::rend() const
{
	return const_reverse_iterator(this->begin());
}


// capacity

template<typename T, typename Compare, typename Alloc>
bool
RBtree<T,Compare,Alloc>::empty() const
{
	return this->_size == 0;
}

template<typename T, typename Compare, typename Alloc>
typename RBtree<T,Compare,Alloc>::size_type
RBtree<T,Compare,Alloc>::size() const
{
	return this->_size;
}

template<typename T, typename Compare, typename Alloc>
typename RBtree<T,Compare,Alloc>::size_type
RBtree<T,Compare,Alloc>::max_size() const
{
	return this->_allocator.max_size();
}


// modifiers

template<typename T, typename Compare, typename Alloc>
ft::pair<typename RBtree<T,Compare,Alloc>::iterator,bool>
RBtree<T,Compare,Alloc>::insert(const value_type& val)
{
	node_ptr new_node = this->_construct_node(val);
	bool inserted = false;
	iterator pos;
	this->_root() = this->_insert(this->_root(), new_node, inserted, pos);
	this->_root()->_parent = &this->_parent;
	if (!inserted)
		this->_destroy_node(new_node);
	else
		this->_rebalance_after_insertion(new_node);
	this->_root()->_color = black;
	return ft::make_pair(pos, inserted);
}

template<typename T, typename Compare, typename Alloc>
typename RBtree<T,Compare,Alloc>::iterator
RBtree<T,Compare,Alloc>::insert(iterator position, const value_type& val) // room for optimisation
{
	return this->insert(val).first;
	(void)position;
}

template<typename T, typename Compare, typename Alloc>
template<typename InputIterator>
void
RBtree<T,Compare,Alloc>::insert(InputIterator first, InputIterator last)
{
	for(; first != last; ++first)
		this->insert(*first);
}

template<typename T, typename Compare, typename Alloc>
void
RBtree<T,Compare,Alloc>::erase(iterator position)
{
	node_ptr pos = position.base();
	if (pos == this->_begin_node)
	{
		++position;
		this->_begin_node = position.base();
	}
	this->_erase(this->_root(), pos);
	if (this->_root() != nullptr)
	{
		this->_root()->_parent = this->_end_node();
		this->_root()->_color = black;
	}
	this->_destroy_node(pos);
}

template<typename T, typename Compare, typename Alloc>
typename RBtree<T,Compare,Alloc>::size_type
RBtree<T,Compare,Alloc>::erase(const value_type& val)
{
	iterator pos = this->find(val);
	if (pos == this->end())
		return 0;
	this->erase(pos);
	return 1;
}

template<typename T, typename Compare, typename Alloc>
void
RBtree<T,Compare,Alloc>::erase(iterator first, iterator last)
{
	for (; first != last; ++first)
		this->erase(first);
}

template<typename T, typename Compare, typename Alloc>
void
RBtree<T,Compare,Alloc>::swap(RBtree& other)
{
	ft::swap(this->_begin_node, other._begin_node);
	ft::swap(this->_parent->_left, other._parent->_left);
	ft::swap(this->_size, other._size);
	ft::swap(this->_comp, other._comp);
}


template<typename T, typename Compare, typename Alloc>
void
RBtree<T,Compare,Alloc>::clear()
{
	if (this->_root() != nullptr)
	{
		this->_destroy(this->_root());
		this->_root() = nullptr;
		this->_begin_node = this->_end_node();
	}
}


// observer

template<typename T, typename Compare, typename Alloc>
typename RBtree<T,Compare,Alloc>::value_compare
RBtree<T,Compare,Alloc>::value_comp() const
{
	return this->_comp;
}


// operations

template<typename T, typename Compare, typename Alloc>
typename RBtree<T,Compare,Alloc>::iterator
RBtree<T,Compare,Alloc>::find(const value_type& val)
{
	node_ptr node = this->_root();

	while (node != nullptr)
	{
		if (this->_comp(node->_data, val))
			node = node->_right;
		else if (this->_comp(val, node->_data))
			node = node->_left;
		else
			return iterator(node);
	}
	return this->end();
}

template<typename T, typename Compare, typename Alloc>
typename RBtree<T,Compare,Alloc>::const_iterator
RBtree<T,Compare,Alloc>::find(const value_type& val) const
{
	const_node_ptr node = this->_root();

	while (node != nullptr)
	{
		if (this->_comp(node->_data, val))
			node = node->_right;
		else if (this->_comp(val, node->_data))
			node = node->_left;
		else
			return const_iterator(node);
	}
	return this->end();
}

template<typename T, typename Compare, typename Alloc>
typename RBtree<T,Compare,Alloc>::size_type
RBtree<T,Compare,Alloc>::count(const value_type& val) const
{
	return this->find(val) == this->end() ? 0 : 1;
}

template<typename T, typename Compare, typename Alloc>
typename RBtree<T,Compare,Alloc>::iterator
RBtree<T,Compare,Alloc>::lower_bound(const value_type& val)
{
	node_ptr node = this->_root();
	node_ptr pos = this->_end_node();

	while (node != nullptr)
	{
		if (!this->_comp(node->_data, val))
		{
			pos = node;
			node = node->_left;
		}
		else
			node = node->_right;
	}
	return iterator(pos);
}

template<typename T, typename Compare, typename Alloc>
typename RBtree<T,Compare,Alloc>::const_iterator
RBtree<T,Compare,Alloc>::lower_bound(const value_type& val) const
{
	const_node_ptr node = this->_root();
	const_node_ptr pos = this->_end_node();

	while (node != nullptr)
	{
		if (!this->_comp(node->_data, val))
		{
			pos = node;
			node = node->_left;
		}
		else
			node = node->_right;
	}
	return const_iterator(pos);
}

template<typename T, typename Compare, typename Alloc>
typename RBtree<T,Compare,Alloc>::iterator
RBtree<T,Compare,Alloc>::upper_bound(const value_type& val)
{
	node_ptr node = this->_root();
	node_ptr pos = this->_end_node();

	while (node != nullptr)
	{
		if (this->_comp(val, node->_data))
		{
			pos = node;
			node = node->_left;
		}
		else
			node = node->_right;
	}
	return iterator(pos);
}

template<typename T, typename Compare, typename Alloc>
typename RBtree<T,Compare,Alloc>::const_iterator
RBtree<T,Compare,Alloc>::upper_bound(const value_type& val) const
{
	const_node_ptr node = this->_root();
	const_node_ptr pos = this->_end_node();

	while (node != nullptr)
	{
		if (this->_comp(val, node->_data))
		{
			pos = node;
			node = node->_left;
		}
		else
			node = node->_right;
	}
	return const_iterator(pos);
}

template<typename T, typename Compare, typename Alloc>
ft::pair<typename RBtree<T,Compare,Alloc>::iterator,
		typename RBtree<T,Compare,Alloc>::iterator>
RBtree<T,Compare,Alloc>::equal_range(const value_type& val)
{
	node_ptr node = this->_root();
	node_ptr pos = this->_end_node();

	while (node != nullptr)
	{
		if (this->_comp(val, node->_data))
		{
			pos = node;
			node = node->_left;
		}
		else if (this->_comp(node->_data, val))
			node = node->_right;
		else
			return ft::make_pair(iterator(node), iterator(
				node->_right == nullptr ? pos : tree_min<value_type>(node->_right)));
	}
	return ft::make_pair(iterator(pos), iterator(pos));
}

template<typename T, typename Compare, typename Alloc>
ft::pair<typename RBtree<T,Compare,Alloc>::const_iterator,
		typename RBtree<T,Compare,Alloc>::const_iterator>
RBtree<T,Compare,Alloc>::equal_range(const value_type& val) const
{
	const_node_ptr node = this->_root();
	const_node_ptr pos = this->_end_node();

	while (node != nullptr)
	{
		if (this->_comp(val, node->_data))
		{
			pos = node;
			node = node->_left;
		}
		else if (this->_comp(node->_data, val))
			node = node->_right;
		else
			return ft::make_pair(const_iterator(node), const_iterator(
				node->_right == nullptr ? pos : tree_min<value_type>(node->_right)));
	}
	return ft::make_pair(const_iterator(pos), const_iterator(pos));
}


// allocator

template<typename T, typename Compare, typename Alloc>
typename RBtree<T,Compare,Alloc>::allocator_type
RBtree<T,Compare,Alloc>::get_allocator() const
{
	return this->_allocator;
}


// private methods

// utility

template<typename T, typename Compare, typename Alloc>
typename RBtree<T,Compare,Alloc>::const_node_ptr&
RBtree<T,Compare,Alloc>::_root() const
{
	return const_cast<const_node_ptr&>(this->_parent._left);
}

template<typename T, typename Compare, typename Alloc>
typename RBtree<T,Compare,Alloc>::node_ptr&
RBtree<T,Compare,Alloc>::_root()
{
	return this->_parent._left;
}

template<typename T, typename Compare, typename Alloc>
typename RBtree<T,Compare,Alloc>::const_node_ptr
RBtree<T,Compare,Alloc>::_end_node() const
{
	return const_cast<const_node_ptr>(&this->_parent);
}

template<typename T, typename Compare, typename Alloc>
typename RBtree<T,Compare,Alloc>::node_ptr
RBtree<T,Compare,Alloc>::_end_node()
{
	return &this->_parent;
}

template<typename T, typename Compare, typename Alloc>
typename RBtree<T,Compare,Alloc>::node_ptr
RBtree<T,Compare,Alloc>::_get_sibling(node_ptr node) const
{
	if (tree_is_left_child<value_type>(node))
		return node->_parent->_right;
	else
		return node->_parent->_left;
}

template<typename T, typename Compare, typename Alloc>
typename RBtree<T,Compare,Alloc>::node_ptr
RBtree<T,Compare,Alloc>::_replacement_node(node_ptr node) const
{
	if (node->_left == nullptr || node->_right == nullptr)
		return node;
	else
		return tree_min<value_type>(node->_right);
}


template<typename T, typename Compare, typename Alloc>
node_color
RBtree<T,Compare,Alloc>::_get_node_color(node_ptr node) const
{
	if (node == nullptr)
		return black;
	return node->_color;
}

template<typename T, typename Compare, typename Alloc>
void
RBtree<T,Compare,Alloc>::_rotate_left(node_ptr node)
{
	node_ptr right_node = node->_right;
	node->_right = right_node->_left;
	if (node->_right != nullptr)
		node->_right->_parent = node;
	right_node->_parent = node->_parent;
	if (tree_is_left_child<value_type>(node))
		node->_parent->_left = right_node;
	else
		node->_parent->_right = right_node;
	right_node->_left = node;
	node->_parent = right_node;
}

template<typename T, typename Compare, typename Alloc>
void
RBtree<T,Compare,Alloc>::_rotate_right(node_ptr node)
{
	node_ptr left_node = node->_left;
	node->_left = left_node->_right;
	if (node->_left != nullptr)
		node->_left->_parent = node;
	left_node->_parent = node->_parent;
	if (tree_is_left_child<value_type>(node))
		node->_parent->_left = left_node;
	else
		node->_parent->_right = left_node;
	left_node->_right = node;
	node->_parent = left_node;
}


// insertion

template<typename T, typename Compare, typename Alloc>
typename RBtree<T,Compare,Alloc>::node_ptr
RBtree<T,Compare,Alloc>::_construct_node(const value_type& data)
{
	node_ptr new_node = this->_node_allocator.allocate(1);
	this->_allocator.construct(&new_node->_data, data);
	new_node->_color = red;
	new_node->_parent = nullptr;
	new_node->_left = nullptr;
	new_node->_right = nullptr;
	if (this->empty() || this->_comp(data, this->_begin_node->_data))
		this->_begin_node = new_node;
	++this->_size;
	return new_node;
}

template<typename T, typename Compare, typename Alloc>
typename RBtree<T,Compare,Alloc>::node_ptr
RBtree<T,Compare,Alloc>::_copy(const_node_ptr node)
{
	if (node == nullptr)
		return nullptr;
	node_ptr new_node = this->_construct_node(node->_data);
	new_node->_left = _copy(node->_left);
	if (new_node->_left != nullptr)
		new_node->_left->_parent = new_node;
	new_node->_right = _copy(node->_right);
	if (new_node->_right != nullptr)
		new_node->_right->_parent = new_node;
	return new_node;
}

template<typename T, typename Compare, typename Alloc>
typename RBtree<T,Compare,Alloc>::node_ptr
RBtree<T,Compare,Alloc>::_insert(node_ptr node, node_ptr new_node,
									bool& inserted, iterator& pos)
{
	if (node == nullptr)
	{
		pos = new_node;
		inserted = true;
		return new_node;
	}
	if (this->_comp(node->_data, new_node->_data)) // greater than
	{
		node->_right = _insert(node->_right, new_node, inserted, pos);
		node->_right->_parent = node;
	}
	else if (this->_comp(new_node->_data, node->_data)) // less than
	{
		node->_left = _insert(node->_left, new_node, inserted, pos);
		node->_left->_parent = node;
	}
	else // equal
	{
		pos = node;
		inserted = false;
	}
	return node;
}

template<typename T, typename Compare, typename Alloc>
void
RBtree<T,Compare,Alloc>::_rebalance_after_insertion(node_ptr node)
{
	while (node != this->_root() && this->_get_node_color(node->_parent) == red) // Case 1 and 2
	{
		node_ptr uncle = this->_get_sibling(node->_parent);
		if (this->_get_node_color(uncle) == red) // Case 3
		{
			uncle->flip_color();
			node = node->_parent;
			node->flip_color();
			node = node->_parent;
			node->flip_color();
		}
		else if (tree_is_left_child<value_type>(node->_parent)) // Case 4
		{
			if (!tree_is_left_child<value_type>(node)) // Case 4.1
			{
				node = node->_parent;
				this->_rotate_left(node);
			}
			node = node->_parent; // Case 4.2
			node->flip_color();
			node = node->_parent;
			node->flip_color();
			this->_rotate_right(node);
			break;
		}
		else // Case 4
		{
			if (tree_is_left_child<value_type>(node)) // Case 4.3
			{
				node = node->_parent;
				this->_rotate_right(node);
			}
			node = node->_parent; // Case 4.4
			node->flip_color();
			node = node->_parent;
			node->flip_color();
			this->_rotate_left(node);
			break;
		}
	}
}


// erasion

template<typename T, typename Compare, typename Alloc>
void
RBtree<T,Compare,Alloc>::_destroy_node(node_ptr node)
{
	this->_allocator.destroy(&node->_data);
	this->_node_allocator.deallocate(node, 1);
	--this->_size;
}

template<typename T, typename Compare, typename Alloc>
void
RBtree<T,Compare,Alloc>::_destroy(node_ptr node)
{
	if (node == nullptr)
		return;
	_destroy(node->_left);
	_destroy(node->_right);
	this->_destroy_node(node);
}

/*
					Node name lookup table for RBtree::_erase:

-> see RBtree::_erase in RBtree.tpp

*	many guides aren't very verbose, so they just call the nodes w, x, y and z.
	I decided to be a bit more verbose, so here's a lookup table if the names are
	confusing:
*	root: The root of the tree
*	node: The node to be deleted (also known as z)
*	repl: The successor of node or if node had either no children or one child,
			the same as node. It's the leaf-node node will be replaced by
			(also known as y)
*	repl_child: The child of repl (also known as x)
				It's null if repl had no children.
				It's the first node to be marked as double black if it was
				black before.
				In the rebalancing part, it will be referred to as db_node,
				since it's the double black node
*	sibling: The sibling of repl_child (also known as w).
			Case 3, 4, 5 and 6 will be chosen according to his color
			and the colors of his children.
			It is also the node responsible for the heavy lifting in the
			rebalancing part, since repl_child is might be null
*/

template<typename T, typename Compare, typename Alloc>
void
RBtree<T,Compare,Alloc>::_erase(node_ptr root, node_ptr node)
{
	node_ptr repl = this->_replacement_node(node);
	node_ptr repl_child = repl->_left == nullptr ? repl->_right : repl->_left;
	node_ptr sibling = nullptr;
	if (repl_child != nullptr)
		repl_child->_parent = repl->_parent;
	if (tree_is_left_child<value_type>(repl))
	{
		repl->_parent->_left = repl_child;
		if (repl == root)
			root = repl_child; // sibling will be null in this case
		else
			sibling = repl->_parent->_right;
	}
	else
	{
		// root can't be this->_parent's right child
		repl->_parent->_right = repl_child;
		sibling = repl->_parent->_left;
	}
	node_color repl_color = repl->_color;
	if (repl != node) // copy the contents of node into repl
	{
		repl->_parent = node->_parent;
		if (tree_is_left_child<value_type>(node))
			repl->_parent->_left = repl;
		else
			repl->_parent->_right = repl;
		repl->_left = node->_left;
		repl->_left->_parent = repl;
		repl->_right = node->_right;
		if (repl->_right != nullptr)
			repl->_right->_parent = repl;
		repl->_color = node->_color;
		if (node == root)
			root = repl;
		
	}
	// we don't need to rebalance if we removed a red node or if there are no
	// more nodes in the tree
	if (repl_color == black && root != nullptr) // Case 1
	{
		// repl had either no children or one red child (repl_child).
		// so, if repl_child != nullptr it is either red or root.
		// root can't be double black and a red node will be flipped
		// to black
		if (repl_child != nullptr) // Case 2
			repl_child->_color = black;
		else
			this->_rebalance_before_erasion(root, repl_child, sibling); // repl_child is always null at the start
	}
}


template<typename T, typename Compare, typename Alloc>
void
RBtree<T,Compare,Alloc>::_rebalance_before_erasion(node_ptr root, node_ptr db_node, node_ptr sibling)
{
	while (true) // == (node != root && this->_get_node_color(node) == black)
	{
		if (!tree_is_left_child<value_type>(sibling)) // == tree_is_left_child(node)
		{
			if (this->_get_node_color(sibling) == red) // Case 3
			{
				sibling->flip_color();
				sibling->_parent->flip_color();
				this->_rotate_left(sibling->_parent);
				if (root == sibling->_left)
					root = sibling;
				sibling = sibling->_left->_right;
			}
			if (this->_get_node_color(sibling->_left) == black &&
				this->_get_node_color(sibling->_right) == black) // Case 4
			{
				sibling->flip_color();
				db_node = sibling->_parent;
				if (db_node == root || this->_get_node_color(db_node) == red)
				{
					db_node->_color = black;
					break;
				}
				sibling = this->_get_sibling(db_node);
			}
			else // sibling has one red child
			{
				if (this->_get_node_color(sibling->_right) == black) // Case 5
				{
					sibling->_left->flip_color(); // the left child is red
					sibling->flip_color();
					this->_rotate_right(sibling);
					sibling = sibling->_parent;
				}
				sibling->_color = sibling->_parent->_color; // Case 6
				sibling->_parent->_color = black;
				sibling->_right->_color = black;
				this->_rotate_left(sibling->_parent);
				break;
			}
		}
		else // the same as before, but in reverse order
		{
			if (this->_get_node_color(sibling) == red) // Case 3
			{
				sibling->flip_color();
				sibling->_parent->flip_color();
				this->_rotate_right(sibling->_parent);
				if (root == sibling->_right)
					root = sibling;
				sibling = sibling->_right->_left;
			}
			if (this->_get_node_color(sibling->_left) == black &&
				this->_get_node_color(sibling->_right) == black) // Case 4
			{
				sibling->flip_color();
				db_node = sibling->_parent;
				if (db_node == root || this->_get_node_color(db_node) == red)
				{
					db_node->_color = black;
					break;
				}
				sibling = this->_get_sibling(db_node);
			}
			else // sibling has one red child
			{
				if (this->_get_node_color(sibling->_left) == black) // Case 5
				{
					sibling->_right->flip_color(); // the right child is red
					sibling->flip_color();
					this->_rotate_left(sibling);
					sibling = sibling->_parent;
				}
				sibling->_color = sibling->_parent->_color; // Case 6
				sibling->_parent->_color = black;
				sibling->_left->_color = black;
				this->_rotate_right(sibling->_parent);
				break;
			}
		}
	}
}


} // namespace ft