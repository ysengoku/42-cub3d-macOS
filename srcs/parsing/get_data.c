/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:40:20 by jmougel           #+#    #+#             */
/*   Updated: 2024/06/01 16:53:43 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_data(t_cub3d *data)
{
	get_sprites_path(data);
	get_colors_rgb(&data->map);
	return (EXIT_SUCCESS);
}
