# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/10 00:00:00 by ssadi-ou          #+#    #+#              #
#    Updated: 2026/02/10 23:35:18 by ssadi-ou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

# Directories
LIBFT_DIR = libft
FT_PRINTF_DIR = ft_printf
PIPEX_DIR = pipex/src
SYNTAX_DIR = syntax_checker
TOKENIZER_DIR = tokenizer
PARSER_DIR = parser_tokenizer

# Libraries
LIBFT = $(LIBFT_DIR)/libft.a
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a

# Source files
SRCS =	minishell.c \
        expand.c \
        heredoc.c \
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
        $(PARSER_DIR)/utils/else.c

OBJS = $(SRCS:.c=.o)

# Compilation flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline
INCLUDES = -I. -I$(LIBFT_DIR) -I$(FT_PRINTF_DIR) -I$(PIPEX_DIR)/../inc

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

# Rules
all: $(NAME)

$(NAME): $(LIBFT) $(FT_PRINTF) $(OBJS)
	@echo "$(GREEN)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(FT_PRINTF) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled successfully!$(RESET)"

$(LIBFT):
	@echo "$(GREEN)Compiling libft...$(RESET)"
	@make -C $(LIBFT_DIR) bonus

$(FT_PRINTF):
	@echo "$(GREEN)Compiling ft_printf...$(RESET)"
	@make -C $(FT_PRINTF_DIR)

%.o: %.c minishell.h
	@echo "$(GREEN)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@make -C $(FT_PRINTF_DIR) clean
	@echo "$(GREEN)Clean done!$(RESET)"

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@make -C $(FT_PRINTF_DIR) fclean
	@echo "$(GREEN)Full clean done!$(RESET)"

re: fclean all

# Valgrind test
valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.sup ./$(NAME)

# Bonus (if needed)
bonus: all

.PHONY: all clean fclean re valgrind bonus
