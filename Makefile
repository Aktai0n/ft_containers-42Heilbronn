# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/06 15:15:49 by skienzle          #+#    #+#              #
#    Updated: 2022/02/20 17:01:12 by skienzle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_containers
CC = clang++
CFLAGS = -Wall -Wextra -Werror -std=c++98
RM = rm -rf


INC = vector.hpp map.hpp stack.hpp set.hpp utils/iterator.hpp \
	utils/utility.hpp utils/type_traits.hpp utils/algorithm.hpp utils/RBtree.hpp
IDIR = inc
INC_FULL = $(addprefix $(IDIR)/, $(INC))

TPP = vector.tpp stack.tpp map.tpp set.tpp utils/RBtree.tpp
TPP_FULL = $(addprefix $(IDIR)/, $(IPP))

SRC = main.cpp
SDIR = src
SRC_FULL = $(addprefix $(SDIR)/, $(SRC))


ODIR = obj
OBJ = $(patsubst $(SDIR)/%.c, $(ODIR)/%.o, $(SRC_FULL))

$(NAME): $(ODIR) $(OBJ) $(INC_FULL) $(TPP_FULL)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(ODIR):
	@mkdir -p $@

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	$(RM) $(ODIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

bonus: all

debug: CFLAGS += -g
debug: re

release: CFLAGS += -Ofast
release: re

.PHONY: all clean fclean re bonus debug release