/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 08:09:57 by yusengok          #+#    #+#             */
/*   Updated: 2024/05/29 13:12:21 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_init_mlx(t_cub3d *data)
{
	data->mlx_ptr = mlx_init();
	if (!(data->mlx_ptr))
	{
		ft_putendl_fd("MLX: Initialization failed", 2);
		/*== For test =============================*/
		for (int i = 0; data->map.mapdata[i]; i++)
		free(data->map.mapdata[i]);
		free(data->map.mapdata);
		/*=========================================*/
		return (1);
	}
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_W, WIN_H, WINNAME);
	if (!(data->win_ptr))
	{
		perror("MLX");
		free(data->mlx_ptr);
		/*== For test =============================*/
		for (int i = 0; data->map.mapdata[i]; i++)
		free(data->map.mapdata[i]);
		free(data->map.mapdata);
		/*=========================================*/
		return (1);
	}

	return (0);
}

static void	init_player(t_player *player)
{
	player->fov = FOV * M_PI / 180;
	player->pos_x = 0; // will be set after parsing
	player->pos_y = 0; // will be set after parsing
	player->initial_dir = 0; // will be set after parsing
	player->dir = 0.0; // will be set after parsing
	player->dir_x = 0; // will be set in init_camera
	player->dir_y = 0; // will be set in init_camera
	player->plane_length = tan(player->fov / 2);
	player->plane_x = 0; // will be set in init_camera
	player->plane_y = 0; // will be set in init_camera
	player->moved = 1; // must be always initialized to 1 to show initial view
}

static void init_cub3d_data(t_cub3d *data)
{
	int	i;

	i = -1;
	//void		*mlx_ptr; ?
	//void		*win_ptr; ?
	ft_bzero(&data->img, sizeof(data->img));
	ft_bzero(&data->map, sizeof(data->map));
	init_player(&data->player);
	data->ceiling_color = DEFAULT_CEILING;
	data->floor_color = DEFAULT_FLOOR;
	while (++i < 4)
		ft_bzero(&data->textures[i], sizeof(data->textures[i]));
	ft_bzero(&data->mmap, sizeof(data->mmap));
	ft_bzero(&data->mmap.img, sizeof(data->mmap.img));
	ft_bzero(&data->mmap.floor, sizeof(data->mmap.floor)); // if we use texture for minimap
	ft_bzero(&data->mmap.wall, sizeof(data->mmap.wall)); // if we use texture for minimap
	ft_bzero(&data->mmap.player, sizeof(data->mmap.player)); // if we use texture for minimap
	data->key_pressed_left = 0;
	data->key_pressed_right = 0;
}

static void	set_player(t_player *player)
{
	player->pos_x = 8; // from map ---------> Need to change
	player->pos_y = 5; // from map ---------> Need to change
	player->initial_dir = N; // from map ---------> Need to change
	player->dir = (double)player->initial_dir;
}

