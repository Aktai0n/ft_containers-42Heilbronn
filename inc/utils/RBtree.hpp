/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:06:31 by skienzle          #+#    #+#             */
/*   Updated: 2022/03/05 20:17:44 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include <iostream> // has to be erased

#include "iterator.hpp"

#ifndef nullptr
#define nullptr NULL
#endif


/*
						Introduction to red black trees:

*	A red black tree is a self balancing binary search tree
*	In order to balance the tree, every node has an additional attribute representing
	the color red or black (usually a boolean. Or an enum if you want to be more verbose)
*	Depending on the alignment of the red and black nodes, rotations and recoloring
	is performed to an existing tree when inserting or deleting elements in order
	to keep the balance of the tree
*	It's not as strictly balanced as the AVL tree (where the depth of the branches can't
	differ by more than one)
	-> However, compared to the AVL tree, there are less rotations necessary when
		inserting / deleting elements
*	The red black tree is considered a comprimise between fast insertion / deletion (O log(n))
	and fast lookup times (O log(n)), making it the "allround work horse" in the world
	of data structures
*	Rules of the red black tree:
	-> The root is always black
	-> Every newly inserted node is colored red at first
	-> Leaf (null) nodes are considered black
	-> Both children of a red node have to be black
	-> The numer of black nodes from the root to any leaf node has to be the same
		(this is considered the black depth of the tree)
*/


/*
				Red black tree rebalcancing after insertion:

-> see RBtree::_rebalance_after_insertion in RBtree.tpp

*	Case 1: the node is the root
		-> nothing to be done
*	Case 2: the parent of node is black
		-> nothing to be done (no change in the black height)
*	Case 3: the node has a red uncle
		-> node's uncle becomes black
		-> node's parent becomes black
		-> node's grandparent becomes red
		-> proceed to the appropriate case with the grandparent
*	Case 4: the uncle is black
		-> perform the appropriate rotation of the tree:
		Case 4.1: parent is a left child and node is a right child
				(left-right-heavy situation)
				-> rotate the parent to the left
				-> proceed to case 4.2 (with the parent as node)
		Case 4.2: parent and node are left children
				(left-heavy situation)
				-> the parent becomes black
				-> the grandparent becomes red
				-> rotate the grandparent to the right
				-> we're done
		Case 4.3: parent is a right child and node is a left child
				(right-left-heavy situation)
				-> rotate the parent to the right
				-> procees to case 4.4 (with the parent as node)
		Case 4.4: parent and node are right cildren
				(right-heavy situation)
				-> the parent becomes black
				-> the grandparent becomes red
				-> rotate the grandparent to the left
				-> we're done
*/


/*
				Red black tree rebalancing after deletion:

-> see RBtree::_erase and RBtree::_rebalance_before_erasion in RBtree.tpp

* note: parent is always the parent of the sibling and the db_node
*	Case 1: repl was red
		-> no rebalancing needed, as there is no change in the black depth
*	Case 2: repl_child was red or the root
		-> if repl_child is red, we can simply color it black to preserve
			the black depth
		-> the root can't be double black, so we just remove the db
*	Case 3: sibling is red
		-> sibling "takes over" one of the blacks, so db_node and sibling
			are now normal black
		-> the parent of them becomes red
		-> rotation of the parent in the appropriate direction
			(left if db_node is on the left and otherwise right)
		-> reset the sibling and continue to the appropriate case
*	Case 4: both of siblings children are black (and sibling is black)
		-> sibling becomes red
		-> the parent node "takes over" one of the blacks, so
			if it was red, it will become black and if it was black
			it will become double black
		-> if the parent is the root or normal black, we are done.
			Otherwise we reset the sibling and continue
*	Case 5: sibling's child that's facing towards db_node is red
			(and sibling is black)
		-> since one of the children is red it can't be null
		-> sibling and his red child swap colors
		-> rotate sibling away from the db_node
			(right if db_node is on the left and left otherwise)
		-> reset the sibling and move on to case 6
*	Case 6: sibling's child that's facing away from db_node is red
			(and sibling is black)
		-> sibling and his parent swap colors
		-> rotate the parent towards the db_node
			(left if db_node is on the left and right otherwise)
		-> the sibling's child "has taken over" one of the blacks from db_node
		-> we are done
*/

namespace ft
{

//		RBtree_node

enum node_color { black = true, red = false };

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
			<< "\nright: " << _right << "\nnode addr: " << this << '\n' << std::endl;
	}

	node_color	_color;
	value_type	_data;
	node_ptr	_parent;
	node_ptr	_left;
	node_ptr	_right;
};


