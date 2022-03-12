/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:40:18 by skienzle          #+#    #+#             */
/*   Updated: 2022/03/12 09:42:07 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>

#include <memory>

#include "./utils/functional.hpp"
#include "./utils/iterator.hpp"
#include "./utils/algorithm.hpp"
#include "./utils/utility.hpp"
#include "./utils/RBtree.hpp"

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
	typedef T											mapped_type;
	typedef Key											key_type;
	typedef Compare										key_compare;
	typedef Alloc										allocator_type;
	typedef ft::pair<const key_type,mapped_type>		value_type;
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
	typedef typename tree_type::reverse_iterator		reverse_iterator;
	typedef typename tree_type::const_reverse_iterator	const_reverse_iterator;


public: // methods
	// constructors / destructor

	explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
	template<typename InputIterator>
		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type());
	map(const map& other);
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


// external operator overloads

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

#include "map.tpp"