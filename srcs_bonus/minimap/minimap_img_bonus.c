/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_img_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:38:08 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/05 16:19:50 by yusengok         ###   ########.fr       */
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
	/*===== If minimap with texture ==========================================*/
	mmap->floor.img = mlx_xpm_file_to_image(data->mlx_ptr, MMAP_F,
			&mmap->floor.w, &mmap->floor.h);
	mmap->player.img = mlx_xpm_file_to_image(data->mlx_ptr, MMAP_PL,
			&mmap->player.w, &mmap->player.h);
	mmap->wall.img = mlx_xpm_file_to_image(data->mlx_ptr, MMAP_WL,
			&mmap->wall.w, &mmap->wall.h);
	if (!mmap->floor.img || !mmap->player.img || !mmap->wall.img)
		return (free_all(data, 1));
	mmap->floor.addr = mlx_get_data_addr(mmap->floor.img,
			&mmap->floor.bpp, &mmap->floor.line_len, &mmap->floor.endian);
	mmap->player.addr = mlx_get_data_addr(mmap->player.img,
			&mmap->player.bpp, &mmap->player.line_len, &mmap->player.endian);
	mmap->wall.addr = mlx_get_data_addr(mmap->wall.img,
			&mmap->wall.bpp, &mmap->wall.line_len, &mmap->wall.endian);
	/*========================================================================*/
	return (0);
}
