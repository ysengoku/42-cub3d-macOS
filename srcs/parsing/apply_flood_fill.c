/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_flood_fill.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:19:54 by jmougel           #+#    #+#             */
/*   Updated: 2024/06/24 09:14:21 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	apply_flood_fill(t_cub3d *data)
{
	flood_fill_rec(data, data->map.dup_map, data->map.pos_x, data->map.pos_y);
	flood_fill_iter(data, data->map.dup_map);
	if (data->map.check.invalid_map)
		return (exit_parsing(data, "map not close", false));
	if (data->map.check.catch_treasure == false)
		return (exit_parsing(data, "treasure not reachable", false));
	return (EXIT_SUCCESS);
}
