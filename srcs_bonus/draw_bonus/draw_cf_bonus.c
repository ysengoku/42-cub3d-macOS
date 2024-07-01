#include "cub3d.h"

void draw_ceiling_and_floor_bonus(t_cub3d *data, int x, t_ray *ray)
{
    double		current_dist;
	t_vector	position;
	t_line 		line;

	ft_memset(&line, 0, sizeof(line));
    while (++line.y < data->win_half_h)
    {
        current_dist = (double)data->win_half_h / (data->win_half_h - line.y);
        position.x = data->player.pos.x + current_dist * ray->dir.x;
        position.y = data->player.pos.y + current_dist * ray->dir.y;
        line.tx_x = (int)(position.x * data->wall[CE].w) % data->wall[CE].w;
        line.tx_y = (int)(position.y * data->wall[CE].h) % data->wall[CE].h;
        line.color = get_txcolor(&data->wall[CE], line.tx_x, line.tx_y);
        put_pxl_color(&data->img, x, line.y, line.color);
	}
    while (++line.y < WIN_H)
    {
        current_dist = (double)data->win_half_h / (line.y - data->win_half_h);
        position.x = data->player.pos.x + current_dist * ray->dir.x;
        position.y = data->player.pos.y + current_dist * ray->dir.y;
        line.tx_x = (int)(position.x * data->wall[FL].w) % data->wall[FL].w;
        line.tx_y = (int)(position.y * data->wall[FL].h) % data->wall[FL].h;
        line.color = get_txcolor(&data->wall[FL], line.tx_x, line.tx_y);
        put_pxl_color(&data->img, x, line.y, line.color);
	}
}

/* 
Code explanation:
	// Calculate the perceived distance from the player to the ceiling pixel. This uses the screen's half height and the current y-coordinate to simulate perspective.
    	current_dist = (double)data->win_half_h / (data->win_half_h - line.y);

	// Calculate the position of the ceiling pixel in the world. This uses the player's position and the distance calculated above.
        position.x = data->player.pos.x + current_dist * ray->dir.x;
        position.y = data->player.pos.y + current_dist * ray->dir.y;

	// Calculate the texture coordinates of the ceiling pixel. This uses the position calculated above and the dimensions of the ceiling texture.
        line.tx_x = (int)(position.x * data->wall[CE].w) % data->wall[CE].w;
        line.tx_y = (int)(position.y * data->wall[CE].h) % data->wall[CE].h;
*/
