/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_rgb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:52:08 by jmougel           #+#    #+#             */
/*   Updated: 2024/06/19 11:40:30 by jmougel          ###   ########.fr       */
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
	ar = ft_split(color_rgb, ',');
	if (!ar)
		return (-1);
	i = 0;
	while (ar[i])
		i++;
	if (i != 3)
		return (free_split(ar), -1);
	i = 0;
	while (ar[index][i])
	{
		if (ft_isdigit(ar[index][i++]) == 0)
			return (-1);
	}
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

static int	get_color_rgb(char *data_line, char *c, int index)
{
	int	color;

	color = -1;
	if (ft_strncmp(data_line, c, 1) == 0)
		color = extract_color_rgb(data_line, index);
	return (color);
}

static void	treat_rgb(t_cub3d *data, char *data_line, char c)
{
	if (c == 'F')
	{
		if (data->map.f_rgb[0] != 0 || data->map.f_rgb[1] != 0
			|| data->map.f_rgb[2] != 0)
		{
			free_texture_paths(data->wall, 4);
			exit_parsing(&data->map, "Error\nCub3D: multiple data");
		}
		data->map.f_rgb[0] = get_color_rgb(data_line, "F", 0);
		data->map.f_rgb[1] = get_color_rgb(data_line, "F", 1);
		data->map.f_rgb[2] = get_color_rgb(data_line, "F", 2);
	}
	else if (c == 'C')
	{
		if (data->map.c_rgb[0] != 0 || data->map.c_rgb[1] != 0
			|| data->map.c_rgb[2] != 0)
		{
			free_texture_paths(data->wall, 4);
			exit_parsing(&data->map, "Error\nCub3D: multiple data");
		}
		data->map.c_rgb[0] = get_color_rgb(data_line, "C", 0);
		data->map.c_rgb[1] = get_color_rgb(data_line, "C", 1);
		data->map.c_rgb[2] = get_color_rgb(data_line, "C", 2);
	}
}

int	get_colors_rgb(t_cub3d *data)
{
	int	i;

	i = 0;
	while (data->map.data_map[i])
	{
		if (ft_strncmp(data->map.data_map[i], "F ", 2) == 0)
			treat_rgb(data, data->map.data_map[i], 'F');
		else if (ft_strncmp(data->map.data_map[i], "C ", 2) == 0)
			treat_rgb(data, data->map.data_map[i], 'C');
		i++;
	}
	if (data->map.f_rgb[0] == -1 || data->map.f_rgb[1] == -1
		|| data->map.f_rgb[2] == -1 || data->map.c_rgb[0] == -1
		|| data->map.c_rgb[1] == -1 || data->map.c_rgb[2] == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
