#!/bin/bash

RESET="\033[0m"
BOLD="\033[1m"
RED="\033[91m"
YELLOW="\033[33m"

CC="c++"
CFLAGS="-Wall -Werror -Wextra -std=c++98"
SDIR="./tester"
# CFLAGS += " -fsanitize=address"

FT_OUTFILE="ft_output"
FT_ERROR="ft_error"

STD_OUTFILE="std_output"
STD_ERROR="std_error"

DIFF_FILE="diff_containers"

compile () {
	# 1=source files 2=mode (ft/std) 3=container switch 4=executable name
	eval "$CC $CFLAGS ${1} -D${2} -D${3} -o ${4}"
}

run_one () {
	# 1=container name
	local container_file=$(echo "${SDIR}/${1}_tests.cpp")
	local container_flag=$(echo "${1}_ONLY" | awk '{ print toupper($0) }')
	local ft_executable_name=$(echo "ft_${1}")
	local std_executable_name=$(echo "std_${1}")

	compile ${container_file} "FT_MODE=1" ${container_flag} ${ft_executable_name}
	eval "./${ft_executable_name} ${FT_OUTFILE} 2> ${FT_ERROR}"

	compile ${container_file} "STD_MODE" ${container_flag} ${std_executable_name}
	eval "./${std_executable_name} ${STD_OUTFILE} 2> ${STD_ERROR}"

	diff ${FT_OUTFILE} ${STD_OUTFILE} > ${DIFF_FILE}
	rm -f ${std_executable_name} ${ft_executable_name}
}

run_all () {
	eval "make benchmark"
	echo ""
	eval "./ft_containers ${FT_OUTFILE} 2> ${FT_ERROR}"
	eval "./std_containers ${STD_OUTFILE} 2> ${STD_ERROR}"
	diff ${FT_OUTFILE} ${STD_OUTFILE} > ${DIFF_FILE}
}

clean () {
	rm ${FT_OUTFILE} ${FT_ERROR} ${STD_OUTFILE} ${STD_ERROR} ${DIFF_FILE}
}

if [[ $# -eq 0 ]]; then
	run_all
else
	case $1 in
		vector) run_one "vector";;
		stack) run_one "stack";;
		map) run_one "map";;
		set) run_one "set";;
		all) run_all;;
		clean) clean;;
		*) printf "${RED}error\n${YELLOW}unknown option: ${RESET}$1\n"
			printf "options are: vector, stack, map, set, all and clean\n";;
	esac
fi
