/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.tpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 16:54:35 by skienzle          #+#    #+#             */
/*   Updated: 2022/02/27 11:43:36 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once


namespace ft
{

// constructors / destructor

template<typename Key, typename T, typename Compare, typename Alloc>
map<Key,T,Compare,Alloc>::map(const key_compare& comp, const allocator_type& alloc):
	_tree(value_compare(comp), alloc) {}

template<typename Key, typename T, typename Compare, typename Alloc>
template<typename InputIterator>
map<Key,T,Compare,Alloc>::map(InputIterator first, InputIterator last,
								const key_compare& comp, const allocator_type& alloc):
	_tree(value_compare(comp), alloc)
{
	this->insert(first, last);
}

template<typename Key, typename T, typename Compare, typename Alloc>
map<Key,T,Compare,Alloc>::map(const map& other): _tree(other._tree) {}



template<typename Key, typename T, typename Compare, typename Alloc>
map<Key,T,Compare,Alloc>::~map() {}


// operator overloads

template<typename Key, typename T, typename Compare, typename Alloc>
map<Key,T,Compare,Alloc>&
map<Key,T,Compare,Alloc>::operator=(const map& other)
{
	if (this != &other)
		this->_tree = other._tree;
	return *this;
}

template<typename Key, typename T, typename Compare, typename Alloc>
typename map<Key,T,Compare,Alloc>::mapped_type&
map<Key,T,Compare,Alloc>::operator[](const key_type& key)
{
	iterator pos(this->insert(ft::make_pair(key, mapped_type())).first);
	return (*pos).second;
}


// iterators

template<typename Key, typename T, typename Compare, typename Alloc>
typename map<Key,T,Compare,Alloc>::iterator
map<Key,T,Compare,Alloc>::begin()
{
	return this->_tree.begin();
}

template<typename Key, typename T, typename Compare, typename Alloc>
typename map<Key,T,Compare,Alloc>::const_iterator
map<Key,T,Compare,Alloc>::begin() const
{
	return this->_tree.begin();
}

template<typename Key, typename T, typename Compare, typename Alloc>
typename map<Key,T,Compare,Alloc>::iterator
map<Key,T,Compare,Alloc>::end()
{
	return this->_tree.end();
}

template<typename Key, typename T, typename Compare, typename Alloc>
typename map<Key,T,Compare,Alloc>::const_iterator
map<Key,T,Compare,Alloc>::end() const
{
	return this->_tree.end();
}

template<typename Key, typename T, typename Compare, typename Alloc>
typename map<Key,T,Compare,Alloc>::reverse_iterator
map<Key,T,Compare,Alloc>::rbegin()
{
	return this->_tree.rbegin();
}

template<typename Key, typename T, typename Compare, typename Alloc>
typename map<Key,T,Compare,Alloc>::const_reverse_iterator
map<Key,T,Compare,Alloc>::rbegin() const
{
	return this->_tree.rbegin();
}

template<typename Key, typename T, typename Compare, typename Alloc>
typename map<Key,T,Compare,Alloc>::reverse_iterator
map<Key,T,Compare,Alloc>::rend()
{
	return this->_tree.rend();
}

template<typename Key, typename T, typename Compare, typename Alloc>
typename map<Key,T,Compare,Alloc>::const_reverse_iterator
map<Key,T,Compare,Alloc>::rend() const
{
	return this->_tree.rend();
}


// capacity

template<typename Key, typename T, typename Compare, typename Alloc>
bool
map<Key,T,Compare,Alloc>::empty() const
{
	return this->_tree.empty();
}

template<typename Key, typename T, typename Compare, typename Alloc>
typename map<Key,T,Compare,Alloc>::size_type
map<Key,T,Compare,Alloc>::size() const
{
	return this->_tree.size();
}


template<typename Key, typename T, typename Compare, typename Alloc>
typename map<Key,T,Compare,Alloc>::size_type
map<Key,T,Compare,Alloc>::max_size() const
{
	return this->_tree.max_size();
}


// modifiers

template<typename Key, typename T, typename Compare, typename Alloc>
ft::pair<typename map<Key,T,Compare,Alloc>::iterator,bool>
map<Key,T,Compare,Alloc>::insert(const value_type& val)
{
	return this->_tree.insert(val);
}

template<typename Key, typename T, typename Compare, typename Alloc>
typename map<Key,T,Compare,Alloc>::iterator
map<Key,T,Compare,Alloc>::insert(iterator position, const value_type& val)
{
	return this->_tree.insert(position, val);
}

template<typename Key, typename T, typename Compare, typename Alloc>
template<typename InputIterator>
void
map<Key,T,Compare,Alloc>::insert(InputIterator first, InputIterator last)
{
	this->_tree.insert(first, last);
}

template<typename Key, typename T, typename Compare, typename Alloc>
void
map<Key,T,Compare,Alloc>::erase(iterator position)
{
	this->_tree.erase(position);
}

template<typename Key, typename T, typename Compare, typename Alloc>
typename map<Key,T,Compare,Alloc>::size_type
map<Key,T,Compare,Alloc>::erase(const key_type& key)
{
	return this->_tree.erase(ft::make_pair(key, mapped_type()));
}

template<typename Key, typename T, typename Compare, typename Alloc>
void
map<Key,T,Compare,Alloc>::erase(iterator first, iterator last)
{
	this->_tree.erase(first, last);
}

template<typename Key, typename T, typename Compare, typename Alloc>
void
map<Key,T,Compare,Alloc>::swap(map& other)
{
	this->_tree.swap(other._tree);
}

template<typename Key, typename T, typename Compare, typename Alloc>
void
map<Key,T,Compare,Alloc>::clear()
{
	this->_tree.clear();
}


// observers

template<typename Key, typename T, typename Compare, typename Alloc>
typename map<Key,T,Compare,Alloc>::key_compare
map<Key,T,Compare,Alloc>::key_comp() const
{
	return key_compare();
}

template<typename Key, typename T, typename Compare, typename Alloc>
typename map<Key,T,Compare,Alloc>::value_compare
map<Key,T,Compare,Alloc>::value_comp() const
{
	return this->_tree.value_comp();
}


// operations

template<typename Key, typename T, typename Compare, typename Alloc>
typename map<Key,T,Compare,Alloc>::iterator
map<Key,T,Compare,Alloc>::find(const key_type& key)
{
	return this->_tree.find(ft::make_pair(key, mapped_type()));
}

template<typename Key, typename T, typename Compare, typename Alloc>
typename map<Key,T,Compare,Alloc>::const_iterator
map<Key,T,Compare,Alloc>::find(const key_type& key) const
{
	return this->_tree.find(ft::make_pair(key, mapped_type()));
}

template<typename Key, typename T, typename Compare, typename Alloc>
typename map<Key,T,Compare,Alloc>::size_type
map<Key,T,Compare,Alloc>::count(const key_type& key) const
{
	return this->_tree.count(ft::make_pair(key, mapped_type()));
}


template<typename Key, typename T, typename Compare, typename Alloc>
typename map<Key,T,Compare,Alloc>::iterator
map<Key,T,Compare,Alloc>::lower_bound(const key_type& key)
{
	return this->_tree.lower_bound(ft::make_pair(key, mapped_type()));
}

template<typename Key, typename T, typename Compare, typename Alloc>
typename map<Key,T,Compare,Alloc>::const_iterator
map<Key,T,Compare,Alloc>::lower_bound(const key_type& key) const
{
	return this->_tree.lower_bound(ft::make_pair(key, mapped_type()));
}

template<typename Key, typename T, typename Compare, typename Alloc>
typename map<Key,T,Compare,Alloc>::iterator
map<Key,T,Compare,Alloc>::upper_bound(const key_type& key)
{
	return this->_tree.upper_bound(ft::make_pair(key, mapped_type()));
}

template<typename Key, typename T, typename Compare, typename Alloc>
typename map<Key,T,Compare,Alloc>::const_iterator
map<Key,T,Compare,Alloc>::upper_bound(const key_type& key) const
{
	return this->_tree.upper_bound(ft::make_pair(key, mapped_type()));
}

template<typename Key, typename T, typename Compare, typename Alloc>
ft::pair<typename map<Key,T,Compare,Alloc>::iterator,
		typename map<Key,T,Compare,Alloc>::iterator>
map<Key,T,Compare,Alloc>::equal_range(const key_type& key)
{
	return this->_tree.equal_range(ft::make_pair(key, mapped_type()));
}

template<typename Key, typename T, typename Compare, typename Alloc>
ft::pair<typename map<Key,T,Compare,Alloc>::const_iterator,
		typename map<Key,T,Compare,Alloc>::const_iterator>
map<Key,T,Compare,Alloc>::equal_range(const key_type& key) const
{
	return this->_tree.equal_range(ft::make_pair(key, mapped_type()));
}


// allocator

template<typename Key, typename T, typename Compare, typename Alloc>
typename map<Key,T,Compare,Alloc>::allocator_type
map<Key,T,Compare,Alloc>::get_allocator() const
{
	return this->_tree.get_allocator();
}


} // namespace ft