/* temporary code */
static int	set_texture(t_cub3d *data, t_xpm_img textures[4])
{
	char	north[] = "./textures/test/north.xpm";
	char	south[] = "./textures/test/south.xpm";
	char	west[] = "./textures/test/west.xpm";
	char	east[] = "./textures/test/east.xpm";
	int		i;

	textures[NO].path = ft_strdup(north);
	textures[SO].path = ft_strdup(south);
	textures[WE].path = ft_strdup(west);
	textures[EA].path = ft_strdup(east);
	i = -1;
	while (++i < 4)
	{
		textures[i].img = mlx_xpm_file_to_image(data->mlx_ptr, textures[i].path,
			&textures[i].w, &textures[i].h);
		if (textures[i].img == NULL)
		{
			while (i > 0)
				mlx_destroy_image(data->mlx_ptr, textures[i--].img);
			while (i < 4)
				free(textures[i++].path);
			return (1);
		}
		textures[i].addr = mlx_get_data_addr(textures[i].img,
			&textures[i].bits_per_pxl, &textures[i].line_len,
			&textures[i].endian);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub3d	data;

/*=== TEST ===============================================================*/
	char test[26][24] = {
	{"111111111111111111111111"},
	{"100000000000000000000001"},
	{"100000000000000000000001"},
	{"100000000000000000000001"},
	{"100000000000000000000001"},
	{"10000000N000000000000001"},
	{"100000000000000000000001"},
	{"100000111110000101010001"},
	{"100000100010000000000001"},
	{"100000100010000100010001"},
	{"100000100010000000000001"},
	{"100000111100001010100001"},
	{"100000000000000000000001"},
	{"100000000000000000000001"},
	{"100000000000000000000001"},
	{"100000000000000000000001"},
 	{"100000000000000000000001"},
	{"100000000000000000000001"},
	{"100000000000000000000001"},
 	{"111111111000000000000001"},
	{"100100001000000000000001"},
	{"100000101000000000000001"},
	{"100100001000000000000001"},
	{"100111111000000000000001"},
	{"100000000000000000000001"},
	{"111111111111111111111111"}};
	data.colors[0] = 9852907;
	data.colors[1] = 16775920;
	data.colors[2] = 11393254;
	data.colors[3] = 9419927;
/*========================================================================*/

	if (argc != 2 || ft_strnstr_r(argv[1], ".cub") != 0)
		ft_error_exit("Usage: ./cub3D <path/map_name.cub>", 1);
	init_cub3d_data(&data);
	// parsing
	set_player(&data.player);
	/*=== TEST ===============================================================*/
	data.map.maxw = 24;
	data.map.maxh = 26;
	data.map.mapdata = ft_calloc(data.map.maxh + 1, sizeof(char*));
	for (int i = 0; i < data.map.maxh; i++)
		data.map.mapdata[i] = ft_strdup(test[i]);
	/*========================================================================*/
	if (ft_init_mlx(&data) == 1)
		return(1);
	data.img.img = mlx_new_image(data.mlx_ptr, WIN_W, WIN_H);
	if (data.img.img == NULL)
	{
		mlx_destroy_window(data.mlx_ptr, data.win_ptr);
		free(data.mlx_ptr);
		/*== For test =============================*/
		for (int i = 0; data.map.mapdata[i]; i++)
			free(data.map.mapdata[i]);
		free(data.map.mapdata);
		/*=========================================*/
		return (1);
	}
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bits_per_pxl,
			&data.img.line_len, &data.img.endian);
	if (set_texture(&data, data.textures) == 1)
	{
		mlx_destroy_image(data.mlx_ptr, data.img.img);
		mlx_destroy_window(data.mlx_ptr, data.win_ptr);
		free(data.mlx_ptr);
		//== For test =============================
		for (int i = 0; data.map.mapdata[i]; i++)
			free(data.map.mapdata[i]);
		free(data.map.mapdata);
		//=========================================
		return (1);
	}
	if (BONUS)
	{
		data.mmap.img.img = mlx_new_image(data.mlx_ptr,
				data.map.maxw * MMAP_SCALE, data.map.maxh * MMAP_SCALE);
		// NULL check
		data.mmap.img.addr = mlx_get_data_addr(data.mmap.img.img,
			&data.mmap.img.bits_per_pxl, &data.mmap.img.line_len,
			&data.mmap.img.endian);
	}
	/*=== TEST ===============================================================*/
	if (BONUS)
	{
		data.mmap.floor.img = mlx_xpm_file_to_image(data.mlx_ptr, MMAP_F,
				&data.mmap.floor.w, &data.mmap.floor.h);
		data.mmap.floor.addr = mlx_get_data_addr(data.mmap.floor.img,
				&data.mmap.floor.bits_per_pxl, &data.mmap.floor.line_len,
				&data.mmap.floor.endian);
		data.mmap.player.img = mlx_xpm_file_to_image(data.mlx_ptr, MMAP_PL,
				&data.mmap.player.w, &data.mmap.player.h);
		data.mmap.player.addr = mlx_get_data_addr(data.mmap.player.img,
				&data.mmap.player.bits_per_pxl, &data.mmap.player.line_len,
				&data.mmap.player.endian);
		data.mmap.wall.img = mlx_xpm_file_to_image(data.mlx_ptr, MMAP_WL,
				&data.mmap.wall.w, &data.mmap.wall.h);
		data.mmap.wall.addr = mlx_get_data_addr(data.mmap.wall.img,
				&data.mmap.wall.bits_per_pxl, &data.mmap.wall.line_len,
				&data.mmap.wall.endian);
	}
	/*========================================================================*/
	mlx_key_hook(data.win_ptr, handle_keyevents, &data);
	mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, handle_closebutton, &data);
//	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, handle_keypress, &data);
//	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, handle_keyrelease, &data);
	// mlx_mouse_hook(data.win_ptr, &handle_mouseevents, &data); // ---> Doesn't need ??
	mlx_loop_hook(data.mlx_ptr, game_loop, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
