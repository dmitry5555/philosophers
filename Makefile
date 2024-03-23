# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlariono <dlariono@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/06 13:41:01 by dlariono          #+#    #+#              #
#    Updated: 2023/08/08 16:43:26 by dlariono         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = @gcc
RM = @rm -f
FLAGS = -Wall -Wextra -Werror -g #-fsanitize=address

SRC = $(shell find src -name '*.c')
INC = ./inc/philo.h

OBJ = ${SRC:.c=.o}

$(NAME):	$(OBJ)
			$(CC) $(FLAGS) $(OBJ) -o $(NAME)
			@echo "${NAME} ✔️"
			@echo "mandatory files compiled successfully ✔️"

%.o:	%.c $(INC)
	$(CC) $(FLAGS) -c $< -o $@

all:	$(NAME)

clean:
	${RM} ${OBJ}

fclean:	clean
	${RM} ${NAME}

re:	clean all

.PHONY: all clean fclean re