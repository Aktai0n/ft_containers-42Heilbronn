/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:46:55 by skienzle          #+#    #+#             */
/*   Updated: 2022/05/31 12:28:00 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "headers.hpp"
#include "timer.hpp"

#if 0







void set_tests()
{
	set<int> my_set;
	my_set.insert(10);
	my_set.insert(682);
	my_set.insert(289);
	my_set.insert(-3498);
	print_container(my_set);
}

void map_benchmark()
{
	// map<int,std::string> test;
	// test.insert(make_pair(68, "first"));
	// test.insert(make_pair(65, "second"));
	// test.insert(make_pair(70, "third"));
	// test.insert(make_pair(55, "fourth"));
	// test.insert(make_pair(80, "fith"));
	// print_container(test);
	map<std::string,int> ft_test_map;
	ft_test_map.insert(make_pair("zalf", 10));
	ft_test_map.insert(make_pair("robin", 45));
	ft_test_map.erase("alf");
	// ft_test_map.insert(make_pair("robin", 100));
	// ft_test_map.erase("robin");
	for (int i = 0; i < 10; ++i)
	{
		std::string temp("name");
		temp.push_back(i * 2 + '0');
		ft_test_map.insert(pair<std::string,int>(temp, i));
	}
	// map<std::string,int>::iterator iter = ft_test_map.find(std::string("robin"));
	// PRINT(*iter);
	// print_container(ft_test_map);
	// ft_test_map.insert(make_pair("name5", 500));
	for (int i = 0; i < 10; ++i)
	{
		std::string temp("name");
		temp.push_back(i + '0');
		ft_test_map.erase(temp);
	}
	// ft_test_map.erase(std::string("name5"));
	ft_test_map.erase(std::string("robin"));
	// std::cout << __tree_invariant(ft_test_map.end().base()->_left) << std::endl;
	// PRINT(ft_test_map.size());
	// map<std::string,int> copy_map = ft_test_map;
	print_container(ft_test_map);
	// print_container(copy_map);
	// for (map<std::string,int>::iterator it = ft_test_map.begin(); it != ft_test_map.end(); ++it)
	// 	std::cout << (*it).first << std::endl;
}

#endif // 0

void print_header(const char *cntr_name)
{
	CPRINT(BOLD, "\n\t\t\t\t" << cntr_name << ":");
}

void print_test_time(const char *testcase, double time)
{
	std::cout << CYAN;
	std::cout.width(30);
	PRINT(std::left << testcase << time << "ms" << RESET);
}



int main(int argc, char** argv)
{
	#ifdef FT_MODE
	CPRINT(GREEN << BOLD, "\n\t\t\tFT Containers\n");
	#else
	CPRINT(YELLOW << BOLD, "\n\t\t\tSTD Containers\n");
	#endif

	if (argc == 1)
	{
		vector_tests(std::cout);
		// stack_tests(std::cout);
		// map_tests(std::cout);
		#ifdef BONUS
		set_tests(std::cout);
		#endif
	}
	else if (argc == 2)
	{
		std::ofstream outfile(argv[1]);
		if (!outfile.is_open())
		{
			std::cerr << RED << BOLD << "error\n" << "couldn't open the outfile: " << RESET << std::strerror(errno) << std::endl;
			std::exit(errno);
		}
		vector_tests(outfile);
		// stack_tests(outfile);
		// map_tests(outfile);
		#ifdef BONUS
		set_tests(outfile);
		#endif
	}
	else
	{
		std::cerr << RED << BOLD << "error\nusage: " << RESET << argv[0] << " <output-filename>" << std::endl;
		std::exit(1);
	}



	// const std::vector<int> test;
	// vector<int> ft_test(5, 10);
	// const ft::vector<int> referencer(5);
	// map_benchmark();
	// set<int> my_set;
	// my_set.insert(500);
	// PRINT(referencer.size());
	// PRINT(referencer.capacity());
	// PRINT(referencer.max_size());
	// std::vector<int>::const_reverse_iterator rit = test.rbegin();
	// (void)rit;
	// ft::vector<int>::reverse_iterator it = ft_test.rbegin();
	// for (; it != ft_test.rend(); ++it)
	// 	PRINT(*it);
	// try
	// {
	// 	referencer.at(5);
	// }
	// catch(const std::exception& e)
	// {
	// 	std::cerr << e.what() << '\n';
	// }
	// ft::vector<int>::reverse_iterator rit = referencer.rbegin();
	// for (; rit != referencer.rend(); ++rit);
	// test.size_type;
	// test.front();
	// test.size_type hello_world;
	// test.value_type testing;
	// test.allocator_type tester;
	// referencer.size_type hello_world2;
	// std::map<int, int> test_map;
	// std::map<int, int> test_map2;
	// test_map.insert(std::make_pair(5, 2));
	// test_map.insert(std::make_pair(5, 10));
	// print_container(test_map);
	#ifdef FT_MODE
	system("leaks ft_containers");
	#endif
}