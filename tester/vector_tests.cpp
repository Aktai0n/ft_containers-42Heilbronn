/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tests.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:53:59 by skienzle          #+#    #+#             */
/*   Updated: 2022/06/01 21:00:20 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../config.hpp"
#include "./helpers/timer.hpp"
#include "./helpers/my_int.hpp"
#include "./helpers/print.hpp"


template<typename T>
static void assignment(std::ostream& out, vector<T>& vec_short, vector<T>& vec_middle, vector<T>& vec_long)
{
	vector<T> test;
	
	test = vec_short;
	print_container(out, test);
	test = vec_middle;
	print_container(out, test);
	test = vec_long;
	print_container(out, test);
}

template<typename T>
static void iterators(std::ostream& out, vector<T>& vec)
{
	typename vector<T>::iterator it = vec.begin();
	typename vector<T>::iterator ite = vec.end();
	typename vector<T>::const_iterator cit = vec.begin();
	typename vector<T>::const_iterator cite = vec.end();
	typename vector<T>::reverse_iterator rit = vec.rbegin();
	typename vector<T>::reverse_iterator rite = vec.rend();
	typename vector<T>::const_reverse_iterator crit = vec.rbegin();
	typename vector<T>::const_reverse_iterator crite = vec.rend();

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
	FPRINT(out, "it - ite" << it - ite);
	FPRINT(out, "rit - rite" << rit - rite);
	FPRINT(out, "(it + vec.size()) == ite" << ((it + vec.size()) == ite));
	FPRINT(out, "(ite - vec.size()) == it" << ((ite - vec.size()) == it));
	FPRINT(out, "(rit + vec.size()) == rite " << ((rit + vec.size()) == rite));
	FPRINT(out, "(rite - vec.size()) == rit " << ((rite - vec.size()) == rit));
	for (size_t i = 0; i < vec.size() / 2; ++i)
	{
		FPRINT(out, *it);
		FPRINT(out, *rit);
		*it = T(i);
		*rit = T(i);
		++rit;
		++it;
	}
	for (size_t i = 0; i < vec.size() / 2; ++i)
	{
		FPRINT(out, *cit);
		FPRINT(out, *crit);
		// *cit = T(); /* <- error for const iterators */
		// *crit = T(); /* <- error for const iterators */
		++crit;
		++cit;
	}
	it = vec.begin();
	rit = vec.rbegin();
	cit = vec.begin();
	crit = vec.rbegin();
	for (size_t i = 0; i < vec.size(); ++i)
	{
		FPRINT(out, "iterator: " << it[i] << ", reverse_iterator: " << rit[i]
			<< ", reverse_iterator: " << cit[i] << ", const_reverse_iterator: " << crit[i]);
	}
	FPRINT(out, "middle of the vector: " << *(it += vec.size() / 2)
		<< *(cit += vec.size() / 2) << *(rit += vec.size() / 2) << *(crit += vec.size() / 2)
		<< *(ite -= vec.size() / 2) << *(cite -= vec.size() / 2) << *(rite -= vec.size() / 2)
		<< *(crite -= vec.size() / 2));
	it = vec.begin();
	rit = vec.rbegin();
	cit = vec.begin();
	crit = vec.rbegin();
	ite = vec.end();
	rite = vec.rend();
	cite = vec.end();
	crite = vec.rend();
	
	FPRINT(out, "it < ite " << (it < ite));
	FPRINT(out, "it > ite " << (it < ite));
	FPRINT(out, "it <= ite " << (it <= ite));
	FPRINT(out, "it >= ite" << (it >= ite));
	FPRINT(out, "it == ite " << (it == ite));
	FPRINT(out, "it != cite" << (it != ite));

	FPRINT(out, "it < cite " << (it < cite));
	FPRINT(out, "it > cite " << (it < cite));
	FPRINT(out, "it <= cite " << (it <= cite));
	FPRINT(out, "it >= cite" << (it >= cite));
	FPRINT(out, "it == cite " << (it == cite));
	FPRINT(out, "it != cite" << (it != cite));

	FPRINT(out, "cit < ite " << (cit < ite));
	FPRINT(out, "cit > ite " << (cit < ite));
	FPRINT(out, "cit <= ite " << (cit <= ite));
	FPRINT(out, "cit >= ite" << (cit >= ite));
	FPRINT(out, "cit == ite " << (cit == ite));
	FPRINT(out, "cit != cite" << (cit != ite));

	FPRINT(out, "cit < cite " << (cit < cite));
	FPRINT(out, "cit > cite " << (cit < cite));
	FPRINT(out, "cit <= cite " << (cit <= cite));
	FPRINT(out, "cit >= cite" << (cit >= cite));
	FPRINT(out, "cit == cite " << (cit == cite));
	FPRINT(out, "cit != cite" << (cit != cite));

	FPRINT(out, "rit < rite " << (rit < rite));
	FPRINT(out, "rit > rite " << (rit < rite));
	FPRINT(out, "rit <= rite " << (rit <= rite));
	FPRINT(out, "rit >= rite" << (rit >= rite));
	FPRINT(out, "rit == rite " << (rit == rite));
	FPRINT(out, "rit != ite" << (rit != rite));

	FPRINT(out, "rit < crite " << (rit < crite));
	FPRINT(out, "rit > crite " << (rit < crite));
	FPRINT(out, "rit <= crite " << (rit <= crite));
	FPRINT(out, "rit >= crite" << (rit >= crite));
	FPRINT(out, "rit == crite " << (rit == crite));
	FPRINT(out, "rit != cite" << (rit != crite));

	FPRINT(out, "crit < rite " << (crit < rite));
	FPRINT(out, "crit > rite " << (crit < rite));
	FPRINT(out, "crit <= rite " << (crit <= rite));
	FPRINT(out, "crit >= rite" << (crit >= rite));
	FPRINT(out, "crit == rite " << (crit == rite));
	FPRINT(out, "crit != ite" << (crit != rite));

	FPRINT(out, "crit < crite " << (crit < crite));
	FPRINT(out, "crit > crite " << (crit < crite));
	FPRINT(out, "crit <= crite " << (crit <= crite));
	FPRINT(out, "crit >= crite" << (crit >= crite));
	FPRINT(out, "crit == crite " << (crit == crite));
	FPRINT(out, "crit != crite" << (crit != crite));

}

