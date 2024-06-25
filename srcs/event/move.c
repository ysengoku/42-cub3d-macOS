/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:59:51 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/21 08:07:02 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_player_position(t_cub3d *data, t_player *player, \
double dest_x, double dest_y);

void	move_forward(t_cub3d *data, t_player *player, t_map *map)
{
	double	dest_x;
	double	dest_y;

	if (data->anim_close == true || data->anim_open == true)
		return ;
	dest_x = player->pos.x + (player->dir.x * MOVE);
	dest_y = player->pos.y + (player->dir.y * MOVE);
	update_player_position(data, player, dest_x, dest_y);
	map->pos_x = player->pos.x;
	map->pos_y = player->pos.y;
}

void	move_backward(t_cub3d *data, t_player *player, t_map *map)
{
	double	dest_x;
	double	dest_y;

	if (data->anim_close == true || data->anim_open == true)
		return ;
	dest_x = player->pos.x + (player->dir.x * -1 * MOVE);
	dest_y = player->pos.y + (player->dir.y * -1 * MOVE);
	update_player_position(data, player, dest_x, dest_y);
	map->pos_x = player->pos.x;
	map->pos_y = player->pos.y;
}

void	move_left(t_cub3d *data, t_player *player, t_map *map)
{
	double	dest_x;
	double	dest_y;

	if (data->anim_close == true || data->anim_open == true)
		return ;
	dest_x = player->pos.x + (player->dir.y * MOVE);
	dest_y = player->pos.y + (player->dir.x * -1 * MOVE);
	update_player_position(data, player, dest_x, dest_y);
	map->pos_x = player->pos.x;
	map->pos_y = player->pos.y;
}

void	move_right(t_cub3d *data, t_player *player, t_map *map)
{
	double	dest_x;
	double	dest_y;

	if (data->anim_close == true || data->anim_open == true)
		return ;
	dest_x = player->pos.x + (player->dir.y * -1 * MOVE);
	dest_y = player->pos.y + (player->dir.x * MOVE);
	update_player_position(data, player, dest_x, dest_y);
	map->pos_x = player->pos.x;
	map->pos_y = player->pos.y;
}

static void	update_player_position(t_cub3d *data, t_player *player, \
double dest_x, double dest_y)
{
	if (!BONUS)
	{
		if (data->map.map[(int)player->pos.y][(int)dest_x] && dest_x > 0.1
			&& data->map.map[(int)player->pos.y][(int)dest_x] != ' ')
			player->pos.x = dest_x;
		else
			player->pos.x = player->start_pos.x;
		if (data->map.map[(int)dest_y][(int)player->pos.x]
			&& dest_y > 0.1 && dest_y < data->map.map_len_y - 1
			&& data->map.map[(int)dest_y][(int)player->pos.x] != ' '
			&& data->map.map[(int)dest_y][0])
			player->pos.y = dest_y;
		else
			player->pos.y = player->start_pos.y;
		return ;
	}
	if (data->map.map[(int)player->pos.y][(int)dest_x] != '1'
		&& data->map.map[(int)player->pos.y][(int)dest_x] != 'D'
		&& data->map.map[(int)player->pos.y][(int)dest_x] != 'T')
		player->pos.x = dest_x;
	if (data->map.map[(int)dest_y][(int)player->pos.x] != '1'
		&& data->map.map[(int)dest_y][(int)player->pos.x] != 'D'
		&& data->map.map[(int)dest_y][(int)player->pos.x] != 'T')
		player->pos.y = dest_y;
}
