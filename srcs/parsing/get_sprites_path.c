/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sprites_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:53:25 by jmougel           #+#    #+#             */
/*   Updated: 2024/06/03 11:03:50 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

static char	*get_path(char *line)
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
	free_split(ar);
	return (path);
}

static char	*get_sprite_path(char *sprite, t_map *data_map)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while(data_map->data_map[i])
	{
		if (ft_strncmp(data_map->data_map[i], sprite, 2) == 0)
		{
			path = get_path(data_map->data_map[i]);
			break ;
		}
		i++;
	}
	return (path);
}

int	get_sprites_path(t_map *data_map)
{
	data_map->sprite_no = get_sprite_path("NO", data_map);
	data_map->sprite_so = get_sprite_path("SO", data_map);
	data_map->sprite_we = get_sprite_path("WE", data_map);
	data_map->sprite_ea = get_sprite_path("EA", data_map);
	if (!data_map->sprite_no || !data_map->sprite_so
		|| !data_map->sprite_we || !data_map->sprite_ea)
		return (ft_exit_parsing(data_map, "Error\nCub3D: invalid sprite"),EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
