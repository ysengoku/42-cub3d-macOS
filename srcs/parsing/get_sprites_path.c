/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sprites_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:53:25 by jmougel           #+#    #+#             */
/*   Updated: 2024/06/24 12:39:25 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*get_path(t_cub3d *data, char *line)
{
	char	**ar;
	char	*path;
	int		i;

	if (!line)
		return (NULL);
	path = NULL;
	i = 0;
	ar = ft_split(line, ' ');
	if (!ar)
		return (NULL);
	while (ar[i])
		i++;
	if (i != 2)
		return (free_split(ar), NULL);
	path = ft_strdup(ar[1]);
	if (!path)
		return (exit_parsing(data, "malloc", true), NULL);
	free_split(ar);
	return (path);
}

static int	attribute_path(t_cub3d *data, int i)
{
	if (ft_strncmp(data->map.data_map[i], "NO ", 3) == 0)
	{
		if (data->wall[NO].path)
			return (exit_parsing(data, "NO texture already set", false));
		data->wall[NO].path = get_path(data, data->map.data_map[i]);
	}
	else if (ft_strncmp(data->map.data_map[i], "SO ", 3) == 0)
	{
		if (data->wall[SO].path)
			return (exit_parsing(data, "SO texture already set", false));
		data->wall[SO].path = get_path(data, data->map.data_map[i]);
	}
	else if (ft_strncmp(data->map.data_map[i], "WE ", 3) == 0)
	{
		if (data->wall[WE].path)
			return (exit_parsing(data, "WE texture already set", false));
		data->wall[WE].path = get_path(data, data->map.data_map[i]);
	}
	else if (ft_strncmp(data->map.data_map[i], "EA ", 3) == 0)
	{
		if (data->wall[EA].path)
			return (exit_parsing(data, "EA texture already set", false));
		data->wall[EA].path = get_path(data, data->map.data_map[i]);
	}
	return (EXIT_SUCCESS);
}

int	get_sprites_path(t_cub3d *data)
{
	int	i;

	i = 0;
	while (data->map.data_map[i])
	{
		if (attribute_path(data, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	if (!data->wall[NO].path || !data->wall[SO].path
		|| !data->wall[WE].path || !data->wall[EA].path)
		return (exit_parsing(data, "invalid sprite", false));
	if (BONUS && get_door_and_treasure_texture_paths(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
