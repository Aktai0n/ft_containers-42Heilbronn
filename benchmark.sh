#!/bin/bash

trap 'rm -f a.out' EXIT

RESET="\033[0m"
BOLD="\033[1m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
CYAN="\033[36m"

CC="c++"
CFLAGS="-Wall -Werror -Wextra -std=c++98"
SDIR="./tester"
# CFLAGS += " -fsanitize=address"

compile () {
	# 1=source files 2=mode (ft/std) 3=containers 4=executable name

	eval "$CC $CFLAGS ${1} -D${2} -D${3} -o ${4}"
}

run () {
	# 1=source files 2=containers
	compile ${1} "FT_MODE=1" ${2} "./ft_containers"
	eval "./ft_containers ft_output"
	compile ${1} "STD_MODE" ${2} "./std_containers"
	eval "./std_containers std_output"
}

# main () {
# 	echo hello
# 	if [ $# -ne 0 ]; then
# 		echo here
# 		eval "make bonus"
# 	fi
# }

if [[ $# -eq 0 || $1 -eq all ]]; then
	eval "make --silent benchmark"
	eval "./ft_containers ft_output"
	eval "./std_containers std_output"
elif [ $1 -eq vector ]; then
	compile "${SDIR}/vector_tests.cpp" 
fi

# make bonus
# ./ft_containers ft_output 2> ft_error
# ./std_containers std_output 2> std_error
# diff ft_output std_output
# rm ft_output std_output