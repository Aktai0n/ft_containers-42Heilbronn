/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:54:20 by skienzle          #+#    #+#             */
/*   Updated: 2022/06/01 21:08:39 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../config.hpp"
#include "./helpers/timer.hpp"
#include "./helpers/my_int.hpp"
#include "./helpers/print.hpp"

template<typename T>
static void assignment(std::ostream& out, set<T>& set_small, set<T>& set_middle, set<T>& set_big)
{
	set<T> test;
	
	test = set_small;
	print_container(out, test);
	test = set_middle;
	print_container(out, test);
	test = set_big;
	print_container(out, test);
}

template<typename T>
static void iterators(std::ostream& out, set<T>& s)
{
	typename set<T>::iterator it = s.begin();
	typename set<T>::iterator ite = s.end();
	typename set<T>::const_iterator cit = s.begin();
	typename set<T>::const_iterator cite = s.end();
	typename set<T>::reverse_iterator rit = s.rbegin();
	typename set<T>::reverse_iterator rite = s.rend();
	typename set<T>::const_reverse_iterator crit = s.rbegin();
	typename set<T>::const_reverse_iterator crite = s.rend();
	
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

	for (size_t i = 0; i < s.size() / 2; ++i)
	{
		FPRINT(out, *it);
		FPRINT(out, *rit);
		// *it= T(i); /* <-- doesn't work for set */
		// *rit = T(i); /* <-- doesn't work for set */
		++rit;
		++it;
	}
	for (size_t i = 0; i < s.size() / 2; ++i)
	{
		FPRINT(out, *cit);
		FPRINT(out, *crit);
		++crit;
		++cit;
	}

	it = s.begin();
	rit = s.rbegin();
	cit = s.begin();
	crit = s.rbegin();

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
	print_container(out, s);
}

template<typename T>
static void erase(std::ostream& out, set<T>& set_small, set<T>& set_middle, set<T>& set_big)
{
	for (size_t i = 0; i < set_small.size(); ++i)
		FPRINT(out, set_small.erase(T(i)));
	print_container(out, set_small);
	set_middle.erase(set_middle.begin(), set_middle.end());
	print_container(out, set_middle);
	for (size_t i = 0; i < set_big.size(); ++i)
	{
		if (i % 2 == 0)
			set_big.erase(set_big.begin());
	}
	print_container(out, set_big);
}

template<typename T>
static void insert(std::ostream& out, set<T>& set_small, set<T>& set_middle, set<T>& set_big,
			const std::deque<T>& deq)
{
	pair<typename set<T>::iterator,bool> result = set_small.insert(T());
	FPRINT(out, "inserted? " << (result.second ? "yes " : "no ") << *result.first);
	result = set_small.insert(T());
	FPRINT(out, "inserted? " << (result.second ? "yes " : "no ") << *result.first);
	typename set<T>::iterator it = set_middle.begin();
	for (size_t i = 0; i < set_middle.size(); ++i)
		it = set_middle.insert(it, T(i));
	set_big.insert(deq.begin(), deq.end());
	print_container(out, set_small);
	print_container(out, set_middle);
	print_container(out, set_big);
}

template<typename T>
static void relational_operators(std::ostream& out, set<T>& set_small, set<T>& set_middle, set<T>& set_big)
{
	FPRINT(out, "set_small == set_middle? " << (set_small == set_middle));
	FPRINT(out, "set_small != set_middle? " << (set_small != set_middle));
	FPRINT(out, "set_small < set_middle? " << (set_small < set_middle));
	FPRINT(out, "set_small > set_middle? " << (set_small > set_middle));
	FPRINT(out, "set_small <= set_middle? " << (set_small <= set_middle));
	FPRINT(out, "set_small >= set_middle? " << (set_small >= set_middle));

	FPRINT(out, "set_big == set_middle? " << (set_big == set_middle));
	FPRINT(out, "set_big != set_middle? " << (set_big != set_middle));
	FPRINT(out, "set_big < set_middle? " << (set_big < set_middle));
	FPRINT(out, "set_big > set_middle? " << (set_big > set_middle));
	FPRINT(out, "set_big <= set_middle? " << (set_big <= set_middle));
	FPRINT(out, "set_big >= set_middle? " << (set_big >= set_middle));
}

template<typename T>
static void swap_set(std::ostream& out, set<T>& set_small, set<T>& set_middle, set<T>& set_big)
{
	set<T> swap1;
	set<T> swap2(set_small.begin(), set_small.end());

	swap(set_small, swap1);
	set_small.swap(swap2);
	swap(set_small, swap1);
	swap(set_middle, swap1);
	swap(set_big, swap2);
	set_big.swap(swap2);
	print_container(out, set_small);
	print_container(out, set_middle);
	print_container(out, set_big);
}

