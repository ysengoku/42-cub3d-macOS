/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:59:02 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/03 12:16:11 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	convert_color(int rgb[3])
{
	return ((rgb[0] << 16) + (rgb[1] << 8) + rgb[2]);
}

void	put_pxl_color(t_imgdata *img, int x, int y, int color)
{
	char	*pxl;

	if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
	{
		pxl = img->addr + (y * img->line_len + x * (img->bits_per_pxl / 8));
		*(int *)pxl = color;
	}
}

unsigned int	get_txcolor(t_xpm_img *texture, int x, int y)
{
	char	*pxl;

	pxl = texture->addr + (y * texture->line_len + x * (texture->bpp / 8));
	return (*(unsigned int *)pxl);
}
