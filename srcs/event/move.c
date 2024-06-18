/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:59:51 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/05 16:12:57 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_cub3d *data, t_player *player, t_map *map)
{
	int		dest_x;
	int		dest_y;

	dest_x = player->pos.x + (player->dir.x * MOVE);
	dest_y = player->pos.y + (player->dir.y * MOVE);
	if (map->map[(int)player->pos.y][dest_x] != '1'
		&& map->map[(int)player->pos.y][dest_x] != 'D'
		&& map->map[(int)player->pos.y][dest_x] != 'T')
	{
		player->pos.x += player->dir.x * MOVE;
		data->map.pos_x = player->pos.x;
	}
	if (map->map[dest_y][(int)player->pos.x] != '1'
		&& map->map[dest_y][(int)player->pos.x] != 'D'
		&& map->map[dest_y][(int)player->pos.x] != 'T')
	{
		player->pos.y += player->dir.y * MOVE;
		data->map.pos_y = player->pos.y;
	}
}

void	move_backward(t_cub3d *data, t_player *player, t_map *map)
{
	int		dest_x;
	int		dest_y;

	dest_x = player->pos.x + (player->dir.x * -1 * MOVE);
	dest_y = player->pos.y + (player->dir.y * -1 * MOVE);
	if (map->map[(int)player->pos.y][dest_x] != '1'
		&& map->map[(int)player->pos.y][dest_x] != 'D'
		&& map->map[(int)player->pos.y][dest_x] != 'T')
	{
		player->pos.x += player->dir.x * -1 * MOVE;
		data->map.pos_x = player->pos.x;
	}
	if (map->map[dest_y][(int)player->pos.x] != '1'
		&& map->map[dest_y][(int)player->pos.x] != 'D'
		&& map->map[dest_y][(int)player->pos.x] != 'T')
	{
		player->pos.y += player->dir.y * -1 * MOVE;
		data->map.pos_y = player->pos.y;
	}
}

void	move_left(t_cub3d *data, t_player *player, t_map *map)
{
	int		dest_x;
	int		dest_y;

	dest_x = player->pos.x + (player->dir.y * MOVE);
	dest_y = player->pos.y + (player->dir.x * -1 * MOVE);
	if (map->map[(int)player->pos.y][dest_x] != '1'
		&& map->map[(int)player->pos.y][dest_x] != 'D'
		&& map->map[(int)player->pos.y][dest_x] != 'T')
	{
		player->pos.x += player->dir.y * MOVE;
		data->map.pos_x = player->pos.x;
	}
	if (map->map[dest_y][(int)player->pos.x] != '1'
		&& map->map[dest_y][(int)player->pos.x] != 'D'
		&& map->map[dest_y][(int)player->pos.x] != 'T')
	{
		player->pos.y += player->dir.x * -1 * MOVE;
		data->map.pos_y = player->pos.y;
	}
}

void	move_right(t_cub3d *data, t_player *player, t_map *map)
{
	int		dest_x;
	int		dest_y;

	dest_x = player->pos.x + (player->dir.y * -1 * MOVE);
	dest_y = player->pos.y + (player->dir.x * MOVE);
	if (map->map[(int)player->pos.y][dest_x] != '1'
		&& map->map[(int)player->pos.y][dest_x] != 'D'
		&& map->map[(int)player->pos.y][dest_x] != 'T')
	{
		player->pos.x += player->dir.y * -1 * MOVE;
		data->map.pos_y = player->pos.y;
	}
	if (map->map[dest_y][(int)player->pos.x] != '1'
		&& map->map[dest_y][(int)player->pos.x] != 'D'
		&& map->map[dest_y][(int)player->pos.x] != 'T')
	{
		player->pos.y += player->dir.x * MOVE;
		data->map.pos_y = player->pos.y;
	}
}
