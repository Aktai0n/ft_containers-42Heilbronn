/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Itree.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 14:34:38 by skienzle          #+#    #+#             */
/*   Updated: 2022/02/11 21:26:39 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{

template<typename T, typename Compare, typename Alloc>
class Itree
{
public: // types
	typedef T					value_type;
	typedef Compare				value_compare;
	typedef Alloc				allocator_type;

public: // methods
	virtual void traverse() = 0;
	virtual bool empty() = 0;
	virtual void insert(const value_type& data) = 0;
	virtual void erase(const value_type& data) = 0;
	virtual void clear() = 0;
	virtual ~Itree() {};
};

} // namespace ft