template<typename T>
static void resize(std::ostream& out, vector<T>& vec_short, vector<T>& vec_middle, vector<T>& vec_long)
{
	vec_short.resize(100);
	vec_middle.resize(1000);
	vec_long.resize(10000, T(50));
	print_container(out, vec_short);
	print_container(out, vec_middle);
	print_capacity(out, vec_long);
	vec_short.resize(0);
	vec_short.resize(100, T(20));
	vec_long.resize(1000, T());
	print_container(out, vec_short);
	print_container(out, vec_middle);
	print_capacity(out, vec_long);
}

template<typename T>
void reserve(std::ostream& out, vector<T>& vec_short, vector<T>& vec_middle, vector<T>& vec_long)
{
	vec_short.reserve(100);
	vec_middle.reserve(1000);
	vec_long.reserve(10000);
	print_container(out, vec_short);
	print_container(out, vec_middle);
	print_capacity(out, vec_long);
	vec_short.resize(0);
	vec_short.resize(100);
	vec_long.resize(1000);
	print_container(out, vec_short);
	print_container(out, vec_middle);
	print_capacity(out, vec_long);
}


template<typename T>
static void bracket_operator(std::ostream& out, vector<T>& vec_short, vector<T>& vec_middle, vector<T>& vec_long)
{
	for (size_t i = 0; i < vec_short.size(); ++i)
	{
		vec_short[i] = T(i);
		out << vec_short[i] << ", ";
	}
	for (size_t i = 0; i < vec_middle.size(); ++i)
	{
		vec_middle[i] = T(i * 2);
		out << vec_middle[i] << ", ";
	}
	for (size_t i = 0; i < vec_long.size(); ++i)
	{
		vec_long[i] = T(i * 5);
		out << vec_long[i] << ", ";
	}
}

