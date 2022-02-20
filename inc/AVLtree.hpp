/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVLtree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 14:42:25 by skienzle          #+#    #+#             */
/*   Updated: 2022/02/19 15:59:06 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Itree.hpp"
#include "functional.hpp"


#ifndef nullptr
#define nullptr NULL
#endif

namespace ft
{

template<typename T, typename Compare = ft::less<T>, typename Alloc = std::allocator<T> >
class AVLtree: public ft::Itree<T,Compare,Alloc>
{
private: // types
	typedef ft::Itree<T,Compare,Alloc>				interface_type;
public: // types
	typedef typename interface_type::value_type		value_type;
	typedef typename interface_type::key_compare	key_compare;
	typedef typename interface_type::allocator_type	allocator_type;
	typedef typename allocator_type::size_type		size_type;
	



public: // subclass
	class node
	{
	public:
		node(const value_type& data): _depth(1), _data(data),
			_parent(), _left(), _right() {}
		node(const node& other): _depth(other._depth), _data(other.data),
			_parent(other.parent), _left(other._left), _right(other._right) {}
		~node() {}
	private:
		node(): _depth(), _data(), _parent(), _left(), _right() {}
	public:
		size_type _depth;
		value_type _data;
		node *_parent;
		node *_left;
		node *_right;
	};
public: // methods
	AVLtree();
	AVLtree(const AVLtree& other);
	AVLtree(const value_type& data);
	
	~AVLtree();

	AVLtree& operator=(const AVLtree& other);

	void traverse();
	bool is_empty();
	void insert(const value_type& data);
	void erase(const value_type& data);
	void clear();
	node* copy(const AVLtree& other);
private:
	node* create_node(const value_type& data);
	node* _rec_insert(node* node);
	void _rec_delete(node *node);
	void _rec_clear(node *node);
protected: // attributes
	node* _root;

};

template<typename T, typename Compare, typename Alloc>
AVLtree<T,Compare,Alloc>::AVLtree(): _root(nullptr) {}

template<typename T, typename Compare, typename Alloc>
AVLtree<T,Compare,Alloc>::AVLtree(const AVLtree& other): _root(copy(other)) {}

template<typename T, typename Compare, typename Alloc>
AVLtree<T,Compare,Alloc>::AVLtree(const value_type& data): _root(create_node(data)) {}

template<typename T, typename Compare, typename Alloc>
AVLtree<T,Compare,Alloc>::~AVLtree()
{
	if (_root != nullptr)
		this->clear();
}

template<typename T, typename Compare, typename Alloc>
AVLtree<T,Compare,Alloc>&
AVLtree<T,Compare,Alloc>::operator=(const AVLtree& other)
{
	if (this != &other)
	{
		this->clear();
		this->_root = this->copy(other);
	}
	return *this;
}








} // namespace ft