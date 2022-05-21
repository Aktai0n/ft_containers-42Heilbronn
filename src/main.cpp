/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:46:55 by skienzle          #+#    #+#             */
/*   Updated: 2022/04/16 17:47:47 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifdef FT_MODE

#include "../inc/vector.hpp"
#include "../inc/stack.hpp"
#include "../inc/map.hpp"
#include "../inc/set.hpp"

#define __left_ _left
#define __right_ _right
#define __is_black_ _color
#define __parent_ _parent

using ft::vector;
using ft::stack;
using ft::map;
using ft::set;
using ft::make_pair;
using ft::pair;


#else

#include <vector>
#include <stack>
#include <map>
#include <set>

using std::vector;
using std::stack;
using std::map;
using std::set;
using std::make_pair;
using std::pair;

#endif // FT_MODE

// don't forget to erase those includes in the container files!!!
#include <iostream>
#include <string>
#include <deque>

#define PRINT(__msg) (std::cout << __msg << std::endl)
#define GREEN "\u001b[32m"
#define RED "\u001b[31m"
#define RESET "\u001b[0m"

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

template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& lhs, const pair<T1,T2>& rhs)
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


void stack_tests()
{
	PRINT("\n-------------------------------------------------------------------\n");
	PRINT("tests for stack:\n");
	stack<int> my_stack;
	PRINT("empty? " << my_stack.empty());
	PRINT("size? " << my_stack.size());
	for (int i = 0; i < 1000; ++i)
		my_stack.push(i);
	PRINT("-------------------------------------------------------------------");
	PRINT("after adding 1000 elements:");
	PRINT("empty? " << my_stack.empty());
	PRINT("size? " << my_stack.size());
	PRINT("top? " << my_stack.top());
	{
		PRINT("-------------------------------------------------------------------");
		PRINT("operator overloads:");
		stack<int> comp;
		for (int i = 0; i < 100; ++i)
			comp.push(i);
		PRINT("stack1 == stack2? " << (my_stack == comp));
		PRINT("stack1 != stack2? " << (my_stack != comp));
		PRINT("stack1 < stack2? " << (my_stack < comp));
		PRINT("stack1 > stack2? " << (my_stack > comp));
		PRINT("stack1 <= stack2? " << (my_stack <= comp));
		PRINT("stack1 >= stack2? " << (my_stack >= comp));
	}
	for (int i = 0; i < 100; ++i)
		my_stack.pop();
	PRINT("-------------------------------------------------------------------");
	PRINT("after popping 100 elements:");
	PRINT("empty? " << my_stack.empty());
	PRINT("size? " << my_stack.size());
	PRINT("top? " << my_stack.top());
	MutantStack<int> mut_stack;
	for (int i = 0; i < 10; ++i)
		mut_stack.push(i);
	print_container(mut_stack);
	PRINT("stack done. Press enter to continue");
	std::cin.get();
}

void vector_tests()
{
	PRINT("\n-------------------------------------------------------------------\n");
	PRINT("tests for vector:\n");
	vector<int> my_vec;
	PRINT("capacity? " << my_vec.capacity());
	for (int i = 0; i < 10; ++i)
		my_vec.push_back(i);
	PRINT("capacity? " << my_vec.capacity());
	print_container(my_vec);
	{
		PRINT("-------------------------------------------------------------------");
		vector<int> comp;
		comp.push_back(10);
		comp.push_back(50);
		PRINT("vector1 == vector2? " << (my_vec == comp));
		PRINT("vector1 != vector2? " << (my_vec != comp));
		PRINT("vector1 < vector2? " << (my_vec < comp));
		PRINT("vector1 > vector2? " << (my_vec > comp));
		PRINT("vector1 <= vector2? " << (my_vec <= comp));
		PRINT("vector1 >= vector2? " << (my_vec >= comp));
		my_vec.assign(comp.begin(), comp.end());
	}
	my_vec.assign(20, 100);
	print_container(my_vec);
}

void map_tests()
{
	PRINT("\n-------------------------------------------------------------------\n");
	PRINT("tests for map:\n");
	std::deque<pair<int, std::string> > vec;
	for (int i = 0; i < 10; ++i)
		vec.push_back(ft::make_pair(i, std::string(10 - i, i + 65)));
	map<int, std::string> my_map(vec.begin(), vec.end());
	PRINT("empty? " << my_map.empty());
	PRINT("size? " << my_map.size());
	{
		PRINT("-------------------------------------------------------------------");
		map<int, std::string> comp(my_map);
		// print_container(comp); comp.erase(++comp.begin());
		PRINT("map1 == map2? " << (my_map == comp));
		PRINT("map1 != map2? " << (my_map != comp));
		PRINT("map1 < map2? " << (my_map < comp));
		PRINT("map1 > map2? " << (my_map > comp));
		PRINT("map1 <= map2? " << (my_map <= comp));
		PRINT("map1 >= map2? " << (my_map >= comp));
	}
	PRINT("-------------------------------------------------------------------");
	PRINT("testing erase()");
	PRINT("before:");
	PRINT("empty? " << my_map.empty());
	PRINT("size? " << my_map.size());
	print_container(my_map);
	my_map.erase(++my_map.begin());
	my_map.erase(--my_map.end());
	// print_container(my_map);
	my_map.erase(my_map.begin(), ++(++(++my_map.begin())));
	// print_container(my_map);
	my_map.erase(--(--(--my_map.end())), --my_map.end());
	// print_container(my_map);
	my_map.erase(5);
	// print_container(my_map);
	my_map.erase(8);
	// print_container(my_map);
	my_map.erase(4);
	PRINT("after:");
	print_container(my_map);
	PRINT("empty? " << my_map.empty());
	PRINT("size? " << my_map.size());
	PRINT("-------------------------------------------------------------------");
	PRINT("testing insert()");
	pair<map<int,std::string>::iterator,bool> ret;
	ret = my_map.insert(make_pair(100, "hello world"));
	PRINT("inserted 100? " << (ret.second == true ? "yes" : "no"));
	ret = my_map.insert(make_pair(-50, "alfred"));
	ret = my_map.insert(make_pair(100, "something"));
	PRINT("inserted 100 again? " << (ret.second == true ? "yes" : "no"));
	PRINT("it's value is still: " << *ret.first);
	std::deque<pair<int,std::string> > deq;
	for (int i = 0; i < 90; ++i)
		deq.push_front(ft::make_pair(i, std::string(i, i + 32)));
	my_map.insert(deq.begin(), deq.end());
	my_map.insert(--my_map.end(), make_pair(500, "hello there"));
	my_map.insert(my_map.begin(), make_pair(150, "test"));
	print_container(my_map);
}

void set_tests()
{
	set<int> my_set;
	my_set.insert(10);
	my_set.insert(682);
	my_set.insert(289);
	my_set.insert(-3498);
	print_container(my_set);
}

void map_benchmark()
{
	// map<int,std::string> test;
	// test.insert(make_pair(68, "first"));
	// test.insert(make_pair(65, "second"));
	// test.insert(make_pair(70, "third"));
	// test.insert(make_pair(55, "fourth"));
	// test.insert(make_pair(80, "fith"));
	// print_container(test);
	map<std::string,int> ft_test_map;
	ft_test_map.insert(make_pair("zalf", 10));
	ft_test_map.insert(make_pair("robin", 45));
	ft_test_map.erase("alf");
	// ft_test_map.insert(make_pair("robin", 100));
	// ft_test_map.erase("robin");
	for (int i = 0; i < 10; ++i)
	{
		std::string temp("name");
		temp.push_back(i * 2 + '0');
		ft_test_map.insert(pair<std::string,int>(temp, i));
	}
	// map<std::string,int>::iterator iter = ft_test_map.find(std::string("robin"));
	// PRINT(*iter);
	// print_container(ft_test_map);
	// ft_test_map.insert(make_pair("name5", 500));
	for (int i = 0; i < 10; ++i)
	{
		std::string temp("name");
		temp.push_back(i + '0');
		ft_test_map.erase(temp);
	}
	// ft_test_map.erase(std::string("name5"));
	ft_test_map.erase(std::string("robin"));
	// std::cout << __tree_invariant(ft_test_map.end().base()->_left) << std::endl;
	// PRINT(ft_test_map.size());
	// map<std::string,int> copy_map = ft_test_map;
	print_container(ft_test_map);
	// print_container(copy_map);
	// for (map<std::string,int>::iterator it = ft_test_map.begin(); it != ft_test_map.end(); ++it)
	// 	std::cout << (*it).first << std::endl;
}


int main()
{
	// stack_tests();
	// vector_tests();
	// map_tests();
	// set_tests();



	// const std::vector<int> test;
	// vector<int> ft_test(5, 10);
	// const ft::vector<int> referencer(5);
	// map_benchmark();
	// set<int> my_set;
	// my_set.insert(500);
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