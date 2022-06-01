/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:54:10 by skienzle          #+#    #+#             */
/*   Updated: 2022/06/01 18:18:06 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../config.hpp"
#include "./helpers/timer.hpp"
#include "./helpers/my_int.hpp"
#include "./helpers/print.hpp"

typedef map<int, my_int> map_int;
typedef map<my_int, int> map_my_int;
typedef pair<int, my_int> pair_int;
typedef pair<my_int, int> pair_my_int;

template<typename Key, typename T>
static void assignment(std::ostream& out, map<Key,T>& map_small, map<Key,T>& map_middle, map<Key,T>& map_big)
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
static void iterators(std::ostream& out, map<Key,T>& m)
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
static void insert(std::ostream& out, map<Key,T>& map_small, map<Key,T>& map_middle, map<Key,T>& map_big,
			const std::deque< pair<Key,T> >& deq)
{
	pair<typename map<Key,T>::iterator,bool> result = map_small.insert(pair<Key,T>(Key(), T()));
	FPRINT(out, "inserted? " << (result.second ? "yes " : "no ") << *result.first);
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

template<typename Key, typename T>
static void relational_operators(std::ostream& out, map<Key,T>& map_small, map<Key,T>& map_middle, map<Key,T>& map_big)
{
	FPRINT(out, "map_small == map_middle? " << (map_small == map_middle));
	FPRINT(out, "map_small != map_middle? " << (map_small != map_middle));
	FPRINT(out, "map_small < map_middle? " << (map_small < map_middle));
	FPRINT(out, "map_small > map_middle? " << (map_small > map_middle));
	FPRINT(out, "map_small <= map_middle? " << (map_small <= map_middle));
	FPRINT(out, "map_small >= map_middle? " << (map_small >= map_middle));

	FPRINT(out, "map_big == map_middle? " << (map_big == map_middle));
	FPRINT(out, "map_big != map_middle? " << (map_big != map_middle));
	FPRINT(out, "map_big < map_middle? " << (map_big < map_middle));
	FPRINT(out, "map_big > map_middle? " << (map_big > map_middle));
	FPRINT(out, "map_big <= map_middle? " << (map_big <= map_middle));
	FPRINT(out, "map_big >= map_middle? " << (map_big >= map_middle));
}

template<typename Key, typename T>
static void swap_map(std::ostream& out, map<Key,T>& map_small, map<Key,T>& map_middle, map<Key,T>& map_big)
{
	map<Key,T> swap1;
	map<Key,T> swap2(map_small.begin(), map_small.end());

	swap(map_small, swap1);
	map_small.swap(swap2);
	swap(map_small, swap1);
	swap(map_middle, swap1);
	swap(map_big, swap2);
	map_big.swap(swap2);
	print_container(out, map_small);
	print_container(out, map_middle);
	print_container(out, map_big);
}

template<typename Key, typename T>
static void find(std::ostream& out, const map<Key,T>& map_small, map<Key,T>& map_middle, map<Key,T>& map_big)
{
	typename map<Key,T>::iterator it;
	typename map<Key,T>::const_iterator cit;
	for (int i = 0; i < 10000; ++i)
	{
		cit = map_small.find(Key(i));
		if (cit != map_small.end())
		{
			out << *cit << ", ";
			// cit->second = T(i); /* <-- error for const_iterator */
		}
		it = map_middle.find(Key(i));
		if (it != map_middle.end())
		{
			out << *it << ", ";
			it->second = T(-i);
		}
		it = map_big.find(Key(i));
		if (it != map_big.end())
		{
			out << *it << ", ";
			it->second = T(i * 5);
		}
	}
	out << '\n';
}

template<typename Key, typename T>
static void count(std::ostream& out, const map<Key,T>& map_small, map<Key,T>& map_middle, map<Key,T>& map_big)
{
	for (int i = 0; i < 10000; ++i)
	{
		out << map_small.count(Key(i)) << ", ";
		out << map_middle.count(Key(i)) << ", ";
		out << map_big.count(Key(i)) << ", ";
	}
	out << '\n';
}

