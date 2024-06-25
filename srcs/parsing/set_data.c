/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:30:34 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/24 11:42:54 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	create_wall_teture_img(t_cub3d *data, t_xpm_img *wall, int n, \
int i);

void	set_data(t_cub3d *data, t_player *player, t_map *map)
{
	player->pos.x = map->pos_x + 0.5;
	player->pos.y = map->pos_y + 0.5;
	player->start_pos.x = player->pos.x;
	player->start_pos.y = player->pos.y;
	player->dir_rad = (double)map->p_dir * M_PI / 180;
	data->ceiling_color = convert_color(data->map.c_rgb);
	data->floor_color = convert_color(data->map.f_rgb);
}

int	set_wall_texture(t_cub3d *data, t_xpm_img *wall)
{
	int		i;
	int		n;

	i = -1;
	if (!BONUS)
		n = 4;
	else
		n = 12;
	while (++i < n)
		create_wall_teture_img(data, wall, n, i);
	return (0);
}

static void	create_wall_teture_img(t_cub3d *data, t_xpm_img *wall, int n, int i)
{
	wall[i].img = mlx_xpm_file_to_image(data->mlx_ptr, wall[i].path,
			&wall[i].w, &wall[i].h);
	if (wall[i].img == NULL)
	{
		while (i-- > 0)
			mlx_destroy_image(data->mlx_ptr, wall[i].img);
		while (++i < n)
			free(wall[i].path);
		clear_data(data);
		ft_perror_exit("MLX", 1);
	}
	wall[i].addr = mlx_get_data_addr(wall[i].img,
			&wall[i].bpp, &wall[i].line_len, &wall[i].endian);
	if (wall[i].addr == NULL)
	{
		i++;
		while (i-- > 0)
			mlx_destroy_image(data->mlx_ptr, wall[i].img);
		while (++i < n)
			free(wall[i].path);
		clear_data(data);
		ft_perror_exit("MLX", 1);
	}
}
