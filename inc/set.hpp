/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:23:50 by skienzle          #+#    #+#             */
/*   Updated: 2022/02/15 16:49:42 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <set>

#include <memory>

#include "type_traits.hpp"
#include "RBtree.hpp"
#include "functional.hpp"
#include "algorithm.hpp"
#include "iterator.hpp"
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

	typedef ft::tree_iterator<value_type>					iterator;
	typedef ft::const_tree_iterator<value_type>				const_iterator;
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

	iterator	find(const value_type& val) const;
	size_type	count(const value_type& val) const;
	iterator	lower_bound(const value_type& val) const;
	iterator	upper_bound(const value_type& val) const;
	ft::pair<iterator,iterator>	equal_range(const value_type& val) const;


	// allocator

	allocator_type get_allocator() const;

private: // types
	typedef ft::RBtree<value_type,value_compare,allocator_type>	tree_type;
private: // attributes
	tree_type _tree;
};






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