/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_rgb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:52:08 by jmougel           #+#    #+#             */
/*   Updated: 2024/06/05 16:15:10 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	split_color_rgb(char *color_rgb, int index)
{
	char	**ar;
	int		i;
	int		color;

	if (!color_rgb)
		return (-1);
	i = 0;
	ar = ft_split(color_rgb, ',');
	if (!ar)
		return (-1);
	i = 0;
	while (ar[i])
		i++;
	if (i != 3)
		return (free_split(ar), -1);
	color = ft_atoi(ar[index]);
	free_split(ar);
	if (color < 0 || color > 255)
		return (-1);
	return (color);
}

static int	extract_color_rgb(char *line, int index)
{
	char	**ar;
	int		color;
	int		i;

	if (!line)
		return (-1);
	color = 0;
	i = 0;
	ar = ft_split(line, ' ');
	if (!ar)
		return (-1);
	while (ar[i])
		i++;
	if (i != 2)
		return (free_split(ar), -1);
	color = split_color_rgb(ar[1], index);
	free_split(ar);
	return (color);
}

static int	get_color_rgb(t_map *data_map, char *c, int index)
{
	int	color;
	int	i;

	i = 0;
	color = -1;
	while (data_map->data_map[i])
	{
		if (ft_strncmp(data_map->data_map[i], c, 1) == 0)
		{
			color = extract_color_rgb(data_map->data_map[i], index);
			break ;
		}
		i++;
	}
	return (color);
}

int	get_colors_rgb(t_map *data_map)
{
	data_map->f_rgb[0] = get_color_rgb(data_map, "F", 0);
	data_map->f_rgb[1] = get_color_rgb(data_map, "F", 1);
	data_map->f_rgb[2] = get_color_rgb(data_map, "F", 2);
	data_map->c_rgb[0] = get_color_rgb(data_map, "C", 0);
	data_map->c_rgb[1] = get_color_rgb(data_map, "C", 1);
	data_map->c_rgb[2] = get_color_rgb(data_map, "C", 2);
	if (data_map->f_rgb[0] == -1 || data_map->f_rgb[1] == -1
		|| data_map->f_rgb[2] == -1 || data_map->c_rgb[0] == -1
		|| data_map->c_rgb[1] == -1 || data_map->c_rgb[2] == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
