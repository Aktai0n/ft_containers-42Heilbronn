/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_int.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:45:57 by skienzle          #+#    #+#             */
/*   Updated: 2022/05/31 19:38:19 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class my_int
{
public:
	my_int(): _ptr(new int()) {}
	my_int(int n): _ptr(new int(n)) {}
	my_int(const my_int& other): _ptr(new int(*other._ptr)) {}

	~my_int() { delete _ptr; }
	
	operator int() const
	{
		return *_ptr;
	}

	bool operator<(const my_int& other) const
	{
		return *_ptr < *other._ptr;
	}

	my_int& operator=(const my_int& other)
	{
		if (this != &other)
		{
			delete _ptr;
			_ptr = new int(*other._ptr);
		}
		return *this;
	}


private:
	int *_ptr;
};

