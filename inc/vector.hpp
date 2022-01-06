/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:40:35 by skienzle          #+#    #+#             */
/*   Updated: 2022/01/06 17:02:01 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{


template<typename T, typename Alloc = std::allocator<T> >
class vector
{
public: // types
	typedef Alloc allocator_type;
	typedef typename allocator_type::value_type value_type; // expands to typedef T value_type for std::allocator
	typedef typename allocator_type::size_type size_type; // expands to typedef size_t size_type for std::allocator
	
public: // methods
	explicit vector(const allocator_type &alloc = allocator_type());
	explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type());
	template<typename InputIterator>
	vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type());
	vector(const vector &other);
	
private:

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
vector<T, Alloc>::vector(const vector &other)
{
	(void)other;
}

} // namespace ft

// #include "vector.ipp"