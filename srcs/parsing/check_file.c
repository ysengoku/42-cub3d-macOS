/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 10:22:44 by jmougel           #+#    #+#             */
/*   Updated: 2024/06/19 11:52:18 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_player(char c)
{
	char	*player;
	int		i;

	i = 0;
	player = "SNWE";
	while (player[i])
	{
		if (c == player[i])
			return (1);
		i++;
	}
	return (0);
}

static int	is_bonus(char c)
{
	char	*door;
	int		i;

	i = 0;
	door = "DdOoT";
	while (door[i])
	{
		if (c == door[i])
			return (1);
		i++;
	}
	return (0);
}

static int	line_is_map(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		else if (line[i] == '1')
			i++;
		else if (line[i] == '0')
			i++;
		else if (i != 0 && is_player(line[i]))
			i++;
		else if (BONUS && i != 0 && is_bonus(line[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

int	check_file(t_cub3d *data)
{
	int	i;

	i = 0;
	while (data->map.data_map[i])
	{
		if (ft_strncmp(data->map.data_map[i], "F ", 2) == 0
			|| ft_strncmp(data->map.data_map[i], "C ", 2) == 0
			|| ft_strncmp(data->map.data_map[i], "NO ", 3) == 0
			|| ft_strncmp(data->map.data_map[i], "SO ", 3) == 0
			|| ft_strncmp(data->map.data_map[i], "WE ", 3) == 0
			|| ft_strncmp(data->map.data_map[i], "EA ", 3) == 0
			|| line_is_map(data->map.data_map[i]))
			i++;
		else
		{
			free_texture_paths(data->wall, 4);
			exit_parsing(&data->map, "Error\nCub3D: bad data detected");
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
