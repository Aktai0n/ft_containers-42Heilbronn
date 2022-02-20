/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functional.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 17:45:42 by skienzle          #+#    #+#             */
/*   Updated: 2022/02/20 15:59:33 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once


namespace ft
{


template<typename Arg1, typename Arg2, typename Result>
struct binary_function
{
	typedef Arg1	frist_argument_type;
	typedef Arg2	second_argument_type;
	typedef Result	result_type;
};

template<typename T>
struct less: binary_function<T,T,bool>
{
	bool operator()(const T& x, const T& y) const
	{
		return x < y;
	}
};


} // namespace ft