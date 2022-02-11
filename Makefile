# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/06 15:15:49 by skienzle          #+#    #+#              #
#    Updated: 2022/02/11 16:37:13 by skienzle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_containers
CC = clang++
CFLAGS = -Wall -Wextra -Werror -std=c++98
RM = rm -rf

INC = vector.hpp map.hpp stack.hpp set.hpp iterator.hpp \
	utility.hpp type_traits.hpp algorithm.hpp RBtree.hpp
IDIR = inc
INC_FULL = $(addprefix $(IDIR)/, $(INC))

IPP = vector.ipp
IPP_FULL = $(addprefix $(IDIR)/, $(IPP))

SRC = main.cpp
SDIR = src
SRC_FULL = $(addprefix $(SDIR)/, $(SRC))

ODIR = obj
OBJ = $(patsubst $(SDIR)/%.c, $(ODIR)/%.o, $(SRC_FULL))

$(NAME): $(ODIR) $(OBJ) $(INC_FULL) $(IPP_FULL)
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

.PHONY: all clean fclean re bonus