template<typename Key, typename T>
static void lower_bound(std::ostream& out, const map<Key,T>& map_small, map<Key,T>& map_middle, map<Key,T>& map_big)
{
	typename map<Key,T>::iterator it;
	typename map<Key,T>::const_iterator cit;
	for (int i = 0; i < 10000; ++i)
	{
		cit = map_small.lower_bound(Key(i));
		if (cit != map_small.end())
		{
			for (typename map<Key,T>::const_iterator lower = map_small.begin();
				lower != cit; ++lower)
				out << *lower << ", ";
			out << '\n';
		}
		it = map_middle.lower_bound(Key(i));
		if (it != map_middle.end())
		{
			for (typename map<Key,T>::const_iterator lower = map_middle.begin();
				lower != it; ++lower)
				out << *lower << ", ";
			out << '\n';
		}
		it = map_big.lower_bound(Key(i));
		if (it != map_big.end())
			FPRINT(out, *it);
	}
}

template<typename Key, typename T>
static void upper_bound(std::ostream& out, const map<Key,T>& map_small, map<Key,T>& map_middle, map<Key,T>& map_big)
{
	typename map<Key,T>::iterator it;
	typename map<Key,T>::const_iterator cit;
	for (int i = 0; i < 10000; ++i)
	{
		cit = map_small.upper_bound(Key(i));
		if (cit != map_small.end())
		{
			for (;cit != map_small.end(); ++cit)
				out << *cit << ", ";
			out << '\n';
		}
		it = map_middle.upper_bound(Key(i));
		if (it != map_middle.end())
		{
			for (; it != map_middle.end(); ++it)
				out << *it << ", ";
			out << '\n';
		}
		it = map_big.upper_bound(Key(i));
		if (it != map_big.end())
			FPRINT(out, *it);
	}
}

template<typename Key, typename T>
static void equal_range(std::ostream& out, const map<Key,T>& map_small, map<Key,T>& map_middle, map<Key,T>& map_big)
{
	pair< typename map<Key,T>::iterator, typename map<Key,T>::iterator > p;
	pair< typename map<Key,T>::const_iterator, typename map<Key,T>::const_iterator > cp;
	for (int i = 0; i < 10000; ++i)
	{
		cp = map_small.equal_range(Key(i));
		for (; cp.first != cp.second; ++cp.first)
			FPRINT(out, *cp.first);
		p = map_middle.equal_range(Key(i));
		for (; p.first != p.second; ++p.first)
			FPRINT(out, *p.first);
		p = map_big.equal_range(Key(i));
		for (; p.first != p.second; ++p.first)
			FPRINT(out, *p.first);
	}
}

template<typename Key, typename T>
static void get_allocator(const map<Key,T>& map_small, map<Key,T>& map_middle, map<Key,T>& map_big)
{
	map_small.get_allocator();
	map_middle.get_allocator();
	map_big.get_allocator();
}

template<typename Key, typename T>
static void key_comp(const map<Key,T>& map_small, map<Key,T>& map_middle, map<Key,T>& map_big)
{
	map_small.key_comp();
	map_middle.key_comp();
	map_big.key_comp();
}

template<typename Key, typename T>
static void value_comp(const map<Key,T>& map_small, map<Key,T>& map_middle, map<Key,T>& map_big)
{
	map_small.value_comp();
	map_middle.value_comp();
	map_big.value_comp();
}

template<typename Key, typename T>
static void clear(map<Key,T>& map_small, map<Key,T>& map_middle, map<Key,T>& map_big)
{
	map_small.clear();
	map_middle.clear();
	map_big.clear();
}

