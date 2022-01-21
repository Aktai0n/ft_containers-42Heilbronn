/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 20:29:10 by skienzle          #+#    #+#             */
/*   Updated: 2022/01/20 20:55:57 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <utility>


namespace ft
{



template<typename T1, typename T2>
struct pair
{
public: // types
	typedef T1	first_type;
	typedef T2	second_type;

public: // methods
	pair();
	template<typename U, typename V>
		pair(const pair<U,V> &pr);
	pair(const first_type &a, const second_type &b);

	pair &operator=(const pair &pr);

public: // attributes
	T1 first;
	T2 second;
};

template<typename T1, typename T2>
pair<T1,T2>::pair(): first(), second() {}

template<typename T1, typename T2>
template<typename U, typename V>
pair<T1,T2>::pair(const pair<U,V> &pr): first(pr.first), second(pr.second) {}

template<typename T1, typename T2>
pair<T1,T2>::pair(const first_type &a, const second_type &b): first(a), second(b) {}

template<typename T1, typename T2>
pair<T1,T2> &pair<T1,T2>::operator=(const pair<T1,T2> &pr)
{
	this->first = pr.first;
	this->second = pr.second;
	return *this;
}



template<typename T1, typename T2>
inline bool operator==(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs)
{
	return lhs.first == rhs.first && lhs.second == rhs.second;
}

template<typename T1, typename T2>
inline bool operator!=(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs)
{
	return !(lhs == rhs);
}

template<typename T1, typename T2>
inline bool operator<(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs)
{
	return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
}

template<typename T1, typename T2>
inline bool operator>(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs)
{
	return rhs < lhs;
}

template<typename T1, typename T2>
inline bool operator<=(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs)
{
	return !(rhs < lhs);
}

template<typename T1, typename T2>
inline bool operator>=(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs)
{
	return !(lhs < rhs);
}



template<typename T1,typename T2>
inline pair<T1,T2> make_pair(T1 first, T2 second)
{
	return pair<T1,T2>(first, second);
}




} // namespace ft