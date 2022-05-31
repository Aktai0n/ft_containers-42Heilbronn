/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:54:10 by skienzle          #+#    #+#             */
/*   Updated: 2022/05/31 22:01:28 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"
#include "timer.hpp"
#include "my_int.hpp"
#include "print.hpp"

typedef map<int, my_int> map_int;
typedef map<my_int, int> map_my_int;
typedef pair<int, my_int> pair_int;
typedef pair<my_int, int> pair_my_int;

template<typename Key, typename T>
void assignment(std::ostream& out, map<Key,T>& map_small, map<Key,T>& map_middle, map<Key,T>& map_big)
{
	map<Key,T> test;
	
	test = map_small;
	print_container(out, test);
	test = map_middle;
	print_container(out, test);
	test = map_big;
	print_container(out, test);
}

template<typename Key, typename T>
void iterators(std::ostream& out, map<Key,T>& m)
{
	typename map<Key,T>::iterator it = m.begin();
	typename map<Key,T>::iterator ite = m.end();
	typename map<Key,T>::const_iterator cit = m.begin();
	typename map<Key,T>::const_iterator cite = m.end();
	typename map<Key,T>::reverse_iterator rit = m.rbegin();
	typename map<Key,T>::reverse_iterator rite = m.rend();
	typename map<Key,T>::const_reverse_iterator crit = m.rbegin();
	typename map<Key,T>::const_reverse_iterator crite = m.rend();
	
	it++;
	it--;
	ite--;
	ite++;
	++rit;
	--rit;
	rit++;
	rit--;
	rite--;
	rite++;
	--rite;
	++rite;

	cit++;
	cit--;
	cite--;
	cite++;
	++crit;
	--crit;
	crit++;
	crit--;
	crite--;
	crite++;
	--crite;
	++crite;

	for (size_t i = 0; i < m.size() / 2; ++i)
	{
		FPRINT(out, *it);
		FPRINT(out, *rit);
		it->second = T(i);
		rit->second = T(i);
		++rit;
		++it;
	}
	for (size_t i = 0; i < m.size() / 2; ++i)
	{
		FPRINT(out, *cit);
		FPRINT(out, *crit);
		// *cit = T(); /* <- error for const iterators */
		// *crit = T(); /* <- error for const iterators */
		++crit;
		++cit;
	}

	it = m.begin();
	rit = m.rbegin();
	cit = m.begin();
	crit = m.rbegin();

	FPRINT(out, "it == ite " << (it == ite));
	FPRINT(out, "it != ite" << (it != ite));

	FPRINT(out, "it == cite " << (it == cite));
	FPRINT(out, "it != cite" << (it != cite));

	FPRINT(out, "cit == ite " << (cit == ite));
	FPRINT(out, "cit != ite" << (cit != ite));

	FPRINT(out, "cit == cite " << (cit == cite));
	FPRINT(out, "cit != cite" << (cit != cite));

	FPRINT(out, "rit == rite " << (rit == rite));
	FPRINT(out, "rit != ite" << (rit != rite));

	FPRINT(out, "rit == crite " << (rit == crite));
	FPRINT(out, "rit != cite" << (rit != crite));

	FPRINT(out, "crit == rite " << (crit == rite));
	FPRINT(out, "crit != ite" << (crit != rite));

	FPRINT(out, "crit == crite " << (crit == crite));
	FPRINT(out, "crit != crite" << (crit != crite));
	print_container(out, m);
}

template<typename Key, typename T>
void bracket_operator(std::ostream& out, map<Key,T>& map_small, map<Key,T>& map_middle, map<Key,T>& map_big)
{
	for (int i = 0; i < 100; ++i)
		map_small[i] = T(i * 2);
	for (int i = 0; i < 1000; ++i)
		map_middle[i] = T(i * -1);
	for (int i = 0; i < 10000; ++i)
		map_big[i] = T(i);
	print_container(out, map_small);
	print_container(out, map_middle);
	print_container(out, map_big);
}

template<typename Key, typename T>
void erase(std::ostream& out, map<Key,T>& map_small, map<Key,T>& map_middle, map<Key,T>& map_big)
{
	for (size_t i = 0; i < map_small.size(); ++i)
		FPRINT(out, map_small.erase(Key(i)));
	print_container(out, map_small);
	map_middle.erase(map_middle.begin(), map_middle.end());
	print_container(out, map_middle);
	for (size_t i = 0; i < map_big.size(); ++i)
	{
		if (i % 2 == 0)
			map_big.erase(map_big.begin());
	}
	print_container(out, map_big);
}

template<typename Key, typename T>
void insert(std::ostream& out, map<Key,T>& map_small, map<Key,T>& map_middle, map<Key,T>& map_big,
			const std::deque< pair<Key,T> >& deq)
{
	pair<typename map<Key,T>::iterator,bool> result = map_small.insert(pair<Key,T>(Key(), T()));
	FPRINT(out, "inserted? " << (result.second ? "yes" : "no") << *result.first);
	result = map_small.insert(pair<Key,T>(Key(), T()));
	FPRINT(out, "inserted? " << (result.second ? "yes " : "no ") << *result.first);
	typename map<Key,T>::iterator it = map_middle.begin();
	for (size_t i = 0; i < map_middle.size(); ++i)
		it = map_middle.insert(it, pair<Key,T>(i, i));
	map_big.insert(deq.begin(), deq.end());
	print_container(out, map_small);
	print_container(out, map_middle);
	print_container(out, map_big);
}


void
map_tests(std::ostream& out)
{
	print_header("map");

	std::deque<pair<int, my_int> > deq;
	std::deque<pair<my_int, int> > deq2;
	for (int i = 0; i < 100; ++i)
	{
		deq.push_back(pair_int(i, -i));
		deq2.push_back(pair_my_int(i, -i));
	}
	Timer<> timer;
	map<int, my_int> map_small;
	map<my_int, int> my_map_small;
	map<int, my_int> map_middle;
	map<my_int, int> my_map_middle;
	map<int, my_int> map_big(deq.begin(), deq.end());
	map<my_int, int> my_map_big(deq2.begin(), deq2.end());

	{
		map_int copy(map_big);
		map_my_int copy2(my_map_big);
		print_container(out, map_small);
		print_container(out, map_middle);
		print_container(out, map_big);
		print_container(out, copy);
		print_container(out, copy2);
	}
	print_test_time("constructors: ", timer.stop());


	timer.start();
	assignment(out, map_small, map_middle, map_big);
	assignment(out, my_map_small, my_map_middle, my_map_big);
	print_test_time("assignment operator: ", timer.stop());

	timer.start();
	iterators(out, map_big);
	iterators(out, my_map_big);
	print_test_time("iterators: ", timer.stop());

	timer.start();
	bracket_operator(out, map_small, map_middle, map_big);
	bracket_operator(out, my_map_small, my_map_middle, my_map_big);
	print_test_time("operator[]: ", timer.stop());

	timer.start();
	erase(out, map_small, map_middle, map_big);
	erase(out, my_map_small, my_map_middle, my_map_big);
	print_test_time("erase: ", timer.stop());

	{
		
		timer.start();
		insert(out, map_small, map_middle, map_big, deq);
		insert(out, my_map_small, my_map_middle, my_map_big, deq2);
		print_test_time("insert: ", timer.stop());
	}

	
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

	#if FT_MODE
	print_end_time("ft::map", timer.get_total_time());
	#else
	print_end_time("std::map", timer.get_total_time());
	#endif
}