template<typename T>
static void find(std::ostream& out, const set<T>& set_small, set<T>& set_middle, set<T>& set_big)
{
	typename set<T>::iterator it;
	typename set<T>::const_iterator cit;
	for (int i = 0; i < 10000; ++i)
	{
		cit = set_small.find(T(i));
		if (cit != set_small.end())
			out << *cit << ", ";
		it = set_middle.find(T(i));
		if (it != set_middle.end())
			out << *it << ", ";
		it = set_big.find(T(i));
		if (it != set_big.end())
			out << *it << ", ";
	}
	out << '\n';
}

template<typename T>
static void count(std::ostream& out, const set<T>& set_small, set<T>& set_middle, set<T>& set_big)
{
	for (int i = 0; i < 10000; ++i)
	{
		out << set_small.count(T(i)) << ", ";
		out << set_middle.count(T(i)) << ", ";
		out << set_big.count(T(i)) << ", ";
	}
	out << '\n';
}

template<typename T>
static void lower_bound(std::ostream& out, const set<T>& set_small, set<T>& set_middle, set<T>& set_big)
{
	typename set<T>::iterator it;
	typename set<T>::const_iterator cit;
	for (int i = 0; i < 10000; ++i)
	{
		cit = set_small.lower_bound(T(i));
		if (cit != set_small.end())
		{
			for (typename set<T>::const_iterator lower = set_small.begin();
				lower != cit; ++lower)
				out << *lower << ", ";
			out << '\n';
		}
		it = set_middle.lower_bound(T(i));
		if (it != set_middle.end())
		{
			for (typename set<T>::const_iterator lower = set_middle.begin();
				lower != it; ++lower)
				out << *lower << ", ";
			out << '\n';
		}
		it = set_big.lower_bound(T(i));
		if (it != set_big.end())
			FPRINT(out, *it);
	}
}

template<typename T>
static void upper_bound(std::ostream& out, const set<T>& set_small, set<T>& set_middle, set<T>& set_big)
{
	typename set<T>::iterator it;
	typename set<T>::const_iterator cit;
	for (int i = 0; i < 10000; ++i)
	{
		cit = set_small.upper_bound(T(i));
		if (cit != set_small.end())
		{
			for (;cit != set_small.end(); ++cit)
				out << *cit << ", ";
			out << '\n';
		}
		it = set_middle.upper_bound(T(i));
		if (it != set_middle.end())
		{
			for (; it != set_middle.end(); ++it)
				out << *it << ", ";
			out << '\n';
		}
		it = set_big.upper_bound(T(i));
		if (it != set_big.end())
			FPRINT(out, *it);
	}
}

template<typename T>
static void equal_range(std::ostream& out, const set<T>& set_small, set<T>& set_middle, set<T>& set_big)
{
	pair< typename set<T>::iterator, typename set<T>::iterator > p;
	pair< typename set<T>::const_iterator, typename set<T>::const_iterator > cp;
	for (int i = 0; i < 10000; ++i)
	{
		cp = set_small.equal_range(T(i));
		for (; cp.first != cp.second; ++cp.first)
			FPRINT(out, *cp.first);
		p = set_middle.equal_range(T(i));
		for (; p.first != p.second; ++p.first)
			FPRINT(out, *p.first);
		p = set_big.equal_range(T(i));
		for (; p.first != p.second; ++p.first)
			FPRINT(out, *p.first);
	}
}

template<typename T>
static void get_allocator(const set<T>& set_small, set<T>& set_middle, set<T>& set_big)
{
	set_small.get_allocator();
	set_middle.get_allocator();
	set_big.get_allocator();
}

template<typename T>
static void key_comp(const set<T>& set_small, set<T>& set_middle, set<T>& set_big)
{
	set_small.key_comp();
	set_middle.key_comp();
	set_big.key_comp();
}

template<typename T>
static void value_comp(const set<T>& set_small, set<T>& set_middle, set<T>& set_big)
{
	set_small.value_comp();
	set_middle.value_comp();
	set_big.value_comp();
}

template<typename T>
static void clear(set<T>& set_small, set<T>& set_middle, set<T>& set_big)
{
	set_small.clear();
	set_middle.clear();
	set_big.clear();
}