template<typename T>
static void at(std::ostream& out, vector<T>& vec_short, vector<T>& vec_middle, vector<T>& vec_long)
{
	try
	{
		FPRINT(out, vec_short.at(-1));
	}
	catch(const std::exception& e)
	{
		out << e.what() << '\n';
	}
	try
	{
		FPRINT(out, vec_short.at(10));
	}
	catch(const std::exception& e)
	{
		out << e.what() << '\n';
	}
	try
	{
		FPRINT(out, vec_middle.at(-1));
	}
	catch(const std::exception& e)
	{
		out << e.what() << '\n';
	}
	try
	{
		FPRINT(out, vec_middle.at(10));
	}
	catch(const std::exception& e)
	{
		out << e.what() << '\n';
	}
	try
	{
		FPRINT(out, vec_long.at(-1));
	}
	catch(const std::exception& e)
	{
		out << e.what() << '\n';
	}
	try
	{
		FPRINT(out, vec_long.at(10));
	}
	catch(const std::exception& e)
	{
		out << e.what() << '\n';
	}
}

template<typename T>
static void front_back(std::ostream& out, vector<T>& vec_short, vector<T>& vec_middle, vector<T>& vec_long)
{
	if (!vec_short.empty())
		FPRINT(out, "front: " << vec_short.front());
	if (!vec_middle.empty())
		FPRINT(out, "front: " << vec_middle.front());
	if (!vec_long.empty())
		FPRINT(out, "front: " << vec_long.front());
	if (!vec_short.empty())
		FPRINT(out, "back: " << vec_short.back());
	if (!vec_middle.empty())
		FPRINT(out, "back: " << vec_middle.back());
	if (!vec_long.empty())
		FPRINT(out, "back: " << vec_long.back());
}

template<typename T>
static void assign(std::ostream& out, vector<T>& vec_short, vector<T>& vec_middle, vector<T>& vec_long, const std::deque<T>& deq)
{
	vec_middle.assign(vec_short.begin(), vec_short.end());
	print_container(out, vec_middle);
	vec_long.assign(0, T(500));
	print_container(out, vec_long);
	vec_short.assign(vec_long.begin(), vec_long.end());
	print_container(out, vec_short);
	vec_middle.assign(100, T(-200));
	print_container(out, vec_middle);
	vec_long.assign(deq.begin(), deq.end());
	print_container(out, vec_long);
}

template<typename T>
static void pop_back(std::ostream& out, vector<T>& vec_short, vector<T>& vec_middle, vector<T>& vec_long)
{
	while (!vec_short.empty())
		vec_short.pop_back();
	while (!vec_middle.empty())
		vec_middle.pop_back();
	while (!vec_long.empty())
		vec_long.pop_back();
	print_container(out, vec_short);
	print_container(out, vec_middle);
	print_capacity(out, vec_long);
}

template<typename T>
static void push_back(std::ostream& out, vector<T>& vec_short, vector<T>& vec_middle, vector<T>& vec_long)
{
	for (int i = 0; i < 100; ++i)
		vec_short.push_back(T(i));
	for (int i = 0; i < 1000; ++i)
		vec_middle.push_back(T(-i));
	for (int i = 0; i < 100000; ++i)
		vec_long.push_back(T(i));
	print_container(out, vec_short);
	print_container(out, vec_middle);
	print_capacity(out, vec_long);
}

template<typename T>
static void erase(std::ostream& out, vector<T>& vec_short, vector<T>& vec_middle, vector<T>& vec_long)
{
	vec_short.erase(vec_short.begin());
	vec_short.erase(vec_short.begin() + vec_short.size() / 4);
	print_container(out, vec_short);
	typename vector<T>::iterator middle = vec_middle.begin() + vec_middle.size() / 2;
	typename vector<T>::iterator end = vec_middle.end();
	vec_middle.erase(middle, end);
	print_container(out, vec_middle);
	vec_long.erase(vec_long.begin(), vec_long.end());
	print_container(out, vec_long);
}

template<typename T>
static void insert(std::ostream& out, vector<T>& vec_short, vector<T>& vec_middle, vector<T>& vec_long, const std::deque<T>& deq)
{
	vec_short.insert(vec_short.end(), T());
	vec_short.insert(vec_short.begin(), T(100));
	print_container(out, vec_short);
	vec_middle.insert(vec_middle.begin() + vec_middle.size() / 2, vec_middle.size(), T(-1000));
	print_container(out, vec_middle);
	vec_long.insert(vec_long.end(), deq.begin(), deq.end());
	vec_long.insert(vec_long.begin(), vec_middle.begin(), vec_middle.end());
	print_container(out, vec_long);
}

