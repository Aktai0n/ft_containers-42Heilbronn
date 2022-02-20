# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/06 15:15:49 by skienzle          #+#    #+#              #
#    Updated: 2022/02/20 21:03:02 by skienzle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_containers
CC = clang++
CFLAGS = -Wall -Wextra -Werror -std=c++98
RM = rm -rf

STD_NAME = std_containers

INC = vector.hpp map.hpp stack.hpp set.hpp utils/iterator.hpp \
	utils/utility.hpp utils/type_traits.hpp utils/algorithm.hpp utils/RBtree.hpp
IDIR = inc
INC_FULL = $(addprefix $(IDIR)/, $(INC))

TPP = vector.tpp stack.tpp map.tpp set.tpp utils/RBtree.tpp
TPP_FULL = $(addprefix $(IDIR)/, $(TPP))

SRC = main.cpp
SDIR = src
SRC_FULL = $(addprefix $(SDIR)/, $(SRC))

ODIR = obj
OBJ = $(patsubst $(SDIR)/%.cpp, $(ODIR)/%.o, $(SRC_FULL))

STD_ODIR = std_obj
STD_OBJ = $(patsubst $(SDIR)/%.cpp, $(STD_ODIR)/%.o, $(SRC_FULL))


all: $(NAME) $(STD_NAME)

$(NAME): $(ODIR) $(OBJ) $(INC_FULL) $(TPP_FULL)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(STD_NAME): CFLAGS += -DMODE_STD=1
$(STD_NAME): $(STD_ODIR) $(STD_OBJ)
	$(CC) $(CFLAGS) $(STD_OBJ) -o $(STD_NAME)

$(ODIR):
	@mkdir -p $@

$(STD_ODIR):
	@mkdir -p $@

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(STD_ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(ODIR)
	$(RM) $(STD_ODIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(STD_NAME)

re: fclean all

bonus: all

debug: CFLAGS += -g
debug: re

release: CFLAGS += -Ofast
release: re

.PHONY: all clean fclean re bonus debug release