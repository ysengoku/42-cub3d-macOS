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
	
	dest_x = player->pos_x + (player->dir_x * MOVE);
	dest_y = player->pos_y + (player->dir_y * MOVE);
	if (map->map[(int)player->pos_y][dest_x] != '1'
		&& map->map[dest_y][(int)player->pos_x] != '1'
		&& map->map[dest_y][dest_x] != '1')
	{
		player->pos_x += player->dir_x * MOVE;
		player->pos_y += player->dir_y * MOVE;
	}
	data->player.moved = 1;
}

void	move_backward(t_cub3d *data, t_player *player, t_map *map)
{
	int		dest_x;
	int		dest_y;
	
	dest_x = player->pos_x + (player->dir_x * -1 * MOVE);
	dest_y = player->pos_y + (player->dir_y * -1 * MOVE);
	if (map->map[(int)player->pos_y][dest_x] != '1'
		&& map->map[dest_y][(int)player->pos_x] != '1'
		&& map->map[dest_y][dest_x] != '1')
	{
		player->pos_x += player->dir_x * -1 * MOVE;
		player->pos_y += player->dir_y * -1 * MOVE;
	}
	data->player.moved = 1;
}

void	move_left(t_cub3d *data, t_player *player, t_map *map)
{
	int		dest_x;
	int		dest_y;
	
	dest_x = player->pos_x + (player->dir_y * MOVE);
	dest_y = player->pos_y + (player->dir_x * -1 * MOVE);
	if (map->map[(int)player->pos_y][dest_x] != '1'
		&& map->map[dest_y][(int)player->pos_x] != '1'
		&& map->map[dest_y][dest_x] != '1')
	{
		player->pos_x += player->dir_y * MOVE;
		player->pos_y += player->dir_x * -1 * MOVE;
	}
	data->player.moved = 1;
}

void	move_right(t_cub3d *data, t_player *player, t_map *map)
{
	int		dest_x;
	int		dest_y;
	
	dest_x = player->pos_x + (player->dir_y * -1 * MOVE);
	dest_y = player->pos_y + (player->dir_x * MOVE);
	if (map->map[(int)player->pos_y][dest_x] != '1'
		&& map->map[dest_y][(int)player->pos_x] != '1'
		&& map->map[dest_y][dest_x] != '1')
	{
		player->pos_x += player->dir_y * -1 * MOVE;
		player->pos_y += player->dir_x * MOVE;
	}
	data->player.moved = 1;
}
