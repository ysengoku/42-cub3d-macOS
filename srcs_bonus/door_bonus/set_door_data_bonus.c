
#include "cub3d.h"

void	set_door_texture(t_cub3d *data)
{
	data->wall[DR].path = ft_strdup(DOOR_TEX);
	if (!data->wall[DR].path)
	{
		free_all(data, 1);
		ft_perror_exit("malloc", 1);
	}
	data->wall[DR].img = mlx_xpm_file_to_image(data->mlx_ptr,
		data->wall[DR].path, &data->wall[DR].w, &data->wall[DR].h);
	if (data->wall[DR].img == NULL)
	{
		free(data->wall[DR].path);
		free_all(data, 1);
		ft_perror_exit("MLX", 1);
	}
	data->wall[DR].addr = mlx_get_data_addr(data->wall[DR].img,
		&data->wall[DR].bpp, &data->wall[DR].line_len, &data->wall[DR].endian);
}
