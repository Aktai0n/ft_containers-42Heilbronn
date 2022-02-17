/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:46:55 by skienzle          #+#    #+#             */
/*   Updated: 2022/02/17 22:15:31 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <stack>
#include <map>


#include <iostream>
#include <string>

#include "../inc/vector.hpp"
#include "../inc/stack.hpp"
#include "../inc/map.hpp"

#define PRINT(__msg) (std::cout << __msg << std::endl)


template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& lhs, const ft::pair<T1,T2>& rhs)
{
	lhs << "First: " << rhs.first << " Second: " << rhs.second;
	return lhs;
}


template<typename Container>
void
print_container(const Container &c)
{
	typename Container::const_iterator ite = c.end();
	for (typename Container::const_iterator it = c.begin(); it != ite; ++it)
	{
		PRINT(*it);
	}
}


void map_benchmark()
{
	using namespace ft;
	map<std::string,int> ft_test_map;
	ft_test_map.insert(make_pair("zalf", 10));
	ft_test_map.insert(make_pair("robin", 45));
	// ft_test_map.erase("alf");
	ft_test_map.insert(make_pair("robin", 100));
	// ft_test_map.erase("robin");
	for (int i = 0; i < 10; ++i)
	{
		std::string temp("name");
		temp.push_back(i * 2 + '0');
		ft_test_map.insert(ft::make_pair(temp, i));
	}
	ft_test_map.insert(make_pair("name5", 500));
	// 	for (int i = 0; i < 10; ++i)
	// {
	// 	std::string temp("name");
	// 	temp.push_back(i + '0');
	// 	ft_test_map.erase(temp);
	// }
	// ft_test_map.erase(std::string("name5"));
	ft_test_map.erase(std::string("robin"));
	map<std::string,int> copy_map = ft_test_map;
	print_container(ft_test_map);
	print_container(copy_map);
	// for (map<std::string,int>::iterator it = ft_test_map.begin(); it != ft_test_map.end(); ++it)
	// 	std::cout << (*it).first << std::endl;
}


int main()
{
	// const std::vector<int> test;
	// ft::vector<int> ft_test(5, 10);
	// const ft::vector<int> referencer(5);
	map_benchmark();

	// PRINT(referencer.size());
	// PRINT(referencer.capacity());
	// PRINT(referencer.max_size());
	// std::vector<int>::const_reverse_iterator rit = test.rbegin();
	// (void)rit;
	// ft::vector<int>::reverse_iterator it = ft_test.rbegin();
	// for (; it != ft_test.rend(); ++it)
	// 	PRINT(*it);
	// try
	// {
	// 	referencer.at(5);
	// }
	// catch(const std::exception& e)
	// {
	// 	std::cerr << e.what() << '\n';
	// }
	// ft::vector<int>::reverse_iterator rit = referencer.rbegin();
	// for (; rit != referencer.rend(); ++rit);
	// test.size_type;
	// test.front();
	// test.size_type hello_world;
	// test.value_type testing;
	// test.allocator_type tester;
	// referencer.size_type hello_world2;
	// std::map<int, int> test_map;
	// std::map<int, int> test_map2;
	// test_map.insert(std::make_pair(5, 2));
	// test_map.insert(std::make_pair(5, 10));
	// print_container(test_map);
}