template<typename T>
static void relational_operators(std::ostream& out, vector<T>& vec_short, vector<T>& vec_middle, vector<T>& vec_long)
{
	FPRINT(out, "vector_short == vector_middle? " << (vec_short == vec_middle));
	FPRINT(out, "vector_short != vector_middle? " << (vec_short != vec_middle));
	FPRINT(out, "vector_short < vector_middle? " << (vec_short < vec_middle));
	FPRINT(out, "vector_short > vector_middle? " << (vec_short > vec_middle));
	FPRINT(out, "vector_short <= vector_middle? " << (vec_short <= vec_middle));
	FPRINT(out, "vector_short >= vector_middle? " << (vec_short >= vec_middle));

	FPRINT(out, "vector_long == vector_middle? " << (vec_long == vec_middle));
	FPRINT(out, "vector_long != vector_middle? " << (vec_long != vec_middle));
	FPRINT(out, "vector_long < vector_middle? " << (vec_long < vec_middle));
	FPRINT(out, "vector_long > vector_middle? " << (vec_long > vec_middle));
	FPRINT(out, "vector_long <= vector_middle? " << (vec_long <= vec_middle));
	FPRINT(out, "vector_long >= vector_middle? " << (vec_long >= vec_middle));
}

template<typename T>
static void swap_vec(std::ostream& out, vector<T>& vec_short, vector<T>& vec_middle, vector<T>& vec_long)
{
	vector<T> swap1;
	vector<T> swap2(50);
	
	swap(vec_short, swap1);
	vec_short.swap(swap2);
	swap(vec_short, swap1);
	swap(vec_middle, swap1);
	swap(vec_long, swap2);
	vec_long.swap(swap2);
	print_container(out, vec_short);
	print_container(out, vec_middle);
	print_container(out, vec_long);
}

template<typename T>
static void clear(std::ostream& out, vector<T>& vec_short, vector<T>& vec_middle, vector<T>& vec_long)
{
	vec_short.clear();
	vec_middle.clear();
	vec_long.clear();
	print_container(out, vec_short);
	print_container(out, vec_middle);
	print_container(out, vec_long);
}

template<typename T>
static void get_allocator(vector<T>& vec_short, vector<T>& vec_middle, vector<T>& vec_long)
{
	vec_short.get_allocator();
	vec_middle.get_allocator();
	vec_long.get_allocator();
}

