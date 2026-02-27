SRCS = ft_printf.c ft_print_char.c ft_print_str.c ft_print_int.c \
	ft_print_uint.c ft_print_hex.c ft_print_adress.c \
	
OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

# Header files
PRINTF_H_PATHS = ../includes

NAME = libftprintf.a

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

all: $(NAME) 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(PRINTF_H_PATHS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
