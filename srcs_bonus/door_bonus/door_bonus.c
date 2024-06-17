/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 09:14:18 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/12 14:54:35 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	animation_open(t_cub3d *data)
{
	int	j;

	j = 0;
	if (data->animation == 6)
	{
		while (j < 90000000)
			j++;
		data->animation = 0;
		data->anim_open = false;
		data->map.map[(int)round(data->player.dir.y)
			+ (int)data->player.pos.y][(int)round(data->player.dir.x)
			+ (int)data->player.pos.x] = 'O';
	}
	else
	{
		while (j < 90000000)
			j++;
		data->animation += 1;
	}
}

static void	animation_close(t_cub3d *data)
{
	int	j;

	j = 0;
	if (data->animation == 0)
	{
		while (j < 90000000)
			j++;
		data->anim_close = false;
	}
	else
	{
		while (j < 90000000)
			j++;
		data->animation -= 1;
	}
}

void	animations(t_cub3d *data)
{
	if (data->anim_open == true && data->anim_close == false)
		animation_open(data);
	else if (data->anim_close == true && data->anim_open == false)
		animation_close(data);
}

// int	get_door_texture_paths(t_cub3d *data)
// {
// 	int	i;

// 	i = 4;
// 	if (!BONUS)
// 		return (0);
// 	data->wall[DR_C].path = ft_strdup(DOOR_TEX_CLOSE);
// 	data->wall[DR1].path = ft_strdup(DOOR_TEX1);
// 	data->wall[DR2].path = ft_strdup(DOOR_TEX2);
// 	data->wall[DR3].path = ft_strdup(DOOR_TEX3);
// 	data->wall[DR4].path = ft_strdup(DOOR_TEX4);
// 	data->wall[DR5].path = ft_strdup(DOOR_TEX5);
// 	data->wall[DR_O].path = ft_strdup(DOOR_TEX_OPEN);
// 	while (i < 11)
// 	{
// 		if (!data->wall[i].path)
// 		{
// 			free_texture_paths(data->wall, 11);
// 			exit_parsing(&data->map, "Error\nCub3D: malloc failed");
// 		}
// 		i++;
// 	}
// 	return (0);
// }

int	get_door_and_treasure_texture_paths(t_cub3d *data)
{
	int	i;

	i = 4;
	if (!BONUS)
		return (0);
	data->wall[DR_C].path = ft_strdup(DOOR_TEX_CLOSE);
	data->wall[DR1].path = ft_strdup(DOOR_TEX1);
	data->wall[DR2].path = ft_strdup(DOOR_TEX2);
	data->wall[DR3].path = ft_strdup(DOOR_TEX3);
	data->wall[DR4].path = ft_strdup(DOOR_TEX4);
	data->wall[DR5].path = ft_strdup(DOOR_TEX5);
	data->wall[DR_O].path = ft_strdup(DOOR_TEX_OPEN);
	data->wall[TR].path = ft_strdup(TREASURE_TEX);
	while (i < 12)
	{
		if (!data->wall[i].path)
		{
			free_texture_paths(data->wall, 12);
			exit_parsing(&data->map, "Error\nCub3D: malloc failed");
		}
		i++;
	}
	return (0);
}

void	switch_door_status(t_cub3d *data)
{
	int		target_x;
	int		target_y;

	target_x = (int)data->player.pos.x;
	target_y = (int)data->player.pos.y;
	if (data->player.dir.x > 0)
		target_x += round(data->player.dir.x);
	else if (data->player.dir.x < 0)
		target_x -= round(-data->player.dir.x);
	if (data->player.dir.y > 0)
		target_y += round(data->player.dir.y);
	else if (data->player.dir.y < 0)
		target_y -= round(-data->player.dir.y);
	if (data->map.map[target_y][target_x] == 'D' && data->anim_close == false)
	{
		data->anim_open = true;
		data->animation = 0;
	}
	else if (data->map.map[target_y][target_x] == 'O' && data->anim_open == false)
	{
		data->map.map[(int)round(data->player.dir.y)
			+ (int)data->player.pos.y][(int)round(data->player.dir.x)
			+ (int)data->player.pos.x] = 'D';
		data->animation = 6;
		data->anim_close = true;
	}
}
