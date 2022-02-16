/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:23:50 by skienzle          #+#    #+#             */
/*   Updated: 2022/02/16 14:48:45 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <set>

#include <memory>

#include "type_traits.hpp"
#include "RBtree.hpp"
#include "functional.hpp"
#include "utility.hpp"

#ifndef nullptr
#define nullptr NULL
#endif

namespace ft
{

template<typename T, typename Compare = ft::less<T>, typename Alloc = std::allocator<T> >
class set
{
public: // types
	typedef T												key_type;
	typedef T												value_type;
	typedef Compare											key_compare;
	typedef Compare											value_compare;
	typedef Alloc											allocator_type;
	typedef typename allocator_type::reference				reference;
	typedef typename allocator_type::const_reference		const_reference;
	typedef typename allocator_type::pointer				pointer;
	typedef typename allocator_type::const_pointer			const_pointer;
	typedef typename allocator_type::size_type				size_type;

private: // types
	typedef ft::RBtree<value_type,value_compare,allocator_type>	tree_type;
public: // iterator types
	typedef typename tree_type::iterator					iterator;
	typedef typename tree_type::const_iterator				const_iterator;
	typedef ft::reverse_iterator<iterator>					reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

public: // methods
	// constructors

	explicit set(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
	template<typename InputIterator>
		set(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type());
	set(const set& other);


	// destructor

	~set();

	// operator overloads

	set& operator=(const set& other);


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

	ft::pair<iterator, bool>	insert(const value_type& val);
	iterator					insert(iterator position, const value_type& val);
	template<typename InputIterator>
		void					insert(InputIterator first, InputIterator last);
	void						erase(iterator position);
	size_type					erase(const value_type& val);
	void						erase(iterator first, iterator last);
	void						swap(set& other);
	void						clear();


	// observers

	key_compare		key_comp() const;
	value_compare	value_comp() const;


	// operations

	iterator					find(const value_type& val) const;
	size_type					count(const value_type& val) const;
	iterator					lower_bound(const value_type& val) const;
	iterator					upper_bound(const value_type& val) const;
	ft::pair<iterator,iterator>	equal_range(const value_type& val) const;


	// allocator

	allocator_type get_allocator() const;

private: // attributes
	tree_type _tree;
};

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


template<typename T, typename Compare, typename Alloc>
set<T,Compare,Alloc>&
set<T,Compare,Alloc>::operator=(const set& other)
{
	if (this != &other)
		this->_tree = other._tree;
	return *this;
}


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
	this->_tree.max_size();
}


template<typename T, typename Compare, typename Alloc>
ft::pair<typename set<T,Compare,Alloc>::iterator,bool>
set<T,Compare,Alloc>::insert(const value_type& val)
{
	this->_tree.insert(val);
	return ft::make_pair(iterator(), true);
}

template<typename T, typename Compare, typename Alloc>
typename set<T,Compare,Alloc>::iterator
set<T,Compare,Alloc>::insert(iterator position, const value_type& val)
{
	return this->_tree.insert(position, val);
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
	this->_tree.erase(position);
}

template<typename T, typename Compare, typename Alloc>
typename set<T,Compare,Alloc>::size_type
set<T,Compare,Alloc>::erase(const key_type& key)
{
	return this->_tree.erase(ft::make_pair(key, mapped_type()));
}

template<typename T, typename Compare, typename Alloc>
void
set<T,Compare,Alloc>::erase(iterator first, iterator last)
{
	this->_tree.erase(first, last);
}

template<typename T, typename Compare, typename Alloc>
void
set<T,Compare,Alloc>::swap(set& other)
{
	ft::swap(this->_tree, other._tree);
}

template<typename T, typename Compare, typename Alloc>
void
set<T,Compare,Alloc>::clear()
{
	this->_tree.clear();
}


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


template<typename T, typename Compare, typename Alloc>
typename set<T,Compare,Alloc>::iterator
set<T,Compare,Alloc>::find(const key_type& key)
{
	return this->_tree.find(ft::make_pair(key, mapped_type()));
}

template<typename T, typename Compare, typename Alloc>
typename set<T,Compare,Alloc>::const_iterator
set<T,Compare,Alloc>::find(const key_type& key) const
{
	return this->_tree.find(ft::make_pair(key, mapped_type()));
}

template<typename T, typename Compare, typename Alloc>
typename set<T,Compare,Alloc>::size_type
set<T,Compare,Alloc>::count(const key_type& key) const
{
	return this->_tree.count(ft::make_pair(key, mapped_type()));
}


template<typename T, typename Compare, typename Alloc>
typename set<T,Compare,Alloc>::iterator
set<T,Compare,Alloc>::lower_bound(const key_type& key)
{
	return this->_tree.lower_bound(ft::make_pair(key, mapped_type()));
}

template<typename T, typename Compare, typename Alloc>
typename set<T,Compare,Alloc>::const_iterator
set<T,Compare,Alloc>::lower_bound(const key_type& key) const
{
	return this->_tree.lower_bound(ft::make_pair(key, mapped_type()));
}

template<typename T, typename Compare, typename Alloc>
typename set<T,Compare,Alloc>::iterator
set<T,Compare,Alloc>::upper_bound(const key_type& key)
{
	return this->_tree.upper_bound(ft::make_pair(key, mapped_type()));
}

template<typename T, typename Compare, typename Alloc>
typename set<T,Compare,Alloc>::const_iterator
set<T,Compare,Alloc>::upper_bound(const key_type& key) const
{
	return this->_tree.upper_bound(ft::make_pair(key, mapped_type()));
}

template<typename T, typename Compare, typename Alloc>
ft::pair<typename set<T,Compare,Alloc>::iterator,
		typename set<T,Compare,Alloc>::iterator>
set<T,Compare,Alloc>::equal_range(const key_type& key)
{
	return this->_tree.equal_range(ft::make_pair(key, mapped_type()));
}

template<typename T, typename Compare, typename Alloc>
ft::pair<typename set<T,Compare,Alloc>::const_iterator,
		typename set<T,Compare,Alloc>::const_iterator>
set<T,Compare,Alloc>::equal_range(const key_type& key) const
{
	return this->_tree.equal_range(ft::make_pair(key, mapped_type()));
}




// relational operator overloads

template<typename T, typename Compare, typename Alloc>
inline bool
operator==(const set<T,Compare,Alloc>& lhs,
			const set<T,Compare,Alloc>& rhs)
{
	return lhs.size() == rhs.size() &&
			ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template<typename T, typename Compare, typename Alloc>
inline bool
operator!=(const set<T,Compare,Alloc>& lhs,
			const set<T,Compare,Alloc>& rhs)
{
	return !(lhs == rhs);
}

template<typename T, typename Compare, typename Alloc>
inline bool
operator<(const set<T,Compare,Alloc>& lhs,
			const set<T,Compare,Alloc>& rhs)
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin, rhs.end());
}

template<typename T, typename Compare, typename Alloc>
inline bool
operator>(const set<T,Compare,Alloc>& lhs,
			const set<T,Compare,Alloc>& rhs)
{
	return rhs < lhs;
}

template<typename T, typename Compare, typename Alloc>
inline bool
operator<=(const set<T,Compare,Alloc>& lhs,
			const set<T,Compare,Alloc>& rhs)
{
	return !(rhs < lhs);
}

template<typename T, typename Compare, typename Alloc>
inline bool
operator>=(const set<T,Compare,Alloc>& lhs,
			const set<T,Compare,Alloc>& rhs)
{
	return !(lhs < rhs);
}

template<typename T, typename Compare, typename Alloc>
void
swap(set<T,Compare,Alloc>& x, set<T,Compare,Alloc>& y)
{
	x.swap(y);
}


} // namespace ft