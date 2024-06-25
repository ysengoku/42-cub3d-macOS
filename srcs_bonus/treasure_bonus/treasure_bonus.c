/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treasure_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:31:39 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/21 08:19:50 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_line(t_cub3d *data, t_treasure *treasure, int x);

void	draw_treasure(t_cub3d *data, t_treasure *treasure, int x)
{
	if (!treasure->visible)
		return ;
	if (treasure->camera.y >= data->wall_zbuffer[treasure->screen_x])
		return ;
	if (x >= treasure->start_x && x < treasure->end_x)
		draw_line(data, treasure, x);
}

static void	draw_line(t_cub3d *data, t_treasure *treasure, int x)
{
	int	tex_x;
	int	tex_y;
	int	color;
	int	y;

	tex_x = (int)(x - (-treasure->draw_width / 2 + treasure->screen_x)) *\
	data->wall[TR].w / treasure->draw_width;
	if (treasure->camera.y < data->wall_zbuffer[x] && tex_x >= 0)
	{
		y = treasure->start_y;
		while (y < treasure->end_y)
		{
			tex_y = (int)(y - (-treasure->draw_height / 2 + data->win_half_h)) *\
			data->wall[TR].h / treasure->draw_height;
			color = get_txcolor(&data->wall[TR], tex_x, tex_y);
			if (color && color != 0x000000)
				put_pxl_color(&data->img, x, y, color);
			y++;
		}
	}
}
