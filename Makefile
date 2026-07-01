# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ffrattar <ffrattar@student.42firenze.it    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/26 10:52:26 by ffrattar          #+#    #+#              #
#    Updated: 2026/07/01 07:20:24 by ffrattar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Formatting
BOLD = \033[1m
DEF_COLOR = \033[0;39m
GREY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m
RESET_COLOR = \e[m

# Target
NAME := cub3D
# PROGRAM := cub3D

# Source Files (for archive file and main program)
SRC_DIR = src

SRCS = src/main.c src/parsing.c src/validate_config.c src/scene_parse.c \
	src/scene_parse2.c src/map_parse.c src/map_parse2.c src/build_map.c \
	src/validate_map.c src/validate_map2.c src/map_floodfill.c \
	src/floodfill_helper.c src/cleaner.c src/cleaner2.c src/errors.c \
	src/errors2.c src/init_mlx.c src/player_spawn.c src/hooks.c \
	src/renderer.c src/nav.c src/mini_map.c src/raycaster.c \

OFILES = $(SRCS:.c=.o)

# Dependency path info
LIBFT_PATH := ./libft
MLX_PATH := ./minilibx-linux
#MLX_PATH := ./minilibx
LIBFT := $(LIBFT_PATH)/libft.a
LIBMLX := $(MLX_PATH)/libmlx_Linux.a
DOT_H_PATH := include/cub3D.h
INC = -I./include
LIBINC = -I./libft/includes
MLXINC = -I./minilibx-linux
#MLXINC = -I./minilibx

# Compilation Config
CC = cc
CFLAGS = -Wall -Wextra -Werror -Wno-strict-prototypes $(INC) $(LIBINC) $(MLXINC)
DEBUGFLAGS = -g -ggdb -pedantic -g2
# Minilibx configs
MLX = -Lminilibx-linux $(LIBMLX) -lmlx -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -I/usr/include
# Minilibx repository URL
MLX_URL := https://github.com/42Paris/minilibx-linux.git

%.o: %.c
	$(CC) -c $(CFLAGS) $(DEBUGFLAGS)  $< -o $@

# Build Target
all: $(NAME)

$(NAME): $(LIBFT) $(LIBMLX) $(DOT_H_PATH) $(OFILES)

# Build main program file using library
	$(CC) $(CFLAGS) $(OFILES) $(LIBFT) $(MLX) -o $(NAME)
	echo "${GREEN}Created $(NAME) program ${RESET_COLOR}"

# Building_Libft_library
$(LIBFT): FORCE
	make --no-print-directory -C $(LIBFT_PATH) all

FORCE: # empty dependency to force make execution in all

# Building_Libmlx_library
$(LIBMLX):
	if [ ! -d $(MLX_PATH) ]; then \
		$(MAKE) --no-print-directory $(MLX_PATH); \
	fi
	@make --no-print-directory -s -C $(MLX_PATH) all > /dev/null 2>&1
	echo
	echo "${BOLD}${GREEN}Created library: $(RED)libmlx_Linux.a$(NO_COLOR)"
	echo
$(MLX_PATH):
	echo
	echo "${BOLD}${BLUE}Downloading Minilibx from ${YELLOW}$(MLX_URL)...${NO_COLOR}"
	git clone $(MLX_URL) $(MLX_PATH) -q

#run: all
#	./$(NAME)

# Show configuration options
show:
	@printf "NAME       : $(NAME)\n"
	@printf "CC         : $(CC)\n"
	@printf "SYSFLAG    : $(SYSFLAG)\n"
	@printf "CFLAGS     : $(CFLAGS)\n"
	@printf	"DOT_H_PATH : $(DOT_H_PATH)\n"
	@printf "SRCS       : $(SRCS)\n"
	@printf "OFILES     : $(OFILES)\n"
# Clean Operations
clean:
	if [ -n "$$(find $(LIBFT_PATH)/libft -name '*.o')" ]; then \
		make --no-print-directory -s -C $(LIBFT_PATH) clean; \
	fi
	if [ -n "$$(find $(SRC_DIR) -name '*.o')" ]; then \
		echo "${GREY}Removed all .o files for ${NAME} ${RESET_COLOR} "; \
	fi
	cd $(SRC_DIR)
	rm -f $(OFILES)

fclean: clean
	if [ -e $(LIBFT) ]; then \
		make --no-print-directory -s -C $(LIBFT_PATH) fclean; \
	fi
	if [ -e $(NAME) ]; then \
		rm -f $(NAME); \
		echo "${BOLD}${GREY}Removed $(NAME) ${RESET_COLOR}"; \
		echo "${RESET_COLOR}"; \
	fi
re: fclean all

.PHONY: all clean fclean re
	echo "${YELLOW} Mark all non-file targets ${RESET_COLOR}"

# Silence Commands
.SILENT:

# $(shell find $(SRC_DIR) -name '*.c')
