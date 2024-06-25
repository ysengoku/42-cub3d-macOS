/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 10:22:44 by jmougel           #+#    #+#             */
/*   Updated: 2024/06/24 11:39:27 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	line_is_map(char *line, char c)
{
	int	i;

	i = 0;
	if (!c)
		c = ' ';
	if (!BONUS)
	{
		while (line[i] == ' ' || line[i] == '1' || line[i] == '0'
			|| line[i] == 'S' || line[i] == 'N' || line[i] == 'E'
			|| line[i] == 'W' || line[i] == c)
			i++;
	}
	else
	{
		while (line[i] == ' ' || line[i] == '1' || line[i] == '0'
			|| line[i] == 'S' || line[i] == 'N' || line[i] == 'E'
			|| line[i] == 'W' || line[i] == 'D' || line[i] == 'T'
			|| line[i] == c)
			i++;
	}
	if (line[i] == '\0')
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	line_is_space(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
	{
		i++;
	}
	if (line[i] == '\0')
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	line_is_data(char *line)
{
	if (ft_strncmp(line, "F ", 2) == 0
		|| ft_strncmp(line, "C ", 2) == 0
		|| ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	check_file(t_cub3d *data)
{
	int	i;

	i = 0;
	data->map.check.nbr_data = 0;
	while (data->map.data_map[i])
	{
		if (line_is_map(data->map.data_map[i], 0) == EXIT_SUCCESS
			&& line_is_space(data->map.data_map[i]) == EXIT_FAILURE)
			break ;
		else if (line_is_map(data->map.data_map[i], 0) == EXIT_FAILURE
			&& line_is_data(data->map.data_map[i]) == EXIT_SUCCESS)
			data->map.check.nbr_data++;
		else if (line_is_map(data->map.data_map[i], 0) == EXIT_FAILURE
			&& line_is_data(data->map.data_map[i]) == EXIT_FAILURE)
			return (exit_parsing(data, "bad data detected", false));
		else if (line_is_space(data->map.data_map[i]) == EXIT_SUCCESS
			&& data->map.check.nbr_data < 6)
			return (exit_parsing(data, "line with space detected", false));
		i++;
	}
	if (data->map.check.nbr_data < 6)
		return (exit_parsing(data, "missing data", false));
	else if (data->map.check.nbr_data > 6)
		return (exit_parsing(data, "duplicate data detected", false));
	return (EXIT_SUCCESS);
}
