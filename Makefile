# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/23 08:07:54 by yusengok          #+#    #+#              #
#    Updated: 2024/06/05 16:20:30 by yusengok         ###   ########.fr        #
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
#-fsanitize=address
MLXFLAGS = -lft -lmlx -framework OpenGL -framework AppKit
RM = rm -f

SRCS_DIR = srcs/
SRCS_DIR_B = srcs_bonus/

vpath %c $(SRCS_DIR) \
		$(SRCS_DIR)parsing \
		$(SRCS_DIR)rendering \
		$(SRCS_DIR)event \
		$(SRCS_DIR)error	\
		$(SRCS_DIR_B)	\
		$(SRCS_DIR_B)minimap	\
		$(SRCS_DIR_B)event_bonus	\
		$(SRCS_DIR_B)sprite	\
		$(SRCS_DIR_B)door_bonus	\
		
FILES = main	\
		parsing \
		get_file \
		get_data \
		get_sprites_path \
		get_color_rgb \
		get_maps \
		check_map \
		algo_flood_fill \
		handle_errors	\
		set_data	\
		game_loop	\
		draw	\
		colors	\
		raycasting	\
		check_wall_hit	\
		event_handler	\
		move	\
		rotate	\
		quit	\
		error_handling	\
		ft_free	\
		minimap_bonus	\
		minimap_img_bonus	\
		mouse_move_bonus	\
		sprite_bonus	\
		set_sprite_data_bonus	\
		door_bonus	\
		door_parsing_bonus

SRCS = $(addsuffix .c, $(FILES))
OBJS_DIR = .objs/
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))

LIB_DIR = lib/
LIBFT_DIR = $(LIB_DIR)libft/
LIBMLX_DIR = $(LIB_DIR)mlx_macos/

BONUS = 0

all: $(NAME)

$(NAME): $(OBJS)
	@printf "$(CYAN)Compiling Minilibx...\n$(RESET)"
	@$(MAKE) -C $(LIBMLX_DIR)
	@printf "$(CYAN)Compiling Libft...\n$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)
	@printf "$(CYAN)Building cub3D...\n$(RESET)"
	$(CC) $(CCFLAGS) -DBONUS=$(BONUS) $^ -L$(LIBMLX_DIR) -L$(LIBFT_DIR) $(MLXFLAGS) -o $(NAME)
	@printf "$(LIGHT_GREEN)$(BOLD)cub3D is ready to launch\n$(RESET)"

$(OBJS_DIR)%.o: %.c Makefile
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -DBONUS=$(BONUS) -I$(LIBFT_DIR) -I$(LIBMLX_DIR) -I$(INCLUDE) -c $< -o $@

clean:
	@printf "$(WHITE)Cleaning Minilibx...\n$(RESET)"
	@$(MAKE) clean -C $(LIBMLX_DIR)
	@printf "$(WHITE)Cleaning Libft...\n$(RESET)"
	@$(MAKE) clean -C $(LIBFT_DIR)
	@printf "$(WHITE)Cleaning cub3D...\n$(RESET)"
	@$(RM) -r $(OBJS_DIR)

fclean: clean
	@$(MAKE) fclean -C $(LIBMLX_DIR)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)

bonus: lib
	@$(RM) -r $(OBJS_DIR)
	@$(RM) $(NAME)
	$(MAKE) all BONUS=1

lib:
	@$(MAKE) -s -C $(LIBMLX_DIR)
	@$(MAKE) -s -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean bonus lib re
