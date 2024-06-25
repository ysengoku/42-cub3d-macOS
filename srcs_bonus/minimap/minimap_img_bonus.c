/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_img_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:38:08 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/24 11:30:42 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_minimap_img(t_cub3d *data, t_minimap *mmap)
{
	if (!BONUS)
		return (0);
	mmap->totalsize = MMAP_SCALE * MMAP_SIZE + MMAP_BORDER * MMAP_SIZE;
	mmap->img.img = mlx_new_image(data->mlx_ptr,
			((MMAP_SCALE * MMAP_SIZE) + (MMAP_BORDER * MMAP_SIZE) + 1),
			((MMAP_SCALE * MMAP_SIZE) + (MMAP_BORDER * MMAP_SIZE) + 1));
	if (mmap->img.img == NULL)
	{
		free_all(data, 1);
		ft_perror_exit("MLX", 1);
	}
	mmap->img.addr = mlx_get_data_addr(mmap->img.img,
			&mmap->img.bits_per_pxl, &mmap->img.line_len,
			&mmap->img.endian);
	if (mmap->img.addr == NULL)
	{
		free_all(data, 1);
		ft_perror_exit("MLX", 1);
	}
	return (0);
}
