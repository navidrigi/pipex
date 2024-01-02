NAME	=	pipex
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
SRC		=	main.c utils_1.c ft_split.c utils_3.c utils_2.c cleanup.c \
			ft_putstr_fd.c utils_4.c utils_5.c
OBJ		=	$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) output

re: fclean all
