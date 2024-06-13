/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:30:34 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/05 16:17:21 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_data(t_cub3d *data, t_player *player, t_map *map)
{
	player->pos_x = map->pos_x;
	player->pos_y = map->pos_y;
	player->dir = (double)map->p_dir;
	data->ceiling_color = convert_color(data->map.c_rgb);
	data->floor_color = convert_color(data->map.f_rgb);
}

int	set_wall_texture(t_cub3d *data, t_xpm_img wall[4])
{
	int		i;

	i = -1;
	while (++i < 5)
	{
		wall[i].img = mlx_xpm_file_to_image(data->mlx_ptr, wall[i].path,
				&wall[i].w, &wall[i].h);
		if (wall[i].img == NULL)
		{
			while (i-- > 0)
				mlx_destroy_image(data->mlx_ptr, wall[i].img);
			while (++i < 5) // if mandatory, i < 4
				free(wall[i].path);
			mlx_destroy_image(data->mlx_ptr, data->img.img);
			mlx_destroy_window(data->mlx_ptr, data->win_ptr);
			free(data->mlx_ptr);
			free_data_map(&data->map);
			ft_perror_exit("MLX", 1);
		}
		wall[i].addr = mlx_get_data_addr(wall[i].img,
				&wall[i].bpp, &wall[i].line_len, &wall[i].endian);
	}
	return (0);
}