double vector_tests(std::ostream& out)
{
	print_header("vector");
	
	print_test_header(out, "vector constructors");
	Timer<> timer;
	vector<int> vec_short;
	vector<int> vec_middle(1000);
	vector<int> vec_long(vec_middle.begin(), vec_middle.end());
	vector<my_int> my_vec_short;
	vector<my_int> my_vec_middle(1000);
	vector<my_int> my_vec_long(my_vec_middle.begin(), my_vec_middle.end());
	{
		vector<my_int> range(500, 20);
		vector<int> copy(vec_long);
		print_container(out, vec_short);
		print_container(out, vec_middle);
		print_container(out, vec_long);
		print_container(out, copy);
		print_container(out, range);
	}
	print_test_time("constructors: ", timer.stop());

	print_test_header(out, "vector assignment operator");
	timer.start();
	assignment(out, vec_short, vec_middle, vec_long);
	assignment(out, my_vec_short, my_vec_middle, my_vec_long);
	print_test_time("assignment operator: ", timer.stop());

	print_test_header(out, "vector iterators");
	timer.start();
	iterators(out, vec_long);
	iterators(out, my_vec_long);
	print_test_time("iterators: ", timer.stop());

	print_test_header(out, "vector resize");
	timer.start();
	resize(out, vec_short, vec_middle, vec_long);
	resize(out, my_vec_short, my_vec_middle, my_vec_long);
	print_test_time("resize: ", timer.stop());

	print_test_header(out, "vector reserve");
	timer.start();
	reserve(out, vec_short, vec_middle, vec_long);
	reserve(out, my_vec_short, my_vec_middle, my_vec_long);
	print_test_time("reserve: ", timer.stop());

	print_test_header(out, "vector operator[]");
	timer.start();
	bracket_operator(out, vec_short, vec_middle, vec_long);
	bracket_operator(out, my_vec_short, my_vec_middle, my_vec_long);
	print_test_time("operator[]: ", timer.stop());

	print_test_header(out, "vector at");
	timer.start();
	at(out, vec_short, vec_middle, vec_long);
	at(out, my_vec_short, my_vec_middle, my_vec_long);
	print_test_time("at: ", timer.stop());

	print_test_header(out, "vector front and back");
	timer.start();
	front_back(out, vec_short, vec_middle, vec_long);
	front_back(out, my_vec_short, my_vec_middle, my_vec_long);
	print_test_time("front and back: ", timer.stop());

	{
		std::deque<int> deq(1000, -500);
		std::deque<my_int> my_deq(1000, -500);
		print_test_header(out, "vector assign");
		timer.start();
		assign(out, vec_short, vec_middle, vec_long, deq);
		assign(out, my_vec_short, my_vec_middle, my_vec_long, my_deq);
		print_test_time("assign: ", timer.stop());
	}

	print_test_header(out, "vector pop_back");
	timer.start();
	pop_back(out, vec_short, vec_middle, vec_long);
	pop_back(out, my_vec_short, my_vec_middle, my_vec_long);
	print_test_time("pop_back: ", timer.stop());

	print_test_header(out, "vector push_back");
	timer.start();
	push_back(out, vec_short, vec_middle, vec_long);
	push_back(out, my_vec_short, my_vec_middle, my_vec_long);
	print_test_time("push_back: ", timer.stop());

	print_test_header(out, "vector erase");
	timer.start();
	erase(out, vec_short, vec_middle, vec_long);
	erase(out, my_vec_short, my_vec_middle, my_vec_long);
	print_test_time("erase: ", timer.stop());

	{
		std::deque<int> deq(1000, -500);
		std::deque<my_int> my_deq(1000, -500);
		print_test_header(out, "vector insert");
		timer.start();
		insert(out, vec_short, vec_middle, vec_long, deq);
		insert(out, my_vec_short, my_vec_middle, my_vec_long, my_deq);
		print_test_time("insert: ", timer.stop());
	}

	print_test_header(out, "vector get_allocator");
	timer.start();
	get_allocator(vec_short, vec_middle, vec_long);
	get_allocator(my_vec_short, my_vec_middle, my_vec_long);
	print_test_time("get_allocator: ", timer.stop());

	print_test_header(out, "vector relational operators");
	timer.start();
	relational_operators(out, vec_short, vec_middle, vec_long);
	relational_operators(out, my_vec_short, my_vec_middle, my_vec_long);
	print_test_time("relational operators: ", timer.stop());

	print_test_header(out, "vector swap");
	timer.start();
	swap_vec(out, vec_short, vec_middle, vec_long);
	swap_vec(out, my_vec_short, my_vec_middle, my_vec_long);
	print_test_time("swap: ", timer.stop());

	print_test_header(out, "vector clear");
	timer.start();
	clear(out, vec_short, vec_middle, vec_long);
	clear(out, my_vec_short, my_vec_middle, my_vec_long);
	print_test_time("clear: ", timer.stop());

	PRINT("\n--------------------------------------------------------------------------\n");
	return timer.get_total_time();
}


#ifdef VECTOR_ONLY

int main(int argc, char **argv)
{
	print_mode();
	double vec_time = 0.0;

	if (argc == 1)
		vec_time = vector_tests(std::cout);
	else if (argc == 2)
	{
		std::ofstream outfile(argv[1]);
		if (!outfile.is_open())
		{
			std::cerr << RED << BOLD << "error\n" << "couldn't open the outfile: " << RESET << std::strerror(errno) << std::endl;
			std::exit(errno);
		}
		vec_time = vector_tests(outfile);
	}
	else
	{
		std::cerr << RED << BOLD << "error\nusage: " << RESET << argv[0] << " <output-filename>" << std::endl;
		std::exit(1);
	}

	std::cout << '\n' << RED << "total:\n" << RESET;
	#if FT_MODE
	print_end_time("ft::vector", vec_time);
	#else
	print_end_time("std::vector", vec_time);
	#endif
}

#endif // VECTOR_ONLY