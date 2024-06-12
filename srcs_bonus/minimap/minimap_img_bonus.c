/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_img_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:38:08 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/12 14:33:07 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_minimap_img(t_cub3d *data, t_minimap *mmap)
{
	if (!BONUS)
		return (0);
	mmap->img.img = mlx_new_image(data->mlx_ptr,
			(data->map.map_len_x - 1) * MMAP_SCALE,
			data->map.map_len_y * MMAP_SCALE);
	if (mmap->img.img == NULL)
		return (free_all(data, 1));
	mmap->img.addr = mlx_get_data_addr(mmap->img.img,
			&mmap->img.bits_per_pxl, &mmap->img.line_len,
			&mmap->img.endian);
	return (0);
}
