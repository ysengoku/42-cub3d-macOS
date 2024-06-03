/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:25:44 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/03 15:46:06 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_mapdata(t_map *map)
{
	int	i;
	
	i = 0;
	while (i < map->map_len_y)
	{
		free(map->map[i]);
		map->map[i] = 0;
		free(map->data_map[i]);
		map->data_map[i] = 0;
		free(map->dup_map[i]);
		map->dup_map[i] = 0;
		i++;
	}
	free(map->map);
	free(map->data_map);
	free(map->dup_map);
	map->map = 0;
	map->data_map = 0;
	map->dup_map = 0;
	free(map->sprite_no);
	free(map->sprite_so);
	free(map->sprite_we);
	free(map->sprite_ea);
	map->sprite_no = 0;
	map->sprite_so = 0;
	map->sprite_we = 0;
	map->sprite_ea = 0;
}

int	free_all(t_cub3d *data, int status)
{
	int	i;

	mlx_destroy_image(data->mlx_ptr, data->img.img);
	i = 0;
	while (i < 4)
	{
		mlx_destroy_image(data->mlx_ptr, data->wall[i].img);
		free(data->wall[i].path);
		i++;
	}
	if (data->mmap.img.img)
		mlx_destroy_image(data->mlx_ptr, data->mmap.img.img);
	if (data->mmap.floor.img)
		mlx_destroy_image(data->mlx_ptr, data->mmap.floor.img);
	if (data->mmap.player.img)
		mlx_destroy_image(data->mlx_ptr, data->mmap.player.img);
	if (data->mmap.wall.img)
		mlx_destroy_image(data->mlx_ptr, data->mmap.wall.img);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free(data->mlx_ptr);
	free_mapdata(&data->map); // to check
	return (status);
}
