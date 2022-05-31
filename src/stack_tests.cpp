/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:13:07 by skienzle          #+#    #+#             */
/*   Updated: 2022/05/30 16:19:37 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../helpers/headers.hpp"


void stack_tests(std::ostream& out)
{
	FPRINT(out, "\n-------------------------------------------------------------------\n");
	FPRINT(out, "tests for stack:\n");
	stack<int> my_stack;
	FPRINT(out, "empty? " << my_stack.empty());
	FPRINT(out, "size? " << my_stack.size());
	for (int i = 0; i < 1000; ++i)
		my_stack.push(i);
	FPRINT(out, "-------------------------------------------------------------------");
	FPRINT(out, "after adding 1000 elements:");
	FPRINT(out, "empty? " << my_stack.empty());
	FPRINT(out, "size? " << my_stack.size());
	FPRINT(out, "top? " << my_stack.top());
	{
		FPRINT(out, "-------------------------------------------------------------------");
		FPRINT(out, "operator overloads:");
		stack<int> comp;
		for (int i = 0; i < 100; ++i)
			comp.push(i);
		FPRINT(out, "stack1 == stack2? " << (my_stack == comp));
		FPRINT(out, "stack1 != stack2? " << (my_stack != comp));
		FPRINT(out, "stack1 < stack2? " << (my_stack < comp));
		FPRINT(out, "stack1 > stack2? " << (my_stack > comp));
		FPRINT(out, "stack1 <= stack2? " << (my_stack <= comp));
		FPRINT(out, "stack1 >= stack2? " << (my_stack >= comp));
	}
	for (int i = 0; i < 100; ++i)
		my_stack.pop();
	FPRINT(out, "-------------------------------------------------------------------");
	FPRINT(out, "after popping 100 elements:");
	FPRINT(out, "empty? " << my_stack.empty());
	FPRINT(out, "size? " << my_stack.size());
	FPRINT(out, "top? " << my_stack.top());
	MutantStack<int> mut_stack;
	for (int i = 0; i < 10; ++i)
		mut_stack.push(i);
	for (MutantStack<int>::iterator it = mut_stack.begin(); it != mut_stack.end(); ++it)
		FPRINT(out, *it);
}