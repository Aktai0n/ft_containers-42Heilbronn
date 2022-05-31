#!/bin/bash

make bonus
./ft_containers ft_output 2> ft_error
./std_containers std_output 2> std_error
# diff ft_output std_output
# rm ft_output std_output