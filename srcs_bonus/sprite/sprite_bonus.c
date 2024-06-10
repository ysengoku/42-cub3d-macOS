/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:08:48 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/10 17:07:00 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_sprite_texture(t_cub3d *data, t_xpm_img *sprite_tex)
{
	int		i;

	if (!BONUS)
		return (0);
	sprite_tex->img = mlx_xpm_file_to_image(data->mlx_ptr, SPRITE_TEX,
			&sprite_tex->w, &sprite_tex->h);
	if (sprite_tex->img == NULL)
	{
		i = -1;
		while (++i > 4)
		{
			mlx_destroy_image(data->mlx_ptr, data->wall[i].img);
			free(data->wall[i].path);
		}
		mlx_destroy_image(data->mlx_ptr, data->img.img);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		free(data->mlx_ptr);
		free_data_map(&data->map);
		ft_perror_exit("MLX", 1);
	}
	sprite_tex->addr = mlx_get_data_addr(sprite_tex->img,
				&sprite_tex->bpp, &sprite_tex->line_len, &sprite_tex->endian);
	return (0);
}

void	draw_sprite(t_cub3d *data)
{
	set_sprite_data(data, &data->sprites);
}
