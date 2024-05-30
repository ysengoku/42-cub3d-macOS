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

/*== TEST MAP ================================================================*/
char test[26][26] = {
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
/*============================================================================*/

static int	ft_init_mlx(t_cub3d *data)
{
	data->mlx_ptr = mlx_init();
	if (!(data->mlx_ptr))
	{
		ft_putendl_fd("MLX: Initialization failed", 2);
		return (1);
	}
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_W, WIN_H, WINNAME);
	if (!(data->win_ptr))
	{
		perror("MLX");
		free(data->mlx_ptr);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub3d	data;

/*=== TEST ===============================================================*/
	data.ceiling.r = 169;
	data.ceiling.g = 169;
	data.ceiling.b = 169;
	data.ceiling_color = convert_color(data.ceiling);
	data.floor.r = 52;
	data.floor.g = 52;
	data.floor.b = 52;
	data.floor_color = convert_color(data.floor);
	data.colors[0] = 9852907;
	data.colors[1] = 16775920;
	data.colors[2] = 11393254;
	data.colors[3] = 9419927;

	data.player.pos_x = 8; //* TEXTURE_SIZE + TEXTURE_SIZE / 2;
	data.player.pos_y = 5; //* TEXTURE_SIZE + TEXTURE_SIZE / 2;
	data.player.dir = N;
	data.player.fov = FOV * M_PI / 180;
	data.player.plane_length = tan(data.player.fov / 2);
	data.player.moved = 1;
/*========================================================================*/

	if (argc != 2 || ft_strnstr_r(argv[1], ".cub") != 0)
		ft_error_exit("Usage: ./cub3D <path/map_name.cub>", 1);
	// map parsing
	if (ft_init_mlx(&data) == 1)
		exit(1);
	data.img.img = mlx_new_image(data.mlx_ptr, WIN_W, WIN_H);
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bits_per_pxl,
			&data.img.line_len, &data.img.endian);
	data.mmap.img.img = mlx_new_image(data.mlx_ptr, MMAP_H, MMAP_H);
	data.mmap.img.addr = mlx_get_data_addr(data.mmap.img.img,
		&data.mmap.img.bits_per_pxl, &data.mmap.img.line_len,
		&data.mmap.img.endian);
	mlx_key_hook(data.win_ptr, &handle_keyevents, &data);
	mlx_mouse_hook(data.win_ptr, &handle_mouseevents, &data.map); // For bonus
	mlx_hook(data.win_ptr, 17, (1L<<17),
		&handle_closebutton, &data);
	mlx_loop_hook(data.mlx_ptr, &render_image, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
