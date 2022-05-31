/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:05:52 by skienzle          #+#    #+#             */
/*   Updated: 2022/05/31 12:37:48 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <fstream>
#include "MutantStack.hpp"

#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"

#define PRINT(msg) (std::cout << msg << '\n')
#define FPRINT(out, msg) (out << msg << '\n')
#define CPRINT(color, msg) (std::cout << color << msg << RESET << '\n')


template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& lhs, const pair<T1,T2>& rhs)
{
	lhs << "First: " << rhs.first << " Second: " << rhs.second;
	return lhs;
}

template<typename Key, typename Value, typename Comp, typename Alloc,
		template<typename, typename, typename, typename> class Map>
void
print_capacity(__attribute((unused)) std::ostream& out,
				__attribute((unused)) const Map<Key,Value,Comp,Alloc>& c)
{}

template<typename Value, typename Comp, typename Alloc,
		template<typename, typename, typename> class Set>
void
print_capacity(__attribute((unused)) std::ostream& out,
				__attribute((unused)) const Set<Value,Comp,Alloc>& c)
{}

template<typename Value, typename Alloc,
		template<typename, typename> class Vector>
void
print_capacity(std::ostream& out, const Vector<Value,Alloc>& c)
{
	FPRINT(out, "capacity: " << c.capacity());
}

template<typename Container>
void
print_container(std::ostream& out, const Container& c)
{
	FPRINT(out, "container size: " << c.size());
	FPRINT(out, "empty? " << (c.empty() ? "true" : "false"));
	print_capacity(out, c);
	FPRINT(out, "content:");
	typename Container::const_iterator ite = c.end();
	for (typename Container::const_iterator it = c.begin(); it != ite; ++it)
	{
		out << *it << ", ";
	}
	
	FPRINT(out, "\n-------------------------------------------------------------------");
}

void print_header(const char *cntr_name);
void print_test_time(const char *testcase, double time);
