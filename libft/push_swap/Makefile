# -*- Makefile -*-

# Target_name
NAME = push_swap
# Compiler
CC = cc
# Library_paths
LIBFT_PATH := ../
# Header_path
DOT_H_PATH := $(LIBFT_PATH)/includes
# Compilation_flags
FLAGS = -g -ggdb -pedantic -Wall -Wextra -Werror -I$(DOT_H_PATH)
# Library_files
LIBFT := $(LIBFT_PATH)/libft.a
# Source_files
SRCS = calculate_moves.c free_exit_error.c full_sorter.c in_parsing.c \
	inside_lis.c lis.c list_elements.c list.c main.c move_costs.c \
	node_target.c parser.c push_moves.c rev_rot_moves.c \
	rotate_moves.c sorter.c swap_moves.c \


# Main_target
$(NAME) : $(LIBFT) $(SRCS)
	echo
	echo "${BOLD}${GREEN}Compiling and linking ${NAME}...${NO_COLOR}"
	$(CC) $(FLAGS) $(SRCS) $(LIBFT) -o $(NAME)
	echo
	echo "${BOLD}${GREEN}Created  -> ${RED}$(NAME)${NO_COLOR}"
# Building_Libft_library
$(LIBFT) :
	make -s -C $(LIBFT_PATH) all
# Building_all
all : $(NAME)
# Cleaning and rebuilding
re : fclean all
# Cleaning
clean:
	if [ -n "$$(find . -name '*.o')" ]; then \
		rm -f *.o; \
	echo; \
	echo "${BOLD}${YELLOW}Cleaning ${BLUE}$(NAME)${BOLD}${YELLOW} object files...${NO_COLOR}"; \
	fi
# Full_cleaning
fclean: clean
	if [ -e $(NAME) ]; then \
		rm -f $(NAME); \
		echo; \
		echo "${BOLD}${YELLOW}Successfully removed builds for ${BLUE}$(NAME)${NO_COLOR}"; \
	fi
# Declaration of phony targets
.PHONY: all clean fclean re
# Silence all commands
.SILENT:
# Color codes
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
NO_COLOR = \033[0m
BOLD = \033[1m
# End of Makefile
