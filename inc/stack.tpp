/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 16:54:27 by skienzle          #+#    #+#             */
/*   Updated: 2022/02/20 18:59:47 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{


// public methods

template<typename T, typename Container>
stack<T,Container>::stack(const container_type &cntr): _c(cntr) {}

template<typename T, typename Container>
bool
stack<T,Container>::empty() const
{
	return this->_c.empty();
}

template<typename T, typename Container>
typename stack<T,Container>::size_type
stack<T,Container>::size() const
{
	return this->_c.size();
}

template<typename T, typename Container>
typename stack<T,Container>::value_type&
stack<T,Container>::top()
{
	return this->_c.back();
}

template<typename T, typename Container>
const typename stack<T,Container>::value_type&
stack<T,Container>::top() const
{
	return this->_c.back();
}

template<typename T, typename Container>
void
stack<T,Container>::push(const value_type &val)
{
	this->_c.push_back(val);
}

template<typename T, typename Container>
void
stack<T,Container>::pop()
{
	this->_c.pop_back();
}


} // namespace ft