/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 08:09:43 by yusengok          #+#    #+#             */
/*   Updated: 2024/05/29 15:49:58 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*===== libraries ============================================================*/
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <errno.h>
# include "libft.h"
# include "mlx.h"

/*===== math definition ======================================================*/
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

/*===== macro definition =====================================================*/
# define WINNAME "cub3D"
# define WIN_W 1280
# define WIN_H 720
# define TEXTURE_SIZE 64

# ifndef FOV
#  define FOV 60
# endif
// # define MOVE_SPEED 
// # define ROTATE_SPEED

/*===== keysym definition ====================================================*/
# define ESC 53
# define LEFT 123
# define RIGHT 124
# define KEY_A 0
# define KEY_D 2
# define KEY_S 1
# define KEY_W 13

/*===== enum definition =====================================================*/
enum	e_direction
{
	N = 90,
	E = 0,
	S = 270,
	W = 180
};

enum	e_wallside
{
	NO = 0,
	SO = 1,
	WE = 2,
	EA = 3
};

/*===== structures ===========================================================*/
typedef struct s_imgdata
{
	void	*img;
	char	*addr;
	int		bits_per_pxl;
	int		line_len;
	int		endian;
}				t_imgdata;

typedef struct s_map
{
	char	**mapdata;
}				t_map;

typedef struct s_player
{
	double				fov; // FOV in radians
	int					pos_x;
	int					pos_y;
	enum e_direction	initial_dir;
	double				dir; //direction in degree
	double				dir_x; 
	double				dir_y;
	double				plane_length;
	double				plane_x;
	double				plane_y;

}				t_player;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}				t_color;

typedef struct s_ray
{
	// double	angle_rad; // initialize: player.angle - FOV * M_PI / 180
	// double			inc_angle; // = FOV / WIN_W
	double			camera_p;
	double			dir_x;
	double			dir_y;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	double			sidedist_x;
	double			sidedist_y;
	double			delta_x;
	double			delta_y;
	// double			inc_x;
	// double			inc_y;
	// double			x_distance;
	// double			y_distance;
	double			distance;
	int				wall_height;
	enum e_wallside	wall_side;
}				t_ray;

typedef struct s_cub3d
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_imgdata	img;
	t_map		map;
	t_player	player;
	t_color		ceiling;
	t_color		floor;
	// textures
	//--- For TEST -----------
	t_color			colors[4];
	//------------------------
}				t_cub3d;

/*===== functions ============================================================*/
/*----- Ray casting -----*/
int		ft_raycasting(t_cub3d *data);

/*----- Image rendering -----*/
int		render_image(t_cub3d *data);
void	draw_floor(t_cub3d *data, int start, int end, int floor_color);
void	draw_wall(t_cub3d *data, int x, t_ray *ray); // Temporary version without texture
void	draw_ceiling(t_cub3d *data, int x, int end, int ceiling_color);
int		convert_color(t_color color);
void	put_pxl_color(t_imgdata *img, int x, int y, int color);

/*----- Event handler -----*/
int		handle_keyevents(int keysym, t_cub3d *data);
int		handle_mouseevents(int mousecode, int x, int y);
int		handle_closebutton(t_cub3d *data);

/*----- Error handling -----*/
void	ft_perror_exit(char *message, int code);
void	ft_error_exit(char *message, int code);

#endif
