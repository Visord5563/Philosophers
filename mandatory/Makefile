# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/29 10:53:22 by saharchi          #+#    #+#              #
#    Updated: 2024/08/07 14:53:42 by saharchi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CFLAGS =  -Wall -Wextra -Werror 
RM = rm -f

SRC = main.c routine.c init_function.c eating.c

OBJM = $(SRC:%.c=%.o)


all : $(NAME)

%.o : %.c philo.h
	cc $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJM)
	cc $(CFLAGS) $(OBJM) -o $(NAME)

clean : 
	$(RM) $(OBJM)

fclean : clean
	$(RM) $(NAME) 
re : fclean all