double map_tests(std::ostream& out)
{
	print_header("map");

	std::deque<pair<int, my_int> > deq;
	std::deque<pair<my_int, int> > deq2;
	for (int i = 0; i < 100; ++i)
	{
		deq.push_back(pair_int(i, -i));
		deq2.push_back(pair_my_int(i, -i));
	}
	print_test_header(out, "map constructors");
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


	print_test_header(out, "map assignment operator");
	timer.start();
	assignment(out, map_small, map_middle, map_big);
	assignment(out, my_map_small, my_map_middle, my_map_big);
	print_test_time("assignment operator: ", timer.stop());

	print_test_header(out, "map iterators");
	timer.start();
	iterators(out, map_big);
	iterators(out, my_map_big);
	print_test_time("iterators: ", timer.stop());

	print_test_header(out, "map operator[]");
	timer.start();
	bracket_operator(out, map_small, map_middle, map_big);
	bracket_operator(out, my_map_small, my_map_middle, my_map_big);
	print_test_time("operator[]: ", timer.stop());

	print_test_header(out, "map erase");
	timer.start();
	erase(out, map_small, map_middle, map_big);
	erase(out, my_map_small, my_map_middle, my_map_big);
	print_test_time("erase: ", timer.stop());

	{
		print_test_header(out, "map insert");
		timer.start();
		insert(out, map_small, map_middle, map_big, deq);
		insert(out, my_map_small, my_map_middle, my_map_big, deq2);
		print_test_time("insert: ", timer.stop());
	}

	print_test_header(out, "map relational operators");
	timer.start();
	relational_operators(out, map_small, map_middle, map_big);
	relational_operators(out, my_map_small, my_map_middle, my_map_big);
	print_test_time("relational operators: ", timer.stop());

	print_test_header(out, "map swap");
	timer.start();
	swap_map(out, map_small, map_middle, map_big);
	swap_map(out, my_map_small, my_map_middle, my_map_big);
	print_test_time("swap: ", timer.stop());

	print_test_header(out, "map find");
	timer.start();
	find(out, map_small, map_middle, map_big);
	find(out, my_map_small, my_map_middle, my_map_big);
	print_test_time("find: ", timer.stop());

	print_test_header(out, "map count");
	timer.start();
	count(out, map_small, map_middle, map_big);
	count(out, my_map_small, my_map_middle, my_map_big);
	print_test_time("count: ", timer.stop());

	print_test_header(out, "map lower_bound");
	timer.start();
	lower_bound(out, map_small, map_middle, map_big);
	lower_bound(out, my_map_small, my_map_middle, my_map_big);
	print_test_time("lower_bound: ", timer.stop());

	print_test_header(out, "map upper_bound");
	timer.start();
	upper_bound(out, map_small, map_middle, map_big);
	upper_bound(out, my_map_small, my_map_middle, my_map_big);
	print_test_time("upper_bound: ", timer.stop());

	print_test_header(out, "map equal_range");
	timer.start();
	equal_range(out, map_small, map_middle, map_big);
	equal_range(out, my_map_small, my_map_middle, my_map_big);
	print_test_time("equal_range: ", timer.stop());

	print_test_header(out, "map get_allocator");
	timer.start();
	get_allocator(map_small, map_middle, map_big);
	get_allocator(my_map_small, my_map_middle, my_map_big);
	print_test_time("get_allocator: ", timer.stop());

	print_test_header(out, "map key_comp");
	timer.start();
	key_comp(map_small, map_middle, map_big);
	key_comp(my_map_small, my_map_middle, my_map_big);
	print_test_time("key_comp: ", timer.stop());

	print_test_header(out, "map value_comp");
	timer.start();
	value_comp(map_small, map_middle, map_big);
	value_comp(my_map_small, my_map_middle, my_map_big);
	print_test_time("value_comp: ", timer.stop());

	print_test_header(out, "map clear");
	timer.start();
	clear(map_small, map_middle, map_big);
	clear(my_map_small, my_map_middle, my_map_big);
	print_test_time("clear: ", timer.stop());

	PRINT("\n--------------------------------------------------------------------------\n");
	return timer.get_total_time();
}


#ifdef MAP_ONLY

int main(int argc, char **argv)
{
	print_mode();
	double map_time = 0.0;

	if (argc == 1)
		map_time = map_tests(std::cout);
	else if (argc == 2)
	{
		std::ofstream outfile(argv[1]);
		if (!outfile.is_open())
		{
			std::cerr << RED << BOLD << "error\n" << "couldn't open the outfile: " << RESET << std::strerror(errno) << std::endl;
			std::exit(errno);
		}
		map_time = map_tests(outfile);
	}
	else
	{
		std::cerr << RED << BOLD << "error\nusage: " << RESET << argv[0] << " <output-filename>" << std::endl;
		std::exit(1);
	}
	#if FT_MODE
	print_end_time("ft::map", map_time);
	#else
	print_end_time("std::map", map_time);
	#endif
}

#endif // MAP_ONLY