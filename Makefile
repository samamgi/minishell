# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aymen <aymen@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/10 00:00:00 by ssadi-ou          #+#    #+#              #
#    Updated: 2026/03/05 20:30:25 by aymen            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT_DIR = libft
FT_PRINTF_DIR = ft_printf
PIPEX_DIR = pipex/src
SYNTAX_DIR = syntax_checker
TOKENIZER_DIR = tokenizer
PARSER_DIR = parser_tokenizer
BUILTIN_DIR = builtin

LIBFT = $(LIBFT_DIR)/libft.a
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a

SRCS =	minishell.c \
		env_list.c \
		shell_utils.c \
        expand.c \
		expand_utils.c \
        heredoc.c \
        heredoc_child.c \
		signal.c \
        signal_heredoc.c \
		$(PIPEX_DIR)/pipex.c \
		$(PIPEX_DIR)/pipex_util.c \
		$(PIPEX_DIR)/pipex_util2.c \
        $(PIPEX_DIR)/cmdexec.c \
        $(PIPEX_DIR)/utils.c \
        $(SYNTAX_DIR)/syntax_checker.c \
        $(SYNTAX_DIR)/checkers/check_pipe.c \
        $(SYNTAX_DIR)/checkers/check_cote.c \
        $(SYNTAX_DIR)/checkers/check_chevron.c \
        $(SYNTAX_DIR)/check_else/check_else.c \
        $(TOKENIZER_DIR)/tokenizer.c \
        $(TOKENIZER_DIR)/token_utils.c \
        $(TOKENIZER_DIR)/sets/sets1.c \
        $(TOKENIZER_DIR)/sets/sets2.c \
		$(PARSER_DIR)/parser_tokenizer.c \
        $(PARSER_DIR)/utils/utils.c \
        $(PARSER_DIR)/utils/sets.c \
        $(PARSER_DIR)/utils/else.c \
        $(BUILTIN_DIR)/builtin.c \
        $(BUILTIN_DIR)/ft_cd.c \
        $(BUILTIN_DIR)/ft_echo.c \
        $(BUILTIN_DIR)/ft_exit.c \
        $(BUILTIN_DIR)/ft_env.c \
        $(BUILTIN_DIR)/ft_export.c \
        $(BUILTIN_DIR)/ft_pwd.c \
        $(BUILTIN_DIR)/ft_unset.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline
INCLUDES = -I. -I$(LIBFT_DIR) -I$(FT_PRINTF_DIR) -I$(PIPEX_DIR)/../inc

all: $(NAME)

$(NAME): $(LIBFT) $(FT_PRINTF) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(FT_PRINTF) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR) bonus

$(FT_PRINTF):
	@make -C $(FT_PRINTF_DIR)

%.o: %.c minishell.h
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@make -C $(FT_PRINTF_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@make -C $(FT_PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re valgrind bonus
