/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:46:55 by skienzle          #+#    #+#             */
/*   Updated: 2022/06/01 18:14:53 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../config.hpp"
#include "./helpers/print.hpp"

int main(int argc, char** argv)
{
	print_mode();

	double vec_time = 0.0;
	double stack_time = 0.0;
	double map_time = 0.0;
	double set_time = 0.0;

	if (argc == 1)
	{
		vec_time = vector_tests(std::cout);
		stack_time = stack_tests(std::cout);
		map_time = map_tests(std::cout);
		#ifdef BONUS
		set_time = set_tests(std::cout);
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
		vec_time = vector_tests(outfile);
		stack_time = stack_tests(outfile);
		map_time = map_tests(outfile);
		#ifdef BONUS
		set_time = set_tests(outfile);
		#endif
	}
	else
	{
		std::cerr << RED << BOLD << "error\nusage: " << RESET << argv[0] << " <output-filename>" << std::endl;
		std::exit(1);
	}

	std::cout << '\n' << RED << "total:\n" << RESET;
	#if FT_MODE
	print_end_time("ft::vector", vec_time);
	print_end_time("ft::stack", stack_time);
	print_end_time("ft::map", map_time);
	print_end_time("ft::set", set_time);
	#else
	print_end_time("std::vector", vec_time);
	print_end_time("std::stack", stack_time);
	print_end_time("std::map", map_time);
	print_end_time("std::set", set_time);
	#endif

	#ifdef FT_MODE
	// system("leaks ft_containers");
	#endif
}