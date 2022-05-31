/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tests.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:53:59 by skienzle          #+#    #+#             */
/*   Updated: 2022/05/31 12:45:18 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"
#include "timer.hpp"
#include "my_int.hpp"


template<typename T>
void assignment(std::ostream& out, vector<T>& vec_short, vector<T>& vec_middle, vector<T>& vec_long)
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
void iterators(std::ostream& out, vector<T>& vec_long)
{
	typename vector<T>::iterator it = vec_long.begin();
	typename vector<T>::iterator ite = vec_long.end();
	typename vector<T>::const_iterator cit = vec_long.begin();
	typename vector<T>::const_iterator cite = vec_long.end();
	typename vector<T>::reverse_iterator rit = vec_long.rbegin();
	typename vector<T>::reverse_iterator rite = vec_long.rend();
	typename vector<T>::const_reverse_iterator crit = vec_long.rbegin();
	typename vector<T>::const_reverse_iterator crite = vec_long.rend();

	it++;
	it--;
	ite--;
	ite++;
	++rit;
	--rit;
	rit++;
	rit--;
	FPRINT(out, "it - ite" << it - ite);
	FPRINT(out, "rit - rite" << rit - rite);
	


}

template<typename T>
void relational_operators(std::ostream& out, vector<T>& vec_short, vector<T>& vec_middle, vector<T>& vec_long)
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
void swap_vec(std::ostream& out, vector<T>& vec_short, vector<T>& vec_middle, vector<T>& vec_long)
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

void
vector_tests(std::ostream& out)
{
	print_header("vector");
	
	Timer<> timer;
	vector<int> vec_short;
	vector<int> vec_middle(1000);
	vector<int> vec_long(vec_middle.begin(), vec_middle.end());
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
	timer.start();
	assignment(out, vec_short, vec_middle, vec_long);
	print_test_time("assignment operator: ", timer.stop());




	timer.start();
	relational_operators(out, vec_short, vec_middle, vec_long);
	print_test_time("relational operators: ", timer.stop());

	timer.start();
	swap_vec(out, vec_short, vec_middle, vec_long);
	print_test_time("relational operators: ", timer.stop());
	
	
	FPRINT(out, "\n-------------------------------------------------------------------\n");
#if 0
	






	
	vector<int> my_vec;
	FPRINT(out, "capacity? " << my_vec.capacity());
	for (int i = 0; i < 10; ++i)
		my_vec.push_back(i);
	FPRINT(out, "capacity? " << my_vec.capacity());
	print_container(my_vec);
	{
		FPRINT(out, "-------------------------------------------------------------------");
		vector<int> comp;
		comp.push_back(10);
		comp.push_back(50);
		my_vec.assign(comp.begin(), comp.end());
	}
	my_vec.assign(5, 100);
	print_container(my_vec);
	FPRINT(out, "capacity: " << my_vec.capacity());
	FPRINT(out, "-------------------------------------------------------------------");
	FPRINT(out, "inserting 200 elements:");
	vector<int>::iterator it = my_vec.begin();
	it += 5;
	my_vec.insert(it, 5, 10);
	print_container(my_vec);
	set<int> my_set(my_vec.begin(), my_vec.end());
	my_vec.insert(my_vec.begin() + 2, my_set.begin(), my_set.end());
	print_container(my_vec);
#endif

	#ifdef FT_MODE
	print_test_time("\tft::vector total: ", timer.get_total_time());
	#else
	print_test_time("\tstd::vector total: ", timer.get_total_time());
	#endif
}
