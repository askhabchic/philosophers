# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fhyman <fhyman@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/16 20:47:20 by fhyman            #+#    #+#              #
#    Updated: 2021/07/26 21:26:19 by fhyman           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

HEAD = *.h

INPUT = $(wildcard ./*.c)

FLAGS = -Wall -Wextra -Werror

PTHFLAG = -lpthread

RM = rm -f

OBJS = $(INPUT:.c=.o)

NORM =norminette *.[h] ./*.[c]

all: $(NAME)

$(NAME): $(OBJS)
		gcc -g $(OBJS) $(FLAGS) $(PTHFLAG) -o $(NAME) 
		
%.o: %.c %.h
		gcc -g $(FLAGS) $(PTHFLAG) -c $< -o $(<:.c=.o)
clean:
		@$(RM) $(OBJS)
fclean:	clean
		@$(RM) $(NAME)
re:		fclean all
.PHONY:	all clean fclean re
