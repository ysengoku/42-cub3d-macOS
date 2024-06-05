/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:38:40 by jmougel           #+#    #+#             */
/*   Updated: 2024/06/05 16:15:48 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	write_data_map(int fd)
{
	write(fd, "NO ", 3);
	write(fd, SPRITE_NO, ft_strlen(SPRITE_NO));
	write(fd, "\n", 1);
	write(fd, "SO ", 3);
	write(fd, SPRITE_SO, ft_strlen(SPRITE_SO));
	write(fd, "\n", 1);
	write(fd, "WE ", 3);
	write(fd, SPRITE_WE, ft_strlen(SPRITE_WE));
	write(fd, "\n", 1);
	write(fd, "EA ", 3);
	write(fd, SPRITE_EA, ft_strlen(SPRITE_EA));
	write(fd, "\n", 1);
	write(fd, "\n", 1);
	write(fd, "F ", 2);
	write(fd, RGB_F, ft_strlen(RGB_F));
	write(fd, "\n", 1);
	write(fd, "C ", 2);
	write(fd, RGB_C, ft_strlen(RGB_C));
	write(fd, "\n", 1);
	write(fd, "\n", 1);
}

static int	creat_file(char *file)
{
	int		fd;
	char	*line_tmp;

	line_tmp = NULL;
	fd = open(file, O_RDWR | O_CREAT, 0644);
	if (fd == -1)
		return (EXIT_FAILURE);
	write_data_map(fd);
	while (1)
	{
		line_tmp = get_next_line(0);
		if (!line_tmp)
			break ;
		write(fd, line_tmp, ft_strlen(line_tmp));
		free(line_tmp);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

static char	**split_file(int fd)
{
	char	*line;
	char	*line_tmp;
	char	*tmp;
	char	**map;

	line = ft_strdup("");
	while (1)
	{
		if (!line)
			return (NULL);
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		line_tmp = ft_strjoin(line, tmp);
		free(line);
		free(tmp);
		if (!line_tmp)
			return (NULL);
		line = ft_strdup(line_tmp);
		free(line_tmp);
	}
	map = ft_split(line, '\n');
	if (!map)
		return (free(line), NULL);
	return (free(line), map);
}

char	**get_file(char *file)
{
	char	**map;
	int		fd;

	map = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		if (creat_file(file) == EXIT_FAILURE)
			return (NULL);
	}
	else
		close(fd);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	map = split_file(fd);
	close(fd);
	if (!map)
		return (NULL);
	return (map);
}
