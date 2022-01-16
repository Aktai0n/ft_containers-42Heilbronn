/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:46:55 by skienzle          #+#    #+#             */
/*   Updated: 2022/01/16 20:18:01 by skienzle         ###   ########.fr       */
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
	ft::vector<int> referencer;

	PRINT(test.size());
	PRINT(test.capacity());
	PRINT(test.max_size());
	try
	{
		test.at(5);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	// test.size_type;
	// test.front();
	// test.size_type hello_world;
	// test.value_type testing;
	// test.allocator_type tester;
	// referencer.size_type hello_world2;
}