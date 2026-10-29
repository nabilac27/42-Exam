# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/08/14 20:12:08 by nchairun          #+#    #+#              #
#    Updated: 2026/08/14 20:13:22 by nchairun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= 	polyset

SRC 	= 	main.cpp \
			src/array_bag.cpp \
			src/tree_bag.cpp \
			src/searchable_array_bag.cpp \
			src/searchable_tree_bag.cpp \
			src/set.cpp

CC 		= c++
CFLAGS 	= -Wall -Wextra -Werror

$(NAME):
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re