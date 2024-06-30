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

NAME = cub3D
NAME_B = cub3D_bonus


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
		$(SRCS_DIR_B)door_bonus	\
		$(SRCS_DIR_B)treasure_bonus	\
		$(SRCS_DIR_B)draw_bonus	\
		
FILES = main	\
		parsing \
		get_file \
		get_data \
		get_sprites_path \
		get_color_rgb \
		get_maps \
		check_map \
		check_file	\
		apply_flood_fill	\
		fl_iteratif	\
		fl_recursive	\
		handle_errors	\
		set_data	\
		game_loop	\
		draw	\
		colors	\
		rendering	\
		raycasting	\
		check_hit	\
		event_handler	\
		move	\
		rotate	\
		quit	\
		error_handling	\
		ft_free	\
		minimap_bonus	\
		minimap_img_bonus	\
		minimap_utils_bonus	\
		event_bonus	\
		door_bonus	\
		treasure_bonus	\
		set_treasure_data_bonus	\
		draw_cf_bonus

SRCS = $(addsuffix .c, $(FILES))
OBJS_DIR = .objs/
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))
OBJS_DIR_B = .objs_bonus/
OBJS_B = $(addprefix $(OBJS_DIR_B), $(addsuffix .o, $(FILES)))

INCLUDE = includes
HEADERS_DIR = includes/
HEADER_FILES = cub3d.h
HEADERS = $(addprefix $(HEADERS_DIR), $(HEADER_FILES))

LIB_DIR = ./lib
LIBFT_DIR = $(LIB_DIR)/libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBMLX_DIR = $(LIB_DIR)/mlx_macos
LIBMLX = $(LIBMLX_DIR)/libmlx.a

CC = cc
CCFLAGS = -Wextra -Wall -Werror 
#-fsanitize=address
INCLUDE = -I$(HEADERS_DIR) -I$(LIBFT_DIR) -I$(LIBMLX_DIR)
MLXFLAGS = -lft -lmlx -framework OpenGL -framework AppKit
RM = rm -f

all: lib
	@$(MAKE) $(NAME)

$(NAME): $(OBJS)
	@printf "$(CYAN)Building cub3D...\n$(RESET)"
	$(CC) $(CCFLAGS) -DBONUS=0 $^ -L$(LIBMLX_DIR) -L$(LIBFT_DIR) $(MLXFLAGS) -o $(NAME)
	@printf "$(LIGHT_GREEN)$(BOLD)cub3D is ready to launch\n$(RESET)"

$(OBJS_DIR)%.o: %.c $(HEADERS) $(LIBFT) Makefile
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE) -DBONUS=0

$(NAME_B): $(OBJS_B) $(HEADER) $(LIBFT) $(LIBMLX)
	@printf "$(CYAN)$(BOLD)Building cub3D_bonus...\n$(RESET)"
	$(CC) $(CCFLAGS) -DBONUS=1 $^ -L$(LIBMLX_DIR) -L$(LIBFT_DIR) $(MLXFLAGS) -o $(NAME_B)
	@printf "$(LIGHT_GREEN)$(BOLD)cub3D_bonus is ready to launch\n$(RESET)"

$(OBJS_DIR_B)%.o: %.c $(HEADERS) $(LIBFT) Makefile
	@mkdir -p $(OBJS_DIR_B)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE) -DBONUS=1

lib: $(FORCE)
	@printf "$(BLUE)$(BOLD)Compiling Libft...\n$(RESET)"
	@$(MAKE) -s -C $(LIBFT_DIR)
	@printf "$(BLUE)$(BOLD)Compiling Minilibx...\n$(RESET)"
	@$(MAKE) -s -C $(LIBMLX_DIR)

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
	@$(RM) $(NAME_B)

re: fclean all

bonus: lib $(NAME_B)
	$(MAKE) $(NAME_B)

FORCE:

.PHONY: all lib clean fclean re bonus FORCE