//		tree_iterator

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


// external operator overloads for tree_iterator

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
	typedef tree_iterator<typename RBtree_node<Value>::node_ptr,Value>	normal_tree_iterator;
public: // methods
	// constructors
	const_tree_iterator();
	const_tree_iterator(const const_tree_iterator& other);
	const_tree_iterator(const normal_tree_iterator& other);
	const_tree_iterator(const Const_node_ptr& val);
	// operator overloads
	const_tree_iterator&	operator=(const const_tree_iterator& other);
	// const_tree_iterator&	operator=(const normal_tree_iterator& other);
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


// external operator overloads for const_tree_iterator

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

// needs testing!

template<typename Const_node_ptr, typename Node_ptr, typename Value>
inline bool
operator==(const const_tree_iterator<Const_node_ptr,Value>& rhs,
			const tree_iterator<Node_ptr,Value>& lhs)
{
	return rhs.base() == lhs.base();
}

template<typename Const_node_ptr, typename Node_ptr, typename Value>
inline bool
operator!=(const const_tree_iterator<Const_node_ptr,Value>& rhs,
			const tree_iterator<Node_ptr,Value>& lhs)
{
	return rhs.base() != lhs.base();
}


//		RBtree

template<typename T, typename Compare, typename Alloc>
class RBtree
{
private: // types
	typedef ft::RBtree_node<T>											node_type;

public: // types
	typedef T															value_type;
	typedef Compare														value_compare;
	typedef Alloc														allocator_type;
	typedef typename allocator_type::template rebind<node_type>::other	node_allocator_type;
	typedef typename allocator_type::pointer							pointer;
	typedef typename allocator_type::const_pointer						const_pointer;
	typedef typename allocator_type::reference							reference;
	typedef typename allocator_type::const_reference					const_reference;
	typedef typename allocator_type::size_type							size_type;
	typedef typename allocator_type::difference_type					difference_type;
	typedef typename node_type::node_ptr								node_ptr;
	typedef typename node_type::const_node_ptr							const_node_ptr;

	typedef ft::tree_iterator<node_ptr,value_type>						iterator;
	typedef ft::const_tree_iterator<const_node_ptr,value_type>			const_iterator;
	typedef ft::reverse_iterator<iterator>								reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;


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

	ft::pair<iterator,bool>		insert(const value_type& val);
	iterator					insert(iterator position, const value_type& val);
	template<typename InputIterator>
		void					insert(InputIterator first, InputIterator last);
	void						erase(iterator position);
	size_type					erase(const value_type& val);
	void						erase(iterator first, iterator last);
	void						swap(RBtree& other);
	void						clear();


	// observer

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
	// utitlity

	node_ptr&		_root();
	const_node_ptr&	_root() const;
	node_ptr		_end_node();
	const_node_ptr	_end_node() const;
	node_ptr		_get_sibling(node_ptr node) const;
	node_color		_get_node_color(node_ptr node) const;
	void			_rotate_right(node_ptr node);
	void			_rotate_left(node_ptr node);

	// insertion

	node_ptr		_construct_node(const value_type& data);
	node_ptr		_insert(node_ptr node, node_ptr new_node, bool& inserted, iterator& pos);
	void			_rebalance_after_insertion(node_ptr node);
	node_ptr		_copy(const_node_ptr node);

	// deletion

	void			_destroy_node(node_ptr node);
	void			_erase(node_ptr root, node_ptr node);
	void			_rebalance_before_erasion(node_ptr root, node_ptr node, node_ptr sibling);
	node_ptr		_replacement_node(node_ptr node) const;
	void			_destroy(node_ptr node);

	void print_tree(const node_ptr node) const
	{
		if (node == nullptr)
			return;
		node->print_node();
		std::cout << "going left" << std::endl;
		print_tree(node->_left);
		std::cout << "going right" << std::endl;
		print_tree(node->_right);
	}
private: // attributes
	size_type			_size;
	node_type			_parent; // note: _parent->_left is the root
	node_ptr			_begin_node;
	value_compare		_comp;
	allocator_type		_allocator;
	node_allocator_type	_node_allocator;
};



template<typename T, typename Compare, typename Alloc>
void
swap(RBtree<T,Compare,Alloc>& first, RBtree<T,Compare,Alloc>& second)
{
	first.swap(second);
}

} // namespace ft

#include "RBtree.tpp"