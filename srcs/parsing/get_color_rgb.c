/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_rgb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:52:08 by jmougel           #+#    #+#             */
/*   Updated: 2024/06/24 12:58:38 by jmougel          ###   ########.fr       */
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
			return (free_split(ar), -1);
	}
	color = ft_atoi(ar[index]);
	free_split(ar);
	if (color < 0 || color > 255)
		return (-1);
	return (color);
}

static int	check_comma(char *line)
{
	int	i;
	int	comma;

	i = 0;
	comma = 0;
	while (line[i])
	{
		if (line[i] == ',')
			comma++;
		i++;
	}
	if (comma != 2)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
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
	if (check_comma(ar[1]) == EXIT_FAILURE)
		return (-1);
	color = split_color_rgb(ar[1], index);
	free_split(ar);
	return (color);
}

static int	treat_rgb(t_cub3d *data, char *data_line, char c)
{
	if (c == 'F')
	{
		if (data->map.f_rgb[0] != -1 || data->map.f_rgb[1] != -1
			|| data->map.f_rgb[2] != -1)
			return (EXIT_FAILURE);
		if (ft_strncmp(data_line, "F", 1) == 0)
			data->map.f_rgb[0] = extract_color_rgb(data_line, 0);
		if (ft_strncmp(data_line, "F", 1) == 0)
			data->map.f_rgb[1] = extract_color_rgb(data_line, 1);
		if (ft_strncmp(data_line, "F", 1) == 0)
			data->map.f_rgb[2] = extract_color_rgb(data_line, 2);
	}
	else if (c == 'C')
	{
		if (data->map.c_rgb[0] != -1 || data->map.c_rgb[1] != -1
			|| data->map.c_rgb[2] != -1)
			return (EXIT_FAILURE);
		if (ft_strncmp(data_line, "C", 1) == 0)
			data->map.c_rgb[0] = extract_color_rgb(data_line, 0);
		if (ft_strncmp(data_line, "C", 1) == 0)
			data->map.c_rgb[1] = extract_color_rgb(data_line, 1);
		if (ft_strncmp(data_line, "C", 1) == 0)
			data->map.c_rgb[2] = extract_color_rgb(data_line, 2);
	}
	return (EXIT_SUCCESS);
}

int	get_colors_rgb(t_cub3d *data)
{
	int	i;

	i = 0;
	ft_memset(data->map.f_rgb, -1, sizeof(int) * 3);
	ft_memset(data->map.c_rgb, -1, sizeof(int) * 3);
	while (data->map.data_map[i])
	{
		if (ft_strncmp(data->map.data_map[i], "F ", 2) == 0)
		{
			if (treat_rgb(data, data->map.data_map[i], 'F') == EXIT_FAILURE)
				return (exit_parsing(data, "multiple definition of F", false));
		}
		else if (ft_strncmp(data->map.data_map[i], "C ", 2) == 0)
		{
			if (treat_rgb(data, data->map.data_map[i], 'C') == EXIT_FAILURE)
				return (exit_parsing(data, "multiple definition of C", false));
		}
		i++;
	}
	if (data->map.f_rgb[0] == -1 || data->map.f_rgb[1] == -1
		|| data->map.f_rgb[2] == -1 || data->map.c_rgb[0] == -1
		|| data->map.c_rgb[1] == -1 || data->map.c_rgb[2] == -1)
		return (exit_parsing(data, "invalid RGB", false));
	return (EXIT_SUCCESS);
}
