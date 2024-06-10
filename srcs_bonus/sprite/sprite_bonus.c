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

int	set_sprite_texture(t_cub3d *data, t_xpm_img *sprite)
{
	int		i;

	if (!BONUS)
		return (0);
	sprite->img = mlx_xpm_file_to_image(data->mlx_ptr, SPRITE_TEX,
			&sprite->w, &sprite->h);
	if (sprite->img == NULL)
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
	sprite->addr = mlx_get_data_addr(sprite->img,
				&sprite->bpp, &sprite->line_len, &sprite->endian);
	return (0);
}

void	draw_sprite(t_cub3d *data)
{
	t_sprite	sprite_draw;
	double		inv_det;

	(void)data;
	ft_memset(&sprite_draw, 0, sizeof(sprite_draw));
	sprite_draw.relative_x = 0;
	sprite_draw.relative_y = 0;

	inv_det = 1.0 / (data->player.plane_x * data->player.dir_y - data->player.dir_x * data->player.plane_y);
	// *transform_x = inv_det * (game->player.dir.y * normalized_sprite.x - game->player.dir.x * normalized_sprite.y);
	// *transform_y = inv_det * (-game->player.plane.y * normalized_sprite.x + game->player.plane.x * normalized_sprite.y);
}
