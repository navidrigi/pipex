NAME	=	pipex
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
SRC		=	main.c utils_1.c ft_split.c utils_3.c utils_2.c cleanup.c \
			ft_putstr_fd.c utils_4.c utils_5.c
OBDDIR	=	obj
OBJ		=	$(addprefix $(OBDDIR)/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBDDIR):
	mkdir -p $(OBDDIR)

$(OBDDIR)/%.o: %.c | $(OBDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re $(OBDDIR)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) output
	rm -rf $(OBDDIR)

re: fclean all
