/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:40:35 by skienzle          #+#    #+#             */
/*   Updated: 2022/03/05 21:45:02 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>

#include <memory>

#include "./utils/type_traits.hpp"
#include "./utils/iterator.hpp"
#include "./utils/algorithm.hpp"

#ifndef nullptr
#define nullptr NULL
#endif

namespace ft
{


template<typename T, typename Alloc = std::allocator<T> >
class vector
{
private: // types
	typedef vector<T,Alloc>								self;
public: // types
	typedef Alloc										allocator_type;
	typedef typename allocator_type::value_type			value_type; // typedef T for std::allocator
	typedef typename allocator_type::size_type			size_type; //  typedef size_t for std::allocator
	typedef typename allocator_type::pointer			pointer; // typedef T* for std::allocator
	typedef typename allocator_type::difference_type	difference_type; // typedef ptrdiff_t for std::allocator
	typedef typename allocator_type::const_pointer		const_pointer; // typedef const T* for std::allocator
	typedef typename allocator_type::reference			reference; // typedef T& for std::allocator
	typedef typename allocator_type::const_reference	const_reference; // typedef const T& for std::allocator
	typedef ft::linear_iterator<pointer,self>			iterator;
	typedef ft::linear_iterator<const_pointer,self>		const_iterator;
	typedef ft::reverse_iterator<iterator>				reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;


public: // methods
	// constructors / destructor

	explicit vector(const allocator_type& alloc = allocator_type());
	explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
	template<typename InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = nullptr);
	vector(const vector& other);
	~vector();


	// operator overloads

	vector<T,Alloc>&	operator=(const vector<T,Alloc>& other);
	reference			operator[](size_type n);
	const_reference		operator[](size_type n) const;


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

	size_type	size() const;
	size_type	max_size() const;
	void		resize(size_type n, value_type val = value_type());
	size_type	capacity() const;
	bool		empty() const;
	void		reserve(size_type n);


	// element access

	reference			at(size_type n);
	const_reference		at(size_type n) const;
	reference			front();
	const_reference		front() const;
	reference			back();
	const_reference		back() const;


	// modifiers

	template<typename InputIterator>
		void	assign(InputIterator first, InputIterator last,
						typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = nullptr);
	void		assign(size_type n, const value_type& val);
	void		push_back(const value_type& val);
	void		pop_back();
	iterator	insert(iterator position, const value_type& val);
	void		insert(iterator position, size_type n, const value_type& val);
	template<typename InputIterator>
		void	insert(iterator position, InputIterator first, InputIterator last,
						typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = nullptr);
	iterator	erase(iterator position);
	iterator	erase(iterator first, iterator last);
	void		swap(vector& other);
	void		clear();


	// allocator

	allocator_type get_allocator() const;


private: // methods
	size_type	_vsizecheck(size_type new_size) const;
	pointer		_vallocate(size_type n);
	void		_vdeallocate();
	void		_vreallocate(size_type n);
	void		_construct_at_front(const size_type& n, const value_type& val);
	void		_construct_at_front(const vector& other);
	void		_destroy_at_end(pointer new_end);
	pointer		_iterator_to_pointer(const iterator& it) const;


private: // attributes
	size_type		_capacity;
	pointer			_begin;
	pointer			_end;
	allocator_type	_allocator;
};


// external operator overloads

template<typename T, typename Alloc>
inline bool
operator==(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
{
	return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template<typename T, typename Alloc>
inline bool
operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return !(lhs == rhs);
}

template<typename T, typename Alloc>
inline bool
operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<typename T, typename Alloc>
inline bool
operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return rhs < lhs;
}

template<typename T, typename Alloc>
inline bool
operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return !(rhs < lhs);
}

template<typename T, typename Alloc>
inline bool
operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return !(lhs < rhs);
}

template<typename T, typename Alloc>
void
swap(vector<T,Alloc>& x, vector<T,Alloc>& y)
{
	x.swap(y);
}


} // namespace ft

#include "vector.tpp"