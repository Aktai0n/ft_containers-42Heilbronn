/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 17:31:24 by skienzle          #+#    #+#             */
/*   Updated: 2022/05/30 16:20:59 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifdef FT_MODE

#include "../inc/vector.hpp"
#include "../inc/stack.hpp"
#include "../inc/map.hpp"
#include "../inc/set.hpp"

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
#include <cerrno>
#include <fstream>
#include <iostream>
#include <string>
#include <deque>
#include <typeinfo>

void vector_tests(std::ostream& out);
void stack_tests(std::ostream& out);
void map_tests(std::ostream& out);

#ifdef BONUS
void set_tests(std::ostream& out);
#endif


#include "print.hpp"
#include "MutantStack.hpp"