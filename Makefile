# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/29 10:53:22 by saharchi          #+#    #+#              #
#    Updated: 2024/05/20 18:37:03 by saharchi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRC = main.c

OBJM = $(SRC:%.c=%.o)

$(NAME) : $(OBJM)
	cc $(CFLAGS) $(OBJM) -o $(NAME)

all : $(NAME)

%.o : %.c philo.h
	cc $(CFLAGS) -c $< -o $@

clean : 
	$(RM) $(OBJM)

fclean : clean
	$(RM) $(NAME)
re : fclean all