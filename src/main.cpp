/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:46:55 by skienzle          #+#    #+#             */
/*   Updated: 2022/01/25 23:49:38 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <stack>
#include <map>


#include "../inc/vector.hpp"
#include "../inc/stack.hpp"
#include "../inc/map.hpp"

#include <iostream>

#define PRINT(__msg) (std::cout << __msg << std::endl)


int main()
{
	std::vector<int> test;
	ft::vector<int> referencer(5);

	PRINT(referencer.size());
	PRINT(referencer.capacity());
	PRINT(referencer.max_size());
	try
	{
		referencer.at(5);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	// ft::vector<int>::reverse_iterator rit = referencer.rbegin();
	// for (; rit != referencer.rend(); ++rit);
	// test.size_type;
	// test.front();
	// test.size_type hello_world;
	// test.value_type testing;
	// test.allocator_type tester;
	// referencer.size_type hello_world2;
}