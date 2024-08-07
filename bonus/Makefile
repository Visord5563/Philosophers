# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/29 10:53:22 by saharchi          #+#    #+#              #
#    Updated: 2024/08/07 14:55:27 by saharchi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

CFLAGS =  -Wall -Wextra -Werror 
RM = rm -f

SRC = main_bonus.c routine_bonus.c init_function_bonus.c eating_bonus.c

OBJM = $(SRC:%.c=%.o)

all : $(NAME)

%.o : %.c philo_bonus.h
	cc $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJM)
	cc $(CFLAGS) $(OBJM) -o $(NAME)

clean : 
	$(RM) $(OBJM)

fclean : clean
	$(RM) $(NAME)
re : fclean all