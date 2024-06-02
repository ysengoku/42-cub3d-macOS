
#include "cub3d.h"

void	close_window(t_cub3d *data)
{
	int	i;

	mlx_destroy_image(data->mlx_ptr, data->img.img);
	i = 3;
	while (i > 0)
		mlx_destroy_image(data->mlx_ptr, data->textures[i--].img);
	while (i < 4)
		free(data->textures[i++].path);
	if (BONUS)
	{
		mlx_destroy_image(data->mlx_ptr, data->mmap.img.img);
		mlx_destroy_image(data->mlx_ptr, data->mmap.floor.img);
		mlx_destroy_image(data->mlx_ptr, data->mmap.player.img);
		mlx_destroy_image(data->mlx_ptr, data->mmap.wall.img);
	}
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free(data->mlx_ptr);
	// free other things if needed
	exit(0);
	/*== For test =============================*/
	for (int i = 0; data->map.mapdata[i]; i++)
		free(data->map.mapdata[i]);
	free(data->map.mapdata);
	/*=========================================*/
}

int	handle_closebutton(t_cub3d *data)
{
	close_window(data);
	return (0);
}
