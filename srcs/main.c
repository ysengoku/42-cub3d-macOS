/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 08:09:57 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/05 16:08:16 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_player(t_player *player)
{
	player->fov = FOV * M_PI / 180;
	player->pos_x = 0;
	player->pos_y = 0;
	player->dir = 0.0;
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_length = tan(player->fov / 2);
	player->plane_x = 0;
	player->plane_y = 0;
	player->moved = 1;
}

static void init_cub3d_data(t_cub3d *data)
{
	int	i;

	i = -1;
	data->mlx_ptr = 0;
	data->win_ptr = 0;
 	ft_memset(&data->img, 0, sizeof(data->img));
	init_player(&data->player);
	data->ceiling_color = 0;
	data->floor_color = 0;
	ft_memset(&data->mmap, 0, sizeof(data->mmap));
	ft_memset(&data->mmap.img, 0, sizeof(data->mmap.img));
	//------ if we use texture for minimap ----------------------
	ft_memset(&data->mmap.floor, 0, sizeof(data->mmap.floor)); 
	ft_memset(&data->mmap.wall, 0, sizeof(data->mmap.wall));
	ft_memset(&data->mmap.player, 0, sizeof(data->mmap.player));
	//-----------------------------------------------------------
	data->key_pressed_left = 0;
	data->key_pressed_right = 0;
	data->key_pressed_w = 0;
	data->key_pressed_s = 0;
	data->key_pressed_a = 0;
	data->key_pressed_d = 0;
}

static int	ft_init_mlx(t_cub3d *data)
{
	data->mlx_ptr = mlx_init();
	if (!(data->mlx_ptr))
	{
		ft_putendl_fd("MLX: Initialization failed", 2);
		free_data_map(&data->map);
		return (1);
	}
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_W, WIN_H, WINNAME);
	if (!(data->win_ptr))
	{
		perror("MLX");
		free(data->mlx_ptr);
		free_data_map(&data->map);
		return (1);
	}
	return (0);
}

static int	create_main_image(t_cub3d *data)
{
	data->img.img = mlx_new_image(data->mlx_ptr, WIN_W, WIN_H);
	if (data->img.img == NULL)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		free(data->mlx_ptr);
		free_data_map(&data->map);
		return (1);
	}
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pxl,
			&data->img.line_len, &data->img.endian);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub3d	data;
	
	if (argc != 2 || ft_strnstr_r(argv[1], ".cub") != 0)
		ft_error_exit("Usage: ./cub3D <path/map_name.cub>", 1);
	if (parsing(argv[1], &data) == 1)
		return (2);
	init_cub3d_data(&data);
	set_data(&data, &data.player, &data.map);
	if (ft_init_mlx(&data) == 1)
		return(1);
	if (create_main_image(&data) == 1)
		return (1);
	if (set_wall_texture(&data, data.wall) == 1)
		return (1);
	if (create_minimap_img(&data, &data.mmap) == 1)
		return (1);
	mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, handle_closebutton, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, handle_keypress, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, handle_keyrelease, &data);
	// mlx_mouse_hook(data.win_ptr, &handle_mouseevents, &data); // ---> Doesn't need ??
	mlx_loop_hook(data.mlx_ptr, game_loop, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
