/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:20:08 by skienzle          #+#    #+#             */
/*   Updated: 2022/06/01 17:43:26 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../../config.hpp"

template<typename T>
class MutantStack : public stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename stack<T>::container_type::iterator iterator;
	typedef typename stack<T>::container_type::const_iterator const_iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
	const_iterator  begin() const { return this->c.begin(); }
	const_iterator end() const { return this->c.end(); }
};
