/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_treasure_data_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:15:19 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/24 11:06:11 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calculate_camera_coordinates(t_cub3d *data, t_treasure *treasure);
static void	get_draw_range(t_cub3d *data, t_treasure *treasure);

void	set_treasure_data(t_cub3d *data, t_treasure *treasure)
{
	treasure->visible = 0;
	calculate_camera_coordinates(data, treasure);
	if (treasure->camera.y > 0 && fabs(treasure->camera.x
			/ treasure->camera.y) < data->player.plane_length)
	{
		get_draw_range(data, treasure);
		treasure->visible = 1;
	}
}

static void	calculate_camera_coordinates(t_cub3d *data, t_treasure *treasure)
{
	double	inverse_matrix_factor;

	treasure->relative_pos.x = treasure->map.x - data->player.pos.x;
	treasure->relative_pos.y = treasure->map.y - data->player.pos.y;
	inverse_matrix_factor = 1.0 / (data->player.plane.x * data->player.dir.y
			- data->player.dir.x * data->player.plane.y);
	treasure->camera.x = inverse_matrix_factor
		* (data->player.dir.y * treasure->relative_pos.x
			- data->player.dir.x * treasure->relative_pos.y);
	treasure->camera.y = inverse_matrix_factor
		* (-data->player.plane.y * treasure->relative_pos.x
			+ data->player.plane.x * treasure->relative_pos.y);
}

static void	get_draw_range(t_cub3d *data, t_treasure *treasure)
{
	treasure->screen_x = (int)(data->win_half_w
			* (1 + treasure->camera.x / treasure->camera.y));
	treasure->draw_height = ft_abs((int)(WIN_H / treasure->camera.y));
	treasure->start_y = -treasure->draw_height / 2 + data->win_half_h;
	if (treasure->start_y < 0)
		treasure->start_y = 0;
	treasure->end_y = treasure->draw_height / 2 + data->win_half_h;
	if (treasure->end_y >= WIN_H)
		treasure->end_y = WIN_H - 1;
	treasure->draw_width = treasure->draw_height;
	treasure->start_x = -treasure->draw_width / 2 + treasure->screen_x;
	if (treasure->start_x < 0)
		treasure->start_x = 0;
	treasure->end_x = treasure->draw_width / 2 + treasure->screen_x;
	if (treasure->end_x >= WIN_W)
		treasure->end_x = WIN_W - 1;
}
