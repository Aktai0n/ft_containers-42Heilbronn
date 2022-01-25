/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:40:35 by skienzle          #+#    #+#             */
/*   Updated: 2022/01/25 19:48:41 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>

#include <memory>

#include "iterator.hpp"
#include "algorithm.hpp"

namespace ft
{


template<typename T, typename Alloc = std::allocator<T> >
class vector
{
public: // types
	typedef Alloc										allocator_type;
	typedef typename allocator_type::value_type			value_type; // typedef T for std::allocator
	typedef typename allocator_type::size_type			size_type; //  typedef size_t for std::allocator
	typedef typename allocator_type::pointer			pointer; // typedef T* for std::allocator
	typedef typename allocator_type::const_pointer		const_pointer; // typedef const T* for std::allocator
	typedef typename allocator_type::reference			reference; // typedef T& for std::allocator
	typedef typename allocator_type::const_reference	const_reference; // typedef const T& for std::allocator
	typedef pointer										iterator;
	typedef const_pointer								const_iterator;
	typedef ft::reverse_iterator<iterator>				reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
	
public: // methods
	// constructors
	explicit vector(const allocator_type &alloc = allocator_type());
	explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type());
	template<typename InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type());
	vector(const vector &x);

	// destructor
	~vector();

	// operator overloads
	vector<T, Alloc>	&operator=(const vector<T, Alloc> &x);
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
		void	assign(InputIterator first, InputIterator last);
	void		assign(size_type n, const value_type &val);
	void		push_back(const value_type &val);
	void		pop_back();
	iterator	insert(iterator position, const value_type &val);
	void		insert(iterator position, size_type n, const value_type &val);
	template<typename InputIterator>
		void	insert(iterator position, InputIterator first, InputIterator last);
	iterator	erase(iterator position);
	iterator	erase(iterator first, iterator last);
	void		swap(vector &x);
	void		clear();
	
	// allocator
	allocator_type get_allocator() const;


private: // attributes
	size_type		_capacity;
	pointer			_begin;
	pointer			_end;
	allocator_type	_allocator;
};

template<typename T, typename Alloc>
vector<T, Alloc>::vector(const allocator_type &alloc):
	_begin(nullptr), _end(nullptr), _allocator(alloc) {}

template<typename T, typename Alloc>
vector<T, Alloc>::vector(size_type n, const value_type &val, const allocator_type &alloc)
{
	(void)n;
	(void)val;
	(void)alloc;
}

template<typename T, typename Alloc>
template<typename InputIterator>
vector<T, Alloc>::vector(InputIterator first, InputIterator last, const allocator_type &alloc)
{
	(void)first;
	(void)last;
	(void)alloc;
}

template<typename T, typename Alloc>
vector<T, Alloc>::vector(const vector &x)
{
	(void)x;
}

template<typename T, typename Alloc>
vector<T, Alloc>::~vector()
{
	// allocator_type::deallocate(ptr, size);
}



template<typename T, typename Alloc>
vector<T, Alloc> &vector<T, Alloc>::operator=(const vector<T, Alloc> &x)
{
	(void)x;
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::operator[](size_type n)
{
	return this->_begin[n];
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::operator[](size_type n) const
{
	return this->_begin[n];
}



template<typename T, typename Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::begin()
{
	
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::const_iterator vector<T, Alloc>::begin() const
{
	
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::end()
{
	
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::const_iterator vector<T, Alloc>::end() const
{
	
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rbegin()
{
	return reverse_iterator(this->end());
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::rbegin() const
{
	return const_reverse_iterator(this->end());
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rend()
{
	return reverse_iterator(this->begin());
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::rend() const
{
	return const_reverse_iterator(this->begin());
}



template<typename T, typename Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::size() const
{
	return static_cast<size_type>(this->_end - this->_begin);
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::max_size() const
{
	return this->_allocator.max_size();
}

template<typename T, typename Alloc>
void vector<T, Alloc>::resize(size_type n, value_type val)
{
	(void)n;
	(void)val;
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::capacity() const
{
	return this->_capacity;
}

template<typename T, typename Alloc>
bool vector<T, Alloc>::empty() const
{
	return this->_begin == this->_end;
}

template<typename T, typename Alloc>
void vector<T, Alloc>::reserve(size_type n)
{
	if (n <= this->_size)
		return;
	if (n > this->_max_size)
		throw std::length_error("vector->reserve exception: requested size exceeds maximum size"); // change that to the appropriate size
	
}



template<typename T, typename Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::at(size_type n)
{
	if (n >= this->_size)
		throw std::out_of_range("vector");
	return this->_begin[n];
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::at(size_type n) const
{
	if (n >= this->_size)
		throw std::out_of_range("vector");
	return this->_begin[n];
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::front()
{
	return *this->_begin;
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::front() const
{
	return *this->_begin;
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::back()
{
	return *(this->_end - 1);
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::back() const
{
	return *(this->_end - 1);
}

template<typename T, typename Alloc>
template<typename InputIterator>
void vector<T, Alloc>::assign(InputIterator first, InputIterator last)
{
	(void)first;
	(void)last;
}

template<typename T, typename Alloc>
void vector<T, Alloc>::assign(size_type n, const value_type &val)
{
	(void)n;
	(void)val;
}

template<typename T, typename Alloc>
void vector<T, Alloc>::push_back(const value_type &val)
{
	(void)val;
}

template<typename T, typename Alloc>
void vector<T, Alloc>::pop_back()
{

}

template<typename T, typename Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(iterator position,
														const value_type &val)
{
	(void)position;
	(void)val;
}

template<typename T, typename Alloc>
void vector<T, Alloc>::insert(iterator position, size_type n, const value_type &val)
{
	(void)position;
	(void)n;
	(void)val;
}

template<typename T, typename Alloc>
template<typename InputIterator>
void vector<T, Alloc>::insert(iterator position, InputIterator first, InputIterator last)
{
	(void)position;
	(void)first;
	(void)last;
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator position)
{
	(void)position;
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator first, iterator last)
{
	(void)first;
	(void)last;
}

template<typename T, typename Alloc>
void vector<T, Alloc>::swap(vector &x)
{
	(void)x;
}

template<typename T, typename Alloc>
void vector<T, Alloc>::clear()
{
	
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::allocator_type vector<T, Alloc>::get_allocator() const
{
	return this->_allocator;
}


// relational operator overloads

template<typename T, typename Alloc>
inline bool operator==(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
{
	return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template<typename T, typename Alloc>
inline bool operator!=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
{
	return !(lhs == rhs);
}

template<typename T, typename Alloc>
inline bool operator<(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<typename T, typename Alloc>
inline bool operator>(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
{
	return rhs < lhs;
}

template<typename T, typename Alloc>
inline bool operator<=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
{
	return !(rhs < lhs);
}

template<typename T, typename Alloc>
inline bool operator>=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
{
	return !(lhs < rhs);
}

template<typename T, typename Alloc>
void swap(vector<T,Alloc> &x, vector<T,Alloc> &y)
{
	x.swap(y);
}


} // namespace ft

// #include "vector.ipp"