double set_tests(std::ostream& out)
{
	print_header("set");

	std::deque<int> deq;
	std::deque<my_int > deq2;
	for (int i = 0; i < 100; ++i)
	{
		deq.push_back(i);
		deq2.push_back(i);
	}
	print_test_header(out, "set constructors");
	Timer<> timer;
	set<int> set_small;
	set<my_int> my_set_small;
	set<int> set_middle;
	set<my_int> my_set_middle;
	set<int> set_big(deq.begin(), deq.end());
	set<my_int> my_set_big(deq2.begin(), deq2.end());

	{
		set<int> copy(set_big);
		set<my_int> copy2(my_set_big);
		print_container(out, set_small);
		print_container(out, set_middle);
		print_container(out, set_big);
		print_container(out, copy);
		print_container(out, copy2);
	}
	print_test_time("constructors: ", timer.stop());


	print_test_header(out, "set assignment operator");
	timer.start();
	assignment(out, set_small, set_middle, set_big);
	assignment(out, my_set_small, my_set_middle, my_set_big);
	print_test_time("assignment operator: ", timer.stop());

	print_test_header(out, "set iterators");
	timer.start();
	iterators(out, set_big);
	iterators(out, my_set_big);
	print_test_time("iterators: ", timer.stop());

	print_test_header(out, "set erase");
	timer.start();
	erase(out, set_small, set_middle, set_big);
	erase(out, my_set_small, my_set_middle, my_set_big);
	print_test_time("erase: ", timer.stop());

	{
		print_test_header(out, "set insert");
		timer.start();
		insert(out, set_small, set_middle, set_big, deq);
		insert(out, my_set_small, my_set_middle, my_set_big, deq2);
		print_test_time("insert: ", timer.stop());
	}

	print_test_header(out, "set relational operators");
	timer.start();
	relational_operators(out, set_small, set_middle, set_big);
	relational_operators(out, my_set_small, my_set_middle, my_set_big);
	print_test_time("relational operators: ", timer.stop());

	print_test_header(out, "set swap");
	timer.start();
	swap_set(out, set_small, set_middle, set_big);
	swap_set(out, my_set_small, my_set_middle, my_set_big);
	print_test_time("swap: ", timer.stop());

	print_test_header(out, "set find");
	timer.start();
	find(out, set_small, set_middle, set_big);
	find(out, my_set_small, my_set_middle, my_set_big);
	print_test_time("find: ", timer.stop());

	print_test_header(out, "set count");
	timer.start();
	count(out, set_small, set_middle, set_big);
	count(out, my_set_small, my_set_middle, my_set_big);
	print_test_time("count: ", timer.stop());

	print_test_header(out, "set lower_bound");
	timer.start();
	lower_bound(out, set_small, set_middle, set_big);
	lower_bound(out, my_set_small, my_set_middle, my_set_big);
	print_test_time("lower_bound: ", timer.stop());

	print_test_header(out, "set upper_bound");
	timer.start();
	upper_bound(out, set_small, set_middle, set_big);
	upper_bound(out, my_set_small, my_set_middle, my_set_big);
	print_test_time("upper_bound: ", timer.stop());

	print_test_header(out, "set equal_range");
	timer.start();
	equal_range(out, set_small, set_middle, set_big);
	equal_range(out, my_set_small, my_set_middle, my_set_big);
	print_test_time("equal_range: ", timer.stop());

	print_test_header(out, "set get_allocator");
	timer.start();
	get_allocator(set_small, set_middle, set_big);
	get_allocator(my_set_small, my_set_middle, my_set_big);
	print_test_time("get_allocator: ", timer.stop());

	print_test_header(out, "set key_comp");
	timer.start();
	key_comp(set_small, set_middle, set_big);
	key_comp(my_set_small, my_set_middle, my_set_big);
	print_test_time("key_comp: ", timer.stop());

	print_test_header(out, "set value_comp");
	timer.start();
	value_comp(set_small, set_middle, set_big);
	value_comp(my_set_small, my_set_middle, my_set_big);
	print_test_time("value_comp: ", timer.stop());

	print_test_header(out, "set clear");
	timer.start();
	clear(set_small, set_middle, set_big);
	clear(my_set_small, my_set_middle, my_set_big);
	print_test_time("clear: ", timer.stop());

	// #if FT_MODE
	// print_end_time("ft::set", timer.get_total_time());
	// #else
	// print_end_time("std::set", timer.get_total_time());
	// #endif
	PRINT("\n--------------------------------------------------------------------------\n");
	return timer.get_total_time();
}


#ifdef SET_ONLY

int main(int argc, char **argv)
{
	print_mode();
	double set_time = 0.0;

	if (argc == 1)
		set_time = set_tests(std::cout);
	else if (argc == 2)
	{
		std::ofstream outfile(argv[1]);
		if (!outfile.is_open())
		{
			std::cerr << RED << BOLD << "error\n" << "couldn't open the outfile: " << RESET << std::strerror(errno) << std::endl;
			std::exit(errno);
		}
		set_time = set_tests(outfile);
	}
	else
	{
		std::cerr << RED << BOLD << "error\nusage: " << RESET << argv[0] << " <output-filename>" << std::endl;
		std::exit(1);
	}

	std::cout << '\n' << RED << "total:\n" << RESET;
	#if FT_MODE
	print_end_time("ft::set", set_time);
	#else
	print_end_time("std::set", set_time);
	#endif
}

#endif // SET_ONLY