# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/29 10:53:22 by saharchi          #+#    #+#              #
#    Updated: 2024/07/13 14:54:48 by saharchi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

NAMEB = philo_bonus

CFLAGS =  -Wall -Wextra -Werror #-g -fsanitize=thread
RM = rm -f

SRC = mandatory/main.c mandatory/routine.c mandatory/init_function.c mandatory/eating.c

SRCB = bonus/main_bonus.c bonus/routine_bonus.c bonus/init_function_bonus.c bonus/eating_bonus.c

OBJM = $(SRC:%.c=%.o)

OBJB = $(SRCB:%.c=%.o)

all : $(NAME)

bonus/%.o : bonus/%.c bonus/philo_bonus.h
	cc $(CFLAGS) -c $< -o $@

mandatory/%.o : mandatory/%.c mandatory/philo.h
	cc $(CFLAGS) -c $< -o $@

bonus : $(OBJB)
	cc $(CFLAGS) $(OBJB) -o $(NAMEB)

$(NAME) : $(OBJM)
	cc $(CFLAGS) $(OBJM) -o $(NAME)

clean : 
	$(RM) $(OBJM) $(OBJB)

fclean : clean
	$(RM) $(NAME) $(NAMEB)
re : fclean all