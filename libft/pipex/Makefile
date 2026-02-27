# -*- Makefile -*-

# Target_name
NAME = pipex
# Bonus_target
NAME_B = pipex_bonus
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
SRCS = main.c utils.c utils_one.c utils_bonus.c \

# Bonus_files
SRCS_BONUS = bonus.c utils.c utils_one.c utils_bonus.c \

# Main_target
$(NAME) : $(LIBFT) $(SRCS)
	echo "${BOLD}${GREEN}Compiling and linking ${NAME}...${NO_COLOR}"
	$(CC) $(FLAGS) $(SRCS) $(LIBFT) -o $(NAME)
	echo
	echo "${BOLD}${GREEN}Created  -> ${RED}$(NAME)${NO_COLOR}"
	echo
# Bonus_target
$(NAME_B) : $(LIBFT) $(SRCS_BONUS)
	echo "${BOLD}${GREEN}Compiling and linking ${NAME_B}...${NO_COLOR}"
	$(CC) $(FLAGS) $(SRCS_BONUS) $(LIBFT) -o $(NAME_B)
	echo
	echo "${BOLD}${GREEN}Created  -> ${RED}$(NAME_B)${NO_COLOR}"
# Building_Libft_library
$(LIBFT) :
	make -s -C $(LIBFT_PATH) all
# Building_all
all : $(NAME) $(NAME_B)
# Building_bonus
bonus : $(NAME_B)
# Cleaning and rebuilding
re : fclean all
# Cleaning
clean:
	if [ -n "$$(find . -name '*.o')" ]; then \
		rm -f *.o; \
	echo; \
	echo "${BOLD}${YELLOW}Cleaned pipex object files...${NO_COLOR}"; \
	fi
# Full_cleaning
fclean: clean
	if [ -e $(NAME) ]; then \
		rm -f $(NAME); \
		echo; \
		echo "${BOLD}${YELLOW}Successfully removed builds for ${BLUE}$(NAME)${NO_COLOR}"; \
	fi
	if [ -e $(NAME_B) ]; then \
		rm -f $(NAME_B); \
		echo; \
		echo "${BOLD}${YELLOW}Successfully removed builds for ${BLUE}$(NAME_B)${NO_COLOR}"; \
	fi
# Declaration of phony targets
.PHONY: all clean fclean re bonus
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
