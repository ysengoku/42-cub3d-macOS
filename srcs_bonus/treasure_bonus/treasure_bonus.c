/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treasure_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:31:39 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/17 17:49:52 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_treasure(t_cub3d *data, t_treasure *treasure)
{
	int	x;
	int	y;
	int	tex_x;
	int	tex_y;
	int color;
	
	if (!treasure->visible)
	{
		printf("Treasure is not visible\n");
		return ;
	}
	x = treasure->start_x;
	if (treasure->camera.y >= data->wall_zbuffer[treasure->screen_x])
    {
        printf("Camera.y is greater than or equal to wall_zbuffer[screen_x]\n");
        return ;
    }
	while (x < treasure->end_x)
	{
		tex_x = (int)(x - (-treasure->draw_width / 2 + treasure->screen_x))
			* data->wall[TR].w / treasure->draw_width;
		if (treasure->camera.y < data->wall_zbuffer[x] && tex_x >= 0)
		{
			y = treasure->start_y;
			while (y < treasure->end_y)
			{
				tex_y = (int)(y - (-treasure->draw_height / 2 + WIN_H / 2))
					* data->wall[TR].h / treasure->draw_height;
				color = get_txcolor(&data->wall[TR], tex_x, tex_y);
				if (color && color != 0x000000)
					put_pxl_color(&data->img, x, y, color);
				y++;
			}
		}
		x++;
	}
}