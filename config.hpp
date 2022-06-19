/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 17:31:24 by skienzle          #+#    #+#             */
/*   Updated: 2022/06/19 12:27:12 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifdef FT_MODE

#include "./inc/vector.hpp"
#include "./inc/stack.hpp"
#include "./inc/map.hpp"
#include "./inc/set.hpp"

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

#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <deque>
#include <iostream>


double vector_tests(std::ostream& out);
double stack_tests(std::ostream& out);
double map_tests(std::ostream& out);

#ifdef BONUS
double set_tests(std::ostream& out);
#endif
