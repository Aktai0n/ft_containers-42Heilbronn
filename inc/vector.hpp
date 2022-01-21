/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:40:35 by skienzle          #+#    #+#             */
/*   Updated: 2022/01/21 21:55:18 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>

#include <memory>

#include "iterator.hpp"

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

	// capacity
	size_type			size() const;
	size_type			max_size() const;
	void				resize(size_type n, value_type val = value_type());
	size_type			capacity() const;
	bool				empty() const;
	void				reserve(size_type n);

	// element access
	reference			at(size_type n);
	const_reference		at(size_type n) const;
	reference			front();
	const_reference		front() const;
	reference			back();
	const_reference		back() const;

	// modifiers
	template<typename InputIterator>
		void			assign(InputIterator first, InputIterator last);
	void				assign(size_type n, const value_type &val);
	void				push_back(const value_type &val);
	void				pop_back(const value_type &val);
	
private: // attributes
	size_type _size;
	size_type _capacity;
	size_type _max_size;
	value_type _arr;
};

template<typename T, typename Alloc>
vector<T, Alloc>::vector(const allocator_type &alloc)
{(void)alloc;}

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
	return this->_arr[n];
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::operator[](size_type n) const
{
	return this->_arr[n];
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::size() const
{
	return this->_size;
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::max_size() const
{
	return this->_max_size;
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
	return this->_size == 0;
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
	return this->_arr[n];
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::at(size_type n) const
{
	if (n >= this->_size)
		throw std::out_of_range("vector");
	return this->_arr[n];
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::front()
{
	return this->_arr[0];
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::front() const
{
	return this->_arr[0];
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::back()
{
	return this->_arr[this->_size - 1];
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::back() const
{
	return this->_arr[this->_size - 1];
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
void vector<T, Alloc>::pop_back(const value_type &val)
{
	(void)val;
}



} // namespace ft

// #include "vector.ipp"