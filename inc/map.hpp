/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:40:18 by skienzle          #+#    #+#             */
/*   Updated: 2022/02/19 16:02:07 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>

#include "functional.hpp"
#include "utility.hpp"
#include "iterator.hpp"
#include "RBtree.hpp"

#ifndef nullptr
#define nullptr NULL
#endif

namespace ft
{


template<typename Key, typename T, typename Compare = ft::less<Key>,
			typename Alloc = std::allocator<ft::pair<const Key, T> > >
class map
{
public: // types
	typedef Key											key_type;
	typedef T											mapped_type;
	typedef ft::pair<const key_type,mapped_type>		value_type;
	typedef Compare										key_compare;
	typedef Alloc										allocator_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
	typedef typename allocator_type::size_type			size_type;
	typedef typename allocator_type::difference_type	difference_type;

public: // subclass
	class value_compare: public ft::binary_function<value_type, value_type, bool>
	{
		friend class map;

	public:
		bool operator()(const value_type& x, const value_type& y) const
		{
			return comp(x.first, y.first);
		}

	protected:
		value_compare(key_compare c): comp(c) {}

		key_compare comp;
	};

private: // types
	typedef ft::RBtree<value_type,value_compare,allocator_type>	tree_type;

public: // iterator types
	typedef typename tree_type::iterator				iterator;
	typedef typename tree_type::const_iterator			const_iterator;
	typedef ft::reverse_iterator<iterator>				reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
	
	
public: // methods
	// constructors

	explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
	template<typename InputIterator>
		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type());
	map(const map& other);

	// destructor

	~map();

	// operator overloads
	
	map&			operator=(const map& other);
	mapped_type&	operator[](const key_type& key);


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

	ft::pair<iterator,bool>	insert(const value_type& val);
	iterator				insert(iterator position, const value_type& val);
	template<typename InputIterator>
		void				insert(InputIterator first, InputIterator last);
	void					erase(iterator position);
	size_type				erase(const key_type& key);
	void					erase(iterator first, iterator last);
	void					swap(map& other);
	void					clear();

	// observers

	key_compare		key_comp() const;
	value_compare	value_comp() const;

	// operations

	iterator								find(const key_type& key);
	const_iterator							find(const key_type& key) const;
	size_type								count(const key_type& key) const;
	iterator								lower_bound(const key_type& key);
	const_iterator							lower_bound(const key_type& key) const;
	iterator								upper_bound(const key_type& key);
	const_iterator							upper_bound(const key_type& key) const;
	ft::pair<iterator,iterator>				equal_range(const key_type& key);
	ft::pair<const_iterator,const_iterator>	equal_range(const key_type& key) const;

	// allocator

	allocator_type	get_allocator() const;

private: // attributes
	tree_type _tree;
};


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
	this->_tree.max_size();
}


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


template<typename Key, typename T, typename Compare, typename Alloc>
typename map<Key,T,Compare,Alloc>::allocator_type
map<Key,T,Compare,Alloc>::get_allocator() const
{
	return this->_tree.get_allocator();
}

// relational operator overloads

template<typename Key, typename T, typename Compare, typename Alloc>
inline bool
operator==(const map<Key,T,Compare,Alloc>& lhs,
			const map<Key,T,Compare,Alloc>& rhs)
{
	return lhs.size() == rhs.size() &&
			ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template<typename Key, typename T, typename Compare, typename Alloc>
inline bool
operator!=(const map<Key,T,Compare,Alloc>& lhs,
			const map<Key,T,Compare,Alloc>& rhs)
{
	return !(lhs == rhs);
}

template<typename Key, typename T, typename Compare, typename Alloc>
inline bool
operator<(const map<Key,T,Compare,Alloc>& lhs,
			const map<Key,T,Compare,Alloc>& rhs)
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<typename Key, typename T, typename Compare, typename Alloc>
inline bool
operator>(const map<Key,T,Compare,Alloc>& lhs,
			const map<Key,T,Compare,Alloc>& rhs)
{
	return rhs < lhs;
}

template<typename Key, typename T, typename Compare, typename Alloc>
inline bool
operator<=(const map<Key,T,Compare,Alloc>& lhs,
			const map<Key,T,Compare,Alloc>& rhs)
{
	return !(rhs < lhs);
}

template<typename Key, typename T, typename Compare, typename Alloc>
inline bool
operator>=(const map<Key,T,Compare,Alloc>& lhs,
			const map<Key,T,Compare,Alloc>& rhs)
{
	return !(lhs < rhs);
}

template<typename Key, typename T, typename Compare, typename Alloc>
void
swap(map<Key,T,Compare,Alloc>& lhs, map<Key,T,Compare,Alloc>& rhs)
{
	lhs.swap(rhs);
}

} // namespace ft