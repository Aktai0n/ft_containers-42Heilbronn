/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:40:38 by skienzle          #+#    #+#             */
/*   Updated: 2022/02/27 10:36:25 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stack>

#include "vector.hpp"

namespace ft
{

template<typename T, typename Container = ft::vector<T> > class stack;

template<typename T, typename Container>
bool operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs);

template<typename T, typename Container>
bool operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs);

template<typename T, typename Container /* = ft::vector<T> */>
class stack
{
public: // types
	typedef Container							container_type;
	typedef typename container_type::value_type	value_type;
	typedef typename container_type::size_type	size_type;

public: // methods
	explicit stack(const container_type &cntr = container_type());

	~stack() {}; 

	bool				empty() const;
	size_type			size() const;
	value_type			&top();
	const value_type	&top() const;
	void				push(const value_type& val);
	void				pop();

public: // friends
	template<typename T1, typename Container1>
		friend bool operator==(const stack<T1,Container1>& lhs,
								const stack<T1,Container1>& rhs);
	template<typename T1, typename Container1>
		friend bool operator<(const stack<T1,Container1>& lhs,
								const stack<T1,Container1>& rhs);

protected:
	container_type c;
};


// external operator overloads

template<typename T, typename Container>
inline bool
operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
{
	return lhs.c == rhs.c;
}

template<typename T, typename Container>
inline bool
operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
{
	return !(lhs == rhs);
}

template<typename T, typename Container>
inline bool
operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
{
	return lhs.c < rhs.c;
}

template<typename T, typename Container>
inline bool
operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
{
	return rhs < lhs;
}

template<typename T, typename Container>
inline bool
operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
{
	return !(rhs < lhs);
}

template<typename T, typename Container>
inline bool
operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
{
	return !(lhs < rhs);
}


} // namespace ft

#include "stack.tpp"