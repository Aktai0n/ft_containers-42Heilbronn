/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_tests.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:13:07 by skienzle          #+#    #+#             */
/*   Updated: 2022/05/31 19:20:00 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"
#include "print.hpp"
#include "timer.hpp"
#include "my_int.hpp"
#include "MutantStack.hpp"

#define NUM_ELEMENTS 10000

template<typename T, typename Cntr>
void print_stack(std::ostream& out, const stack<T,Cntr>& c)
{
	FPRINT(out, "empty? " << (c.empty() ? "true" : "false"));
	FPRINT(out, "container size: " << c.size());
	if (!c.empty())
		FPRINT(out, "top: " << c.top());
}

template<typename T>
void push(std::ostream& out, stack<T, vector<T> >& st, stack<T, std::deque<T> >& st_deq)
{
	for (int i = 0; i < NUM_ELEMENTS; ++i)
		st.push(T(i));
	for (int i = 0; i < NUM_ELEMENTS; ++i)
		st_deq.push(T(i));
	print_stack(out, st);
	print_stack(out, st_deq);
}

template<typename T>
void pop(std::ostream& out, stack<T, vector<T> >& st, stack<T, std::deque<T> >& st_deq)
{
	for (int i = 0; i < NUM_ELEMENTS; ++i)
		st.pop();
	for (int i = 0; i < NUM_ELEMENTS; ++i)
		st_deq.pop();
	print_stack(out, st);
	print_stack(out, st_deq);
}

template<typename T>
void relational_operators(std::ostream& out, stack<T, vector<T> >& st)
{
	stack<T, vector<T> > comp;
	for (int i = 0; i < NUM_ELEMENTS; ++i)
		comp.push(T(i));
	FPRINT(out, "stack1 == stack2? " << (st == comp));
	FPRINT(out, "stack1 != stack2? " << (st != comp));
	FPRINT(out, "stack1 < stack2? " << (st < comp));
	FPRINT(out, "stack1 > stack2? " << (st > comp));
	FPRINT(out, "stack1 <= stack2? " << (st <= comp));
	FPRINT(out, "stack1 >= stack2? " << (st >= comp));
}

template<typename T>
void relational_operators(std::ostream& out, stack<T, std::deque<T> >& st)
{
	stack<T, std::deque<T> > comp;
	FPRINT(out, "stack1 == stack2? " << (st == comp));
	FPRINT(out, "stack1 != stack2? " << (st != comp));
	FPRINT(out, "stack1 < stack2? " << (st < comp));
	FPRINT(out, "stack1 > stack2? " << (st > comp));
	FPRINT(out, "stack1 <= stack2? " << (st <= comp));
	FPRINT(out, "stack1 >= stack2? " << (st >= comp));
}

template<typename T>
void mutant_stack(std::ostream& out)
{
	MutantStack<T> mstack;
	for (int i = 0; i < NUM_ELEMENTS; ++i)
		mstack.push(T(i));
	print_stack(out, mstack);
	for (typename MutantStack<T>::const_iterator it = mstack.begin(); it != mstack.end(); ++it)
		out << *it << ", ";
	out << '\n';
}

void stack_tests(std::ostream& out)
{
	print_header("stack");
	
	Timer<> timer;
	stack<int, vector<int> > st;
	stack<int, std::deque<int> > st_deq;
	stack<my_int, vector<my_int> > my_st;
	stack<my_int, std::deque<my_int> > my_st_deq;
	print_test_time("constructors: ", timer.stop());
	timer.start();
	print_stack(out, st);
	print_stack(out, my_st);
	print_stack(out, st_deq);
	print_stack(out, my_st_deq);
	print_test_time("empty and size: ", timer.stop());

	timer.start();
	push(out, st, st_deq);
	push(out, my_st, my_st_deq);
	print_test_time("push: ", timer.stop());

	timer.start();
	relational_operators(out, st);
	relational_operators(out, my_st);
	relational_operators(out, st);
	relational_operators(out, my_st);
	print_test_time("relational operators: ", timer.stop());

	timer.start();
	pop(out, st, st_deq);
	pop(out, my_st, my_st_deq);
	print_test_time("pop: ", timer.stop());

	timer.start();
	mutant_stack<int>(out);
	mutant_stack<my_int>(out);
	print_test_time("mutant_stack: ", timer.stop());

	#if FT_MODE
	print_end_time("ft::stack", timer.get_total_time());
	#else
	print_end_time("std::stack", timer.get_total_time());
	#endif
}