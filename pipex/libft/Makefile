# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/14 17:45:24 by ssadi-ou          #+#    #+#              #
#    Updated: 2025/04/02 01:07:29 by ssadi-ou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBC =	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
		ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c \
		ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c \
		ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c \
		ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c 

ADDITIONAL =	ft_itoa.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
				ft_split.c ft_strjoin.c ft_strmapi.c ft_strtrim.c ft_substr.c ft_striteri.c

BONUS =	ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstmap_bonus.c\
		 ft_lstlast_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c\
		 ft_lstnew_bonus.c ft_lstsize_bonus.c ft_lstdelone_bonus.c\

SRCS = ${LIBC} ${ADDITIONAL}

SRCSALL = ${LIBC} ${ADDITIONAL} ${BONUS}

OBJS = ${SRCS:.c=.o}

OBJSALL = ${SRCSALL:.c=.o} 

LIB = libft.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra -I ./

%.o: %.c libft.h
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${LIB}:	${OBJS}
		ar -rsc ${LIB} ${OBJS}

bonus:	${OBJSALL}
		ar -rsc ${LIB} $^

all: 	${LIB}

clean:	
		rm -f ${OBJSALL}

fclean:	clean;
		rm -f ${LIB}

re:	fclean all

so:
	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRCSALL)
	gcc -nostartfiles -shared -o libft.so $(OBJSALL)

.PHONY: all clean fclean re bonus
