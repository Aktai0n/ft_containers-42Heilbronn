/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.tpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 16:54:24 by skienzle          #+#    #+#             */
/*   Updated: 2022/05/21 20:34:40 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{

// public methods

// constructors / destructor

template<typename T, typename Compare, typename Alloc>
set<T,Compare,Alloc>::set(const key_compare& comp, const allocator_type& alloc):
	_tree(comp, alloc) {}

template<typename T, typename Compare, typename Alloc>
template<typename InputIterator>
set<T,Compare,Alloc>::set(InputIterator first, InputIterator last,
								const key_compare& comp, const allocator_type& alloc):
	_tree(comp, alloc)
{
	this->insert(first, last);
}

template<typename T, typename Compare, typename Alloc>
set<T,Compare,Alloc>::set(const set& other): _tree(other._tree) {}



template<typename T, typename Compare, typename Alloc>
set<T,Compare,Alloc>::~set() {}


// operator overload

template<typename T, typename Compare, typename Alloc>
set<T,Compare,Alloc>&
set<T,Compare,Alloc>::operator=(const set& other)
{
	if (this != &other)
		this->_tree = other._tree;
	return *this;
}


// iterators

template<typename T, typename Compare, typename Alloc>
typename set<T,Compare,Alloc>::iterator
set<T,Compare,Alloc>::begin()
{
	return this->_tree.begin();
}

template<typename T, typename Compare, typename Alloc>
typename set<T,Compare,Alloc>::const_iterator
set<T,Compare,Alloc>::begin() const
{
	return this->_tree.begin();
}

template<typename T, typename Compare, typename Alloc>
typename set<T,Compare,Alloc>::iterator
set<T,Compare,Alloc>::end()
{
	return this->_tree.end();
}

template<typename T, typename Compare, typename Alloc>
typename set<T,Compare,Alloc>::const_iterator
set<T,Compare,Alloc>::end() const
{
	return this->_tree.end();
}

template<typename T, typename Compare, typename Alloc>
typename set<T,Compare,Alloc>::reverse_iterator
set<T,Compare,Alloc>::rbegin()
{
	return this->_tree.rbegin();
}

template<typename T, typename Compare, typename Alloc>
typename set<T,Compare,Alloc>::const_reverse_iterator
set<T,Compare,Alloc>::rbegin() const
{
	return this->_tree.rbegin();
}

template<typename T, typename Compare, typename Alloc>
typename set<T,Compare,Alloc>::reverse_iterator
set<T,Compare,Alloc>::rend()
{
	return this->_tree.rend();
}

template<typename T, typename Compare, typename Alloc>
typename set<T,Compare,Alloc>::const_reverse_iterator
set<T,Compare,Alloc>::rend() const
{
	return this->_tree.rend();
}


// capacity

template<typename T, typename Compare, typename Alloc>
bool
set<T,Compare,Alloc>::empty() const
{
	return this->_tree.empty();
}

template<typename T, typename Compare, typename Alloc>
typename set<T,Compare,Alloc>::size_type
set<T,Compare,Alloc>::size() const
{
	return this->_tree.size();
}


template<typename T, typename Compare, typename Alloc>
typename set<T,Compare,Alloc>::size_type
set<T,Compare,Alloc>::max_size() const
{
	return this->_tree.max_size();
}


// modifiers

template<typename T, typename Compare, typename Alloc>
ft::pair<typename set<T,Compare,Alloc>::iterator,bool>
set<T,Compare,Alloc>::insert(const value_type& val)
{
	return this->_tree.insert(val);
}

template<typename T, typename Compare, typename Alloc>
typename set<T,Compare,Alloc>::iterator
set<T,Compare,Alloc>::insert(__attribute__((unused)) iterator position, const value_type& val)
{
	return this->_tree.insert(val).first;
}

template<typename T, typename Compare, typename Alloc>
template<typename InputIterator>
void
set<T,Compare,Alloc>::insert(InputIterator first, InputIterator last)
{
	this->_tree.insert(first, last);
}

template<typename T, typename Compare, typename Alloc>
void
set<T,Compare,Alloc>::erase(iterator position)
{
	this->_tree.erase(*position);
}

template<typename T, typename Compare, typename Alloc>
typename set<T,Compare,Alloc>::size_type
set<T,Compare,Alloc>::erase(const value_type& val)
{
	return this->_tree.erase(val);
}

template<typename T, typename Compare, typename Alloc>
void
set<T,Compare,Alloc>::erase(iterator first, iterator last)
{
	while (first != last)
		this->_tree.erase(*(first++));
}

template<typename T, typename Compare, typename Alloc>
void
set<T,Compare,Alloc>::swap(set& other)
{
	this->_tree.swap(other._tree);
}

template<typename T, typename Compare, typename Alloc>
void
set<T,Compare,Alloc>::clear()
{
	this->_tree.clear();
}


// observers

template<typename T, typename Compare, typename Alloc>
typename set<T,Compare,Alloc>::key_compare
set<T,Compare,Alloc>::key_comp() const
{
	return key_compare();
}

template<typename T, typename Compare, typename Alloc>
typename set<T,Compare,Alloc>::value_compare
set<T,Compare,Alloc>::value_comp() const
{
	return this->_tree.value_comp();
}


// operations

template<typename T, typename Compare, typename Alloc>
typename set<T,Compare,Alloc>::iterator
set<T,Compare,Alloc>::find(const value_type& val) const
{
	return this->_tree.find(val);
}

template<typename T, typename Compare, typename Alloc>
typename set<T,Compare,Alloc>::size_type
set<T,Compare,Alloc>::count(const value_type& val) const
{
	return this->_tree.count(val);
}

template<typename T, typename Compare, typename Alloc>
typename set<T,Compare,Alloc>::iterator
set<T,Compare,Alloc>::lower_bound(const value_type& val) const
{
	return this->_tree.lower_bound(val);
}

template<typename T, typename Compare, typename Alloc>
typename set<T,Compare,Alloc>::iterator
set<T,Compare,Alloc>::upper_bound(const value_type& val) const
{
	return this->_tree.upper_bound(val);
}

template<typename T, typename Compare, typename Alloc>
ft::pair<typename set<T,Compare,Alloc>::iterator,
		typename set<T,Compare,Alloc>::iterator>
set<T,Compare,Alloc>::equal_range(const value_type& val) const
{
	return this->_tree.equal_range(val);
}


// allocator

template<typename T, typename Compare, typename Alloc>
typename set<T,Compare,Alloc>::allocator_type
set<T,Compare,Alloc>::get_allocator() const
{
	return this->_tree.get_allocator();
}


} // namespace ft