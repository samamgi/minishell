# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/04 11:05:32 by ssadi-ou          #+#    #+#              #
#    Updated: 2024/12/05 10:35:21 by ssadi-ou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_printf.c ft_printf_else.c ft_printf_hex.c ft_printf_nbr.c

OBJS = ${SRCS:.c=.o}

NAME = libftprintf.a

CFLAGS = -Wall -Wextra -Werror

all: ${NAME}

${NAME}: ${OBJS}
	ar rcs ${NAME} ${OBJS}
%.o:%.c ft_printf.h
	gcc ${CFLAGS} -c $< -o $@
clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
