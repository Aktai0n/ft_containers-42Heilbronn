/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:54:10 by skienzle          #+#    #+#             */
/*   Updated: 2022/05/31 11:33:59 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"


void
map_tests(std::ostream& out)
{
	print_header("map");
	FPRINT(out, "test");
#if 0
	PRINT("\n-------------------------------------------------------------------\n");
	PRINT("tests for map:\n");
	std::deque<pair<int, std::string> > vec;
	for (int i = 0; i < 10; ++i)
		vec.push_back(pair<int, std::string>(i, std::string(10 - i, i + 65)));
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
		deq.push_front(pair<int, std::string>(i, std::string(i, i + 32)));
	my_map.insert(deq.begin(), deq.end());
	my_map.insert(--my_map.end(), make_pair(500, "hello there"));
	my_map.insert(my_map.begin(), make_pair(150, "test"));
	print_container(my_map);
#endif
}
