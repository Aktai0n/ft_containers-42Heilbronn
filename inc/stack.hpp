/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:40:38 by skienzle          #+#    #+#             */
/*   Updated: 2022/02/20 18:59:26 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stack>

#include "vector.hpp"

namespace ft
{

template<typename T, typename Container = ft::vector<T> >
class stack
{
public: // types
	typedef Container							container_type;
	typedef typename container_type::value_type	value_type;
	typedef typename container_type::size_type	size_type;

public: // methods
	explicit stack(const container_type &cntr = container_type());

	bool				empty() const;
	size_type			size() const;
	value_type			&top();
	const value_type	&top() const;
	void				push(const value_type &val);
	void				pop();

public: // friends
	friend bool operator==(const stack &lhs, const stack &rhs);
	friend bool operator<(const stack &lhs, const stack &rhs);

protected:
	container_type _c;
};


// external operator overloads

template<typename T, typename Container>
inline bool
operator==(const stack<T,Container> &lhs, const stack<T,Container> &rhs)
{
	return lhs._c == rhs._c;
}


template<typename T, typename Container>
inline bool
operator!=(const stack<T,Container> &lhs, const stack<T,Container> &rhs)
{
	return !(lhs == rhs);
}

template<typename T, typename Container>
inline bool
operator<(const stack<T,Container> &lhs, const stack<T,Container> &rhs)
{
	return lhs._c < rhs._c;
}

template<typename T, typename Container>
inline bool
operator>(const stack<T,Container> &lhs, const stack<T,Container> &rhs)
{
	return rhs > lhs;
}

template<typename T, typename Container>
inline bool
operator<=(const stack<T,Container> &lhs, const stack<T,Container> &rhs)
{
	return !(lhs > rhs);
}

template<typename T, typename Container>
inline bool
operator>=(const stack<T,Container> &lhs, const stack<T,Container> &rhs)
{
	return !(rhs < lhs);
}


} // namespace ft

#include "stack.tpp"