# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/23 08:07:54 by yusengok          #+#    #+#              #
#    Updated: 2024/05/28 08:57:43 by yusengok         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BOLD = \033[1m
RESET = \033[0m
LIGHT_GREEN = \033[32m
BLUE = \033[34m
CYAN = \033[36m
WHITE = \033[37m

NAME = cub3D
INCLUDE = includes
CC = cc
CCFLAGS = -Wextra -Wall -Werror
MLXFLAGS = -lft -lmlx -framework OpenGL -framework AppKit
RM = rm -f

vpath %c srcs \
		srcs/parsing \
		srcs/raycasting	\
		srcs/rendering \
		srcs/event \
		srcs/error	\
		srcs/minimap
FILES = main	\
		raycasting	\
		img_rendering	\
		draw	\
		colors	\
		event_handler	\
		move	\
		move_utils	\
		rotate	\
		error_handling	\
		minimap #bonus

SRCS = $(addsuffix .c, $(FILES))
OBJS_DIR = .objs/
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))

LIB_DIR = lib/
LIBFT_DIR = $(LIB_DIR)libft/
LIBMLX_DIR = $(LIB_DIR)mlx_macos/

all: $(NAME)

$(NAME): $(OBJS)
	@printf "$(CYAN)Compiling Minilibx...\n$(RESET)"
	@$(MAKE) -C $(LIBMLX_DIR)
	@printf "$(CYAN)Compiling Libft...\n$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)
	@printf "$(CYAN)Building cub3D...\n$(RESET)"
	$(CC) $(CCFLAGS) $^ -L$(LIBMLX_DIR) -L$(LIBFT_DIR) $(MLXFLAGS) -o $(NAME)
	@printf "$(LIGHT_GREEN)$(BOLD)cub3D is ready to launch\n$(RESET)"

$(OBJS_DIR)%.o: %.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS)  -I$(LIBFT_DIR) -I$(LIBMLX_DIR) -I$(INCLUDE) -c $< -o $@

clean:
	@printf "$(WHITE)Cleaning Minilibx...\n$(RESET)"
	@$(MAKE) clean -C $(LIBMLX_DIR)
	@printf "$(WHITE)Cleaning Libft...\n$(RESET)"
	@$(MAKE) clean -C $(LIBFT_DIR)
	@printf "$(WHITE)Cleaning cub3D...\n$(RESET)"
	@$(RM) -r $(OBJ_DIR)

fclean: clean
	@$(MAKE) fclean -C $(LIBMLX_DIR)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)

lib:
	@$(MAKE) -s -C $(LIBMLX_DIR)
	@$(MAKE) -s -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re lib
