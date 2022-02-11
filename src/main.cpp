/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:46:55 by skienzle          #+#    #+#             */
/*   Updated: 2022/02/11 17:22:32 by skienzle         ###   ########.fr       */
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

template<typename T>
class my_allocator: public std::allocator<T>
{};

int main()
{
	const std::vector<int> test;
	ft::vector<int> ft_test(5, 10);
	const ft::vector<int> referencer(5);
	ft::vector<float, my_allocator<float> > my_test;

	PRINT(referencer.size());
	PRINT(referencer.capacity());
	PRINT(referencer.max_size());
	std::vector<int>::const_reverse_iterator rit = test.rbegin();
	(void)rit;
	ft::vector<int>::reverse_iterator it = ft_test.rbegin();
	for (; it != ft_test.rend(); ++it)
		PRINT(*it);
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
	std::map<int, int> test_map;
	std::map<int, int> test_map2;
	test_map.insert(std::make_pair(5, 2));
	test_map2.insert(std::make_pair(5, 2));
	if (test_map != test_map2)
		;
}