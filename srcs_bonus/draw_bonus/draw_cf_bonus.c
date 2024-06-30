#include "cub3d.h"

static void draw_ceiling(t_cub3d *data, int x, double camerax, t_vector raydir);
static void	draw_floor(t_cub3d *data, int x, double camerax, t_vector raydir);

void	draw_ceiling_and_floor_bonus(t_cub3d *data)
{
	int			x;
//	t_vector	scale;
	double		camerax;
	t_vector	raydir;

//	scale.x = (double)WIN_W / data->wall[CE].w;
//	scale.y = (double)data->win_half_h / data->wall[CE].h;
	x = -1;
	while (++x < WIN_W)
	{
    	camerax = 2 * x / (double)WIN_W - 1;
		raydir.x = data->player.dir.x + data->player.plane.x * camerax;
		raydir.y = data->player.dir.y + data->player.plane.y * camerax;
		draw_ceiling(data, x, camerax, raydir);
		draw_floor(data, x, camerax, raydir);
	}
}
/*
static void	draw_ceiling(t_cub3d *data, int x, t_vector scale)
{
	int tx;
	int ty;
	int color;
	int	y;

	y = -1;
	while (++y < data->win_half_h)
	{
		tx = (int)((double)x / WIN_W * data->wall[CE].w * scale.x);
		ty = (int)((double)y / data->win_half_h * data->wall[CE].h * scale.y);
		color = get_txcolor(&data->wall[CE], tx, ty);
		put_pxl_color(&data->img, x, y, color);
	}
}
*/

static void draw_ceiling(t_cub3d *data, int x, double camerax, t_vector raydir)
{
    double		current_dist;
	t_vector	ceiling_pos;
	t_line 		line;

	ft_memset(&line, 0, sizeof(line));
	line.y = 0;
    while (++line.y < data->win_half_h)
    {
        current_dist = (double)data->win_half_h / (data->win_half_h - line.y);
        ceiling_pos.x = data->player.pos.x + current_dist * raydir.x;
        ceiling_pos.y = data->player.pos.y + current_dist * raydir.y;
        line.tx_x = (int)(ceiling_pos.x * data->wall[CE].w) % data->wall[CE].w;
        line.tx_y = (int)(ceiling_pos.y * data->wall[CE].h) % data->wall[CE].h;
        line.color = get_txcolor(&data->wall[CE], line.tx_x, line.tx_y);
        put_pxl_color(&data->img, x, line.y, line.color);
	}
}

static void draw_floor(t_cub3d *data, int x, double camerax, t_vector raydir)
{
    double		current_dist;
	t_vector	ceiling_pos;
	t_line 		line;

	ft_memset(&line, 0, sizeof(line));
	line.y = data->win_half_h - 1;
    while (++line.y < WIN_H)
    {
        current_dist = (double)data->win_half_h / (line.y - data->win_half_h);
        ceiling_pos.x = data->player.pos.x + current_dist * raydir.x;
        ceiling_pos.y = data->player.pos.y + current_dist * raydir.y;
        line.tx_x = (int)(ceiling_pos.x * data->wall[FL].w) % data->wall[FL].w;
        line.tx_y = (int)(ceiling_pos.y * data->wall[FL].h) % data->wall[FL].h;
        line.color = get_txcolor(&data->wall[FL], line.tx_x, line.tx_y);
        put_pxl_color(&data->img, x, line.y, line.color);
	}
}
