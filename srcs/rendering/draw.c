/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   draw.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: yusengok <yusengok@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/05/28 08:57:21 by yusengok		  #+#	#+#			 */
/*   Updated: 2024/06/20 08:10:58 by yusengok		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "cub3d.h"

static double	get_wall_x(t_cub3d *data, t_ray *ray, t_hit *sprite);

void	draw_ceiling_and_floor(t_cub3d *data, int x)
{
	int	y;

	y = 0;
	while (y < data->win_half_h)
		put_pxl_color(&data->img, x, y++, data->ceiling_color);
	while (y < WIN_H)
		put_pxl_color(&data->img, x, y++, data->floor_color);
}

void	draw_wall(t_cub3d *data, int x, t_ray *r)
{
	t_line	line;
	double	wall_x;

	ft_memset(&line, 0, sizeof(line));
	line.y_start = data->win_half_h - r->wall.h * 0.5;
	if (line.y_start < 0)
		line.y_start = 0;
	line.y_end = data->win_half_h + r->wall.h * 0.5;
	if (line.y_end > WIN_H)
		line.y_end = WIN_H -1;
	line.y = line.y_start;
	wall_x = get_wall_x(data, r, &r->wall);
	if (r->wall.h != 0)
		line.span = (double)data->wall[r->wall.side].h / r->wall.h;
	line.tx_x = (int)(wall_x * (double)data->wall[r->wall.side].w);
	if (r->wall.h > WIN_H)
		line.tx_start_y = (r->wall.h - WIN_H) * 0.5;
	while (++line.y < line.y_end)
	{
		line.tx_y = (int)(((double)line.y - (double)line.y_start
					+ line.tx_start_y) * line.span);
		line.color = get_txcolor(&data->wall[r->wall.side],
				line.tx_x, line.tx_y);
		put_pxl_color(&data->img, x, line.y, line.color);
	}
}

void	draw_door(t_cub3d *data, int x, t_ray *r, t_hit *door)
{
	t_line	line;
	double	wall_x;

	ft_memset(&line, 0, sizeof(line));
	line.y_start = data->win_half_h - door->h * 0.5;
	if (line.y_start < 0)
		line.y_start = 0;
	line.y_end = data->win_half_h + door->h * 0.5;
	if (line.y_end > WIN_H)
		line.y_end = WIN_H -1;
	line.y = line.y_start;
	wall_x = get_wall_x(data, r, door);
	if (door->h != 0)
		line.span = (double)data->wall[door->tex].h / door->h;
	line.tx_x = (int)(wall_x * (double)data->wall[door->tex].w);
	if (door->h > WIN_H)
		line.tx_start_y = (door->h - WIN_H) * 0.5;
	while (++line.y < line.y_end)
	{
		line.tx_y = (int)(((double)line.y - (double)line.y_start
					+ line.tx_start_y) * line.span);
		line.color = get_txcolor(&data->wall[door->tex], line.tx_x, line.tx_y);
		if (line.color && line.color != 0x000000)
			put_pxl_color(&data->img, x, line.y, line.color);
	}
}

void	draw_anim_door(t_cub3d *data, int x, t_ray *r, t_xpm_img *tex)
{
	t_line	line;
	double	wall_x;

	ft_memset(&line, 0, sizeof(line));
	line.y_start = data->win_half_h - r->anim_d.h * 0.5;
	if (line.y_start < 0)
		line.y_start = 0;
	line.y_end = data->win_half_h + r->anim_d.h * 0.5;
	if (line.y_end > WIN_H)
		line.y_end = WIN_H -1;
	line.y = line.y_start;
	wall_x = get_wall_x(data, r, &r->anim_d);
	if (r->anim_d.h != 0)
		line.span = (double)tex->h / r->anim_d.h;
	line.tx_x = (int)(wall_x * (double)tex->w);
	if (r->anim_d.h > WIN_H)
		line.tx_start_y = (r->anim_d.h - WIN_H) * 0.5;
	while (++line.y < line.y_end)
	{
		line.tx_y = (int)(((double)line.y - (double)line.y_start
					+ line.tx_start_y) * line.span);
		line.color = get_txcolor(tex, line.tx_x, line.tx_y);
		if (line.color && line.color != 0x000000)
			put_pxl_color(&data->img, x, line.y, line.color);
	}
}

static double	get_wall_x(t_cub3d *data, t_ray *ray, t_hit *sprite)
{
	double	wall_x;

	if (sprite->side == WE)
		wall_x = data->player.pos.y + sprite->dist * ray->dir.y;
	else if (sprite->side == EA)
		wall_x = data->wall[sprite->tex].w
			- (data->player.pos.y + sprite->dist * ray->dir.y);
	else if (sprite->side == SO)
		wall_x = data->player.pos.x + sprite->dist * ray->dir.x;
	else
		wall_x = data->wall[sprite->tex].w
			- (data->player.pos.x + sprite->dist * ray->dir.x);
	wall_x -= floor(wall_x);
	return (wall_x);
}
