/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:38:40 by jmougel           #+#    #+#             */
/*   Updated: 2024/06/24 10:29:37 by jmougel          ###   ########.fr       */
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

static int	check_nl_in_map(t_cub3d *data, char *line)
{
	if (line[0] == '\n' && data->map.check.in_map == true)
		return (EXIT_FAILURE);
	if (line[0] != '\n' && line_is_map(line, '\n') == EXIT_SUCCESS
		&& data->map.check.so && data->map.check.no
		&& data->map.check.we && data->map.check.ea
		&& data->map.check.f && data->map.check.c
		&& data->map.check.nbr_data == 6)
		data->map.check.in_map = true;
	else if (ft_strncmp(line, "SO ", 3) == 0)
		data->map.check.so = true;
	else if (ft_strncmp(line, "NO ", 3) == 0)
		data->map.check.no = true;
	else if (ft_strncmp(line, "WE ", 3) == 0)
		data->map.check.we = true;
	else if (ft_strncmp(line, "EA ", 3) == 0)
		data->map.check.ea = true;
	else if (ft_strncmp(line, "F ", 2) == 0)
		data->map.check.f = true;
	else if (ft_strncmp(line, "C ", 2) == 0)
		data->map.check.c = true;
	if (line_is_map(line, '\n') == EXIT_FAILURE)
		data->map.check.nbr_data++;
	return (EXIT_SUCCESS);
}

static char	**split_file(t_cub3d *data, int fd)
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
		if (check_nl_in_map(data, tmp) == EXIT_FAILURE)
			return (ft_free_all(2, tmp, line)
				, ft_error_exit("nl in map", 1), NULL);
		line_tmp = ft_strjoin(line, tmp);
		ft_free_all(2, tmp, line);
		if (!line_tmp)
			return (NULL);
		line = ft_strdup(line_tmp);
		free(line_tmp);
	}
	map = ft_split(line, '\n');
	return (free(line), map);
}

char	**get_file(t_cub3d *data, char *file)
{
	char	**map;
	int		fd;

	map = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		if (BONUS)
		{
			if (creat_file(file) == EXIT_FAILURE)
				return (NULL);
		}
		else
			return (NULL);
	}
	else
		close(fd);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	map = split_file(data, fd);
	close(fd);
	if (!map)
		return (NULL);
	return (map);
}
