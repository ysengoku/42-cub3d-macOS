/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:54:57 by jmougel           #+#    #+#             */
/*   Updated: 2024/06/24 13:27:36 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parsing(char *file, t_cub3d *data)
{
	if (!file)
		return (EXIT_FAILURE);
	ft_memset(&data->map, 0, sizeof(t_map));
	ft_memset(&data->map.check, 0, sizeof(t_check_map));
	data->map.data_map = get_file(data, file);
	if (!data->map.data_map)
		return (exit_parsing(data, "file", true));
	if (check_file(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (get_data(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (get_maps(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_map(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
