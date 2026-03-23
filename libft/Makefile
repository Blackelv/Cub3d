# -*- Makefile -*-

# Target_name
NAME = libft.a
# Compiler
CC = cc
# Compilation_flags
FLAGS = -g -ggdb -pedantic -Wall -Wextra -Werror
# Header_paths
LIBFT_H_PATH = ./includes
# Library_paths
PRINTF_PATH := ./printf
PIPEX_PATH := ./pipex
# Library_files
PRINTF := $(PRINTF_PATH)/libftprintf.a
# Source_files
SRCS = ft_isalpha.c ft_toupper.c ft_tolower.c ft_isdigit.c ft_isalnum.c \
	ft_isascii.c ft_isprint.c ft_issign.c ft_isspace.c ft_strlen.c \
	ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c \
	ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c \
	ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c \
	ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
	ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c get_next_line.c get_next_line_utils.c \
	ft_trimendl.c \
# Bonus_files
BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
	ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c \
	get_next_line_bonus.c \
# Object_files
OBJS = $(SRCS:.c=.o)
# Bonus_object_files
OBJS_B = $(BONUS:.c=.o)
# Main_target
$(NAME): $(OBJS)
	echo "${BOLD}${GREEN}Compiling and linking ${NAME}...${NO_COLOR}"
	echo; \
	make -s -C $(PRINTF_PATH)
	cp $(PRINTF) $(NAME)
	ar rc $(NAME) $(OBJS)
	make all -s -C $(PIPEX_PATH)
	echo; \
	echo "${BOLD}${GREEN}Created -> ${RED}$(BOLD)$(NAME)${NO_COLOR}"
	echo
# Building_all
all: $(NAME) bonus
# Building_bonus
bonus: $(NAME) $(OBJS_B)
	@new_objs_b=$$(find . -name '*_bonus.o' -newer $(NAME)); \
	if [ -n "$$new_objs_b" ]; then \
		ar rc $(NAME) $(OBJS_B); \
		echo "${BOLD}${GREEN}Created bonus -> ${RED}$(BOLD)$(NAME)${NO_COLOR}"; \
		echo; \
	fi
# Building_object_files
%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@ -I$(LIBFT_H_PATH)
# Cleaning
clean:
	if [ -n "$$(find $(PRINTF_PATH) -name '*.o')" ]; then \
		make -s -C $(PRINTF_PATH) clean; \
		echo; \
		echo "${BOLD}${YELLOW}Cleaned printf object files ${NO_COLOR}"; \
	fi
	make -s -C $(PIPEX_PATH) clean; \
	if [ -n "$$(find . -name '*.o')" ]; then \
		rm -f $(OBJS) $(OBJS_B); \
		echo; \
		echo "${BOLD}${YELLOW}Cleaned libft object files ${NO_COLOR}"; \
	fi
# Full_cleaning
fclean: clean
	if [ -e $(PRINTF) ]; then \
		make -s -C $(PRINTF_PATH) fclean; \
		echo; \
		echo "${BOLD}${YELLOW}Cleaned -> ${BLUE}$(PRINTF)${NO_COLOR}"; \
	fi
	make -s -C $(PIPEX_PATH) fclean; \
	if [ -e $(NAME) ]; then \
		rm -f $(NAME); \
		echo; \
		echo "${BOLD}${YELLOW}Removed -> ${BLUE}$(NAME)${NO_COLOR}"; \
	fi
# Cleaning_and_rebuilding
re: fclean all
# Declaration_of_phony_targets
.PHONY: all bonus clean fclean re
# Silence_all_commands
.SILENT:
# Color_codes
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
NO_COLOR = \033[0m
BOLD = \033[1m

# -*- End of Makefile -*-
