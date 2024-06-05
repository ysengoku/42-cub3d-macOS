/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:54:57 by jmougel           #+#    #+#             */
/*   Updated: 2024/06/05 16:17:06 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	display_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

static void	display_data(t_cub3d *data)
{
	printf("\n[DATA MAP]\n\n");
	display_map(data->map.data_map);
	printf("\n[DUP MAP]\n\n");
	display_map(data->map.dup_map);
	printf("\n[MAP]\n\n");
	display_map(data->map.map);
	printf("\n\n");
	printf("[max len x] : %d\n", data->map.map_len_x);
	printf("[max len y] : %d\n", data->map.map_len_y);
	printf("[sprite_NO] : %s\n", data->wall[NO].path);
	printf("[sprite_SO] : %s\n", data->wall[SO].path);
	printf("[sprite_EA] : %s\n", data->wall[WE].path);
	printf("[sprite_WE] : %s\n", data->wall[EA].path);
	printf("[F_RGB]     : [R]%d, [G]%d, [B]%d\n", data->map.f_rgb[0], data->map.f_rgb[1], data->map.f_rgb[2]);
	printf("[C_RGB]     : [R]%d, [G]%d, [B]%d\n", data->map.c_rgb[0], data->map.c_rgb[1], data->map.c_rgb[2]);
}

int	parsing(char *file, t_cub3d *data)
{
	if (!file)
		return (EXIT_FAILURE);
	ft_memset(&data->map, 0, sizeof(t_map));
	data->map.data_map = get_file(file);
	if (!data->map.data_map)
		return (ft_perror_exit("Error\nCub3D", EXIT_FAILURE), EXIT_FAILURE);
	get_data(data);
	get_maps(&data->map);
	check_map(&data->map);
	/* Test */
	
	display_data(data);
	//free_data_map(&data->map);
	
	/********/
	return (EXIT_SUCCESS);
}
