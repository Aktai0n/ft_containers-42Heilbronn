/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:06:31 by skienzle          #+#    #+#             */
/*   Updated: 2022/02/17 22:48:22 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include <iostream>

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

	RBtree_node();
	RBtree_node(const RBtree_node& other);

	~RBtree_node();

	RBtree_node& operator=(const RBtree_node& other);

	void flip_color();

	void print_node() const
	{
		std::cout << "color: " << (_color == black ? "black" : "red") << '\n'
			<< "data: " << _data.first << ' ' << _data.second << '\n'
			<< "parent: " << _parent << "\nleft: " << _left
			<< "\nright: " << _right << "\nnode addr: " << this << std::endl;
	}

	node_color	_color;
	value_type	_data;
	node_ptr	_parent;
	node_ptr	_left;
	node_ptr	_right;
};

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



// tree_iterator

template<typename Node_ptr, typename Value>
class tree_iterator
{
public: // types
	typedef bidirectional_iterator_tag		iterator_category;
	typedef Value							value_type;
	typedef ptrdiff_t						difference_type;
	typedef Value*							pointer;
	typedef Value&							reference;

public: // methods
	// constructors
	tree_iterator();
	tree_iterator(const tree_iterator& other);
	tree_iterator(const Node_ptr& val);
	// operator overloads
	tree_iterator&	operator=(const tree_iterator& other);
	tree_iterator&	operator=(const Node_ptr& ptr);
	reference		operator*() const;
	pointer			operator->() const;
	tree_iterator&	operator++();
	tree_iterator	operator++(int);
	tree_iterator&	operator--();
	tree_iterator	operator--(int);

	Node_ptr	base() const;

private: // attributes
	Node_ptr _current_node;
};

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

// needs testing!
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

// also needs testing!
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


// relational operator overloads for tree_iterator

template<typename Node_ptr, typename Value>
inline bool
operator==(const tree_iterator<Node_ptr,Value>& rhs,
			const tree_iterator<Node_ptr,Value>& lhs)
{
	return rhs.base() == lhs.base();
}

template<typename Node_ptr, typename Value>
inline bool
operator!=(const tree_iterator<Node_ptr,Value>& rhs,
			const tree_iterator<Node_ptr,Value>& lhs)
{
	return rhs.base() != lhs.base();
}

// const_tree_iterator

template<typename Const_node_ptr, typename Value>
class const_tree_iterator
{
public: // types
	typedef bidirectional_iterator_tag		iterator_category;
	typedef Value							value_type;
	typedef ptrdiff_t						difference_type;
	typedef const Value*					pointer;
	typedef const Value&					reference;

private: // types
	typedef tree_iterator<RBtree_node<Value>,Value>	normal_tree_iterator;
public: // methods
	// constructors
	const_tree_iterator();
	const_tree_iterator(const const_tree_iterator& other);
	const_tree_iterator(const normal_tree_iterator& other);
	const_tree_iterator(const Const_node_ptr& val);
	// operator overloads
	const_tree_iterator&	operator=(const const_tree_iterator& other);
	const_tree_iterator&	operator=(const normal_tree_iterator& other);
	const_tree_iterator&	operator=(const Const_node_ptr& ptr);
	reference		operator*() const;
	pointer			operator->() const;
	const_tree_iterator&	operator++();
	const_tree_iterator	operator++(int);
	const_tree_iterator&	operator--();
	const_tree_iterator	operator--(int);

	Const_node_ptr	base() const;

private: // attributes
	Const_node_ptr _current_node;
};

template<typename Const_node_ptr, typename Value>
const_tree_iterator<Const_node_ptr,Value>::const_tree_iterator(): _current_node() {}

template<typename Const_node_ptr, typename Value>
const_tree_iterator<Const_node_ptr,Value>::const_tree_iterator(const const_tree_iterator& other):
	_current_node(other._current_node) {}

template<typename Const_node_ptr, typename Value>
const_tree_iterator<Const_node_ptr,Value>::const_tree_iterator(const normal_tree_iterator& other):
	_current_node(other._current_node) {}

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

template<typename Const_node_ptr, typename Value>
const_tree_iterator<Const_node_ptr,Value>&
const_tree_iterator<Const_node_ptr,Value>::operator=(const normal_tree_iterator& other)
{
	this->_current_node = other._current_node;
	return *this;
}

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


// relational operator overloads for const_tree_iterator

template<typename Const_node_ptr, typename Value>
inline bool
operator==(const const_tree_iterator<Const_node_ptr,Value>& rhs,
			const const_tree_iterator<Const_node_ptr,Value>& lhs)
{
	return rhs.base() == lhs.base();
}

template<typename Const_node_ptr, typename Value>
inline bool
operator!=(const const_tree_iterator<Const_node_ptr,Value>& rhs,
			const const_tree_iterator<Const_node_ptr,Value>& lhs)
{
	return rhs.base() != lhs.base();
}


// RBtree

template<typename T, typename Compare, typename Alloc>
class RBtree: public Itree<T,Compare,Alloc>
{
private: // types
	typedef Itree<T,Compare,Alloc>						interface_type;
	typedef RBtree_node<T>								node_type;
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

	typedef ft::tree_iterator<node_ptr,value_type>										iterator;
	typedef ft::const_tree_iterator<const_node_ptr,value_type>							const_iterator;
	typedef ft::reverse_iterator<iterator>												reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>										const_reverse_iterator;
	

public: // methods
	// constructors

	explicit RBtree(const value_compare& comp, const allocator_type& alloc);
	RBtree(const RBtree& other);


	// destructor

	~RBtree();

	// operator overload

	RBtree& operator=(const RBtree& other);

	// iterators

	iterator				begin();
	const_iterator			begin() const;
	iterator				end();
	const_iterator			end() const;
	reverse_iterator		rbegin();
	const_reverse_iterator	rbegin() const;
	reverse_iterator		rend();
	const_reverse_iterator	rend() const;

	// capacity

	bool		empty() const;
	size_type	size() const;
	size_type	max_size() const;

	// modifiers

	// void insert(const value_type& val); // dummy
	ft::pair<iterator,bool>		insert(const value_type& val);
	iterator					insert(iterator position, const value_type& val);
	template<typename InputIterator>
		void					insert(InputIterator first, InputIterator last);
	void						erase(iterator position);
	size_type					erase(const value_type& val);
	void						erase(iterator first, iterator last);
	void						swap(RBtree& other);
	void						clear();


	// observers

	value_compare	value_comp() const;

	// operations

	iterator									find(const value_type& val);
	const_iterator								find(const value_type& val) const;
	size_type									count(const value_type& val) const;
	iterator									lower_bound(const value_type& val);
	const_iterator								lower_bound(const value_type& val) const;
	iterator									upper_bound(const value_type& val);
	const_iterator								upper_bound(const value_type& val) const;
	ft::pair<iterator,iterator>					equal_range(const value_type& val);
	ft::pair<const_iterator,const_iterator>		equal_range(const value_type& val) const;

	// allocator

	allocator_type	get_allocator() const;

	
private: // methods
	const_node_ptr&	_root() const;
	node_ptr&		_root();
	const_node_ptr	_end_node() const;
	node_ptr		_end_node();
	node_ptr		_construct_node(const value_type& data);
	void			_destroy_node(node_ptr node);
	node_ptr		_insert(node_ptr node, node_ptr new_node, bool& inserted, iterator& pos);
	void			_rebalance_after_insertion(node_ptr node);
	void			_rotate_right(node_ptr node);
	void			_rotate_left(node_ptr node);
	node_ptr		_erase(node_ptr node, const value_type& val, bool& deleted);
	node_ptr		_copy(node_ptr node);
	void			_destroy(node_ptr node);
	bool			_equals(const value_type& first, const value_type& second) const;
	void print_tree(const node_ptr node) const
	{
		if (node == nullptr)
			return;
		node->print_node();
		print_tree(node->_left);
		print_tree(node->_right);
	}
private: // attributes
	size_type			_size;
	node_type			_parent; // _parent->_left is the root
	node_ptr			_begin_node;
	value_compare		_comp;
	allocator_type		_allocator;
	node_allocator_type	_node_allocator;
};

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
		this->_root() = this->_copy(other._parent._left);
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
	}
}

template<typename T, typename Compare, typename Alloc>
RBtree<T,Compare,Alloc>&
RBtree<T,Compare,Alloc>::operator=(const RBtree& other)
{
	if (this != &other)
	{
		this->_destroy(this->_root());
		this->_comp = other._comp;
		if (other._root() != nullptr)
		{
			this->_root() = this->_copy(other._parent._left);
			this->_root()->_parent = &this->_parent;
		}
		else
			this->_root() = nullptr;
	}
	return *this;
}

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
		this->_insert(*first);
}

template<typename T, typename Compare, typename Alloc>
void
RBtree<T,Compare,Alloc>::erase(iterator position) // room for optimisation
{
	this->erase(*position);
}

template<typename T, typename Compare, typename Alloc>
typename RBtree<T,Compare,Alloc>::size_type
RBtree<T,Compare,Alloc>::erase(const value_type& val)
{
	size_type old_size = this->_size;
	bool deleted = false;
	this->_root() = this->_erase(this->_root(), val, deleted);
	this->_root()->_parent = &this->_parent;
	return old_size - this->_size;
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
	ft::swap(this->_parent, other._parent);
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


template<typename T, typename Compare, typename Alloc>
typename RBtree<T,Compare,Alloc>::value_compare
RBtree<T,Compare,Alloc>::value_comp() const
{
	return this->_comp;
}

template<typename T, typename Compare, typename Alloc>
typename RBtree<T,Compare,Alloc>::iterator
RBtree<T,Compare,Alloc>::find(const value_type& val)
{
	node_ptr node = this->_root();

	while (node != nullptr)
	{
		if (this->_comp(node->_data, val))
			node = node->_right;
		else if (this->_comp(node->_data, val))
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
	node_ptr node = this->_root();

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
	node_ptr node = this->_root();
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
	node_ptr node = this->_root();
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
				node->_right == nullptr ? pos : tree_min(node->_right)));
	}
	return ft::make_pair(iterator(pos), iterator(pos));
}

template<typename T, typename Compare, typename Alloc>
ft::pair<typename RBtree<T,Compare,Alloc>::const_iterator,
		typename RBtree<T,Compare,Alloc>::const_iterator>
RBtree<T,Compare,Alloc>::equal_range(const value_type& val) const
{
	node_ptr node = this->_root();
	const_node_ptr pos = this->_end_node();

	while (node != nullptr)
	{
		if (this->_comp(val, node->_data))
		{
			pos = node;
			node = node->_left;
		}
		else if (this->_comp(node->data, val))
			node = node->_right;
		else
			return ft::make_pair(const_iterator(node), const_iterator(
				node->_right == nullptr ? pos : tree_min(node->_right)));
	}
	return ft::make_pair(const_iterator(pos), const_iterator(pos));
}

template<typename T, typename Compare, typename Alloc>
typename RBtree<T,Compare,Alloc>::allocator_type
RBtree<T,Compare,Alloc>::get_allocator() const
{
	return this->_allocator;
}



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
	node_ptr parent = node->_parent;
	if (node != this->_root() && parent->_color == red)
	{
		node_ptr grandparent = parent->_parent;
		node_ptr uncle = grandparent->_right;
		if (uncle != nullptr && uncle->_color == red) // only recoloring needed
		{
			parent->flip_color();
			uncle->flip_color();
			grandparent->flip_color();
			this->_rebalance_after_insertion(grandparent);
		}
		else if (tree_is_left_child<value_type>(parent)) // left-heavy situation
		{
			if (!tree_is_left_child<value_type>(node)) // left-right-heavy situation
				this->_rotate_left(parent);
			parent->flip_color();
			grandparent->flip_color();
			this->_rotate_right(grandparent);
			this->_rebalance_after_insertion(
				tree_is_left_child<value_type>(node) ? parent : grandparent);
		}
		else // right-heavy situation
		{
			if (tree_is_left_child<value_type>(node)) // right-left-heavy situation
				this->_rotate_right(parent);
			parent->flip_color();
			grandparent->flip_color();
			this->_rotate_left(grandparent);
			this->_rebalance_after_insertion(
				!tree_is_left_child<value_type>(node) ? parent : grandparent);
		}
	}
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

template<typename T, typename Compare, typename Alloc>
typename RBtree<T,Compare,Alloc>::node_ptr
RBtree<T,Compare,Alloc>::_erase(node_ptr node, const value_type& val, bool& deleted)
{
	if (node == nullptr)
	{
		return nullptr;
	}
	if (this->_comp(node->_data, val))
		node->_right = _erase(node->_right, val, deleted);
	else if (this->_comp(val, node->_data))
		node->_left = _erase(node->_left, val, deleted);
	else
	{
		node_ptr ret_node;
		if (node->_left == nullptr)
			ret_node = node->_right;
		else if (node->_right == nullptr)
			ret_node = node->_left;
		else
		{
			ret_node = node;
			node = ft::tree_max<value_type>(node->_left);
			// ret_node->_data = node->_data; // doesn't work because the first object is marked as const
			// rebalance here
			ret_node->_left = _erase(ret_node->_left, node->_data, deleted);
		}
		if (!deleted)
			this->_destroy_node(node);
		deleted = true;
		return ret_node;
	}
	return node;
}

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
void
RBtree<T,Compare,Alloc>::_destroy_node(node_ptr node)
{
	if (node == this->_begin_node)
	{
		iterator pos(node);
		++pos;
		this->_begin_node = pos.base();
	}
	this->_allocator.destroy(&node->_data);
	this->_node_allocator.deallocate(node, 1);
	--this->_size;
}

template<typename T, typename Compare, typename Alloc>
typename RBtree<T,Compare,Alloc>::node_ptr
RBtree<T,Compare,Alloc>::_copy(const node_ptr node)
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
void
RBtree<T,Compare,Alloc>::_destroy(node_ptr node)
{
	if (node == nullptr)
		return;
	_destroy(node->_left);
	_destroy(node->_right);
	this->_destroy_node(node);
}

template<typename T, typename Compare, typename Alloc>
bool
RBtree<T,Compare,Alloc>::_equals(const value_type& first, const value_type& second) const
{
	return !this->_comp(first, second) && !this->_comp(second, first);
}

template<typename T, typename Compare, typename Alloc>
void
swap(RBtree<T,Compare,Alloc>& first, RBtree<T,Compare,Alloc>& second)
{
	first.swap(second);
}

} // namespace ft