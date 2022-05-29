/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 17:31:24 by skienzle          #+#    #+#             */
/*   Updated: 2022/05/29 17:33:47 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifdef FT_MODE

#include "../vector.hpp"
#include "../stack.hpp"
#include "../map.hpp"
#include "../set.hpp"

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
#include <iostream>
#include <string>
#include <deque>
#include <typeinfo>

#define PRINT(msg) (std::cout << msg << std::endl)
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define BLUE    "\033[34m"
#define RED     "\u001b[31m"