NAME        = libpipex.a
SRC         = src/cmdexec.c \
              src/pipex.c \
              src/utils.c
OBJ         = $(SRC:.c=.o)
CC          = cc
CFLAGS      = -Wall -Werror -Wextra -g3

LIBFT_DIR   = libft
LIBFT_A     = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_A)
	ar rcs $@ $(OBJ) $(LIBFT_A)

%.o: %.c inc/pipex.h
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
