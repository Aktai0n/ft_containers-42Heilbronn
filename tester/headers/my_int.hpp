/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_int.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:45:57 by skienzle          #+#    #+#             */
/*   Updated: 2022/06/26 19:47:04 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

class my_int
{
public:
	my_int(): _ptr(new int()) {}
	my_int(int n): _ptr(new int(n)) {}
	my_int(const my_int& other): _ptr(new int(*other)) {}

	~my_int() { delete _ptr; }

	int operator*() const { return *_ptr; }

	bool operator==(const my_int& rhs) const
	{
		return *(*this) == *rhs;
	}

	bool operator<(const my_int& rhs) const
	{
		return *(*this) < *rhs;
	}

	my_int& operator=(const my_int& other)
	{
		if (this != &other)
		{
			delete _ptr;
			_ptr = new int(*other);
		}
		return *this;
	}

private:
	int *_ptr;
};

inline std::ostream&
operator<<(std::ostream& out, const my_int& rhs)
{
	out << *rhs;
	return out;
}

