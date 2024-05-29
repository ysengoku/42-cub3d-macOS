/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:59:02 by yusengok          #+#    #+#             */
/*   Updated: 2024/05/29 15:42:22 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	convert_color(t_color color)
{
	return ((color.r << 16) + (color.g << 8) + color.b);
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
