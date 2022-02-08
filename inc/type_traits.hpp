/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 19:21:18 by skienzle          #+#    #+#             */
/*   Updated: 2022/02/08 23:14:09 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <type_traits>

namespace ft
{


// enable_if

template<bool, typename T = void>
struct enable_if {};

template<typename T>
struct enable_if<true, T>
{
	typedef T	type;
};


// is_integral

template<typename T, T v>
struct integral_constant
{
	typedef T					value_type;
	typedef integral_constant	type;

	static const value_type value = v;

	const value_type operator()() const
	{
		return value;
	}
};


typedef integral_constant<bool,true> true_type;
typedef integral_constant<bool,false> false_type;

template<typename T>
struct is_integral: public false_type {};

template<>
struct is_integral<bool>: public true_type {};

template<>
struct is_integral<char>: public true_type {};

template<>
struct is_integral<signed char>: public true_type {};

template<>
struct is_integral<unsigned char>: public true_type {};

template<>
struct is_integral<wchar_t>: public true_type {};

template<>
struct is_integral<char16_t>: public true_type {};

template<>
struct is_integral<char32_t>: public true_type {};

template<>
struct is_integral<short>: public true_type {};

template<>
struct is_integral<unsigned short>: public true_type {};

template<>
struct is_integral<int>: public true_type {};

template<>
struct is_integral<unsigned int>: public true_type {};

template<>
struct is_integral<long>: public true_type {};

template<>
struct is_integral<unsigned long>: public true_type {};

template<>
struct is_integral<long long>: public true_type {};

template<>
struct is_integral<unsigned long long>: public true_type {};


} // namespace ft