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
# define WIN_W 960
# define WIN_H 720
# define TEX_SIZE 64

# ifndef FOV
#  define FOV 90
# endif
# define MOVE 1
# define ROTATE 5

# define MMAP_SCALE	8
# define MMAP_WALL (int)0x006064
# define MMAP_FLOOR (int)0xB0BEC5
# define MMAP_P (int)0xC51162
# define MMAP_DIR (int)0xD50000
# define MMAP_SPACE (int)0xE3F2FD
# define MMAP_F "./textures/minimap/floor.xpm"
# define MMAP_PL "./textures/minimap/player.xpm"
# define MMAP_WL "./textures/minimap/wall.xpm"

# ifndef BONUS
#  define BONUS 1
# endif

/*===== keysym definition ====================================================*/
# define ESC 53
# define LEFT 123
# define RIGHT 124
# define KEY_A 0
# define KEY_D 2
# define KEY_S 1
# define KEY_W 13
# define KeyPress 2
# define KeyRelease 3
# define KeyPressMask (1L<<0)
# define KeyReleaseMask (1L<<1)
# define DestroyNotify 17
# define StructureNotifyMask (1L<<17)

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

typedef struct 	s_xpm_img
{
	void		*img;
	char		*addr;
	int			bits_per_pxl;
	int			line_len;
	int			endian;
    int			w;
    int			h;
}				t_xpm_img;

typedef struct s_map
{
	char	**mapdata;
	int		maxh;
	int		maxw;
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
	int					moved;
}				t_player;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}				t_color;

typedef struct s_ray
{
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
	double			distance;
	int				wall_height;
	enum e_wallside	wall_side;
}				t_ray;

typedef struct s_line
{
	int	y;
	int	y_start;
	int	y_end;
	int	tex_x;
	int	tex_y;
	int	span;
}				t_line;

typedef struct s_minimap
{
	t_imgdata	img;
	int			minimap_x;
	int			minimap_y;
	t_xpm_img	floor;
	t_xpm_img	player;
	t_xpm_img	wall;
}				t_minimap;

typedef struct s_cub3d
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_imgdata	img;
	t_map		map;
	t_player	player;
	t_color		ceiling;
	int			ceiling_color;
	t_color		floor;
	int			floor_color;
	// t_imgdata	textures[4];
	t_xpm_img	textures[4];
	//--- For TEST -----------
	int			colors[4];
	//------------------------
	int			key_pressed_left;
	int			key_pressed_right;
	t_minimap	mmap;
}				t_cub3d;

/*===== functions ============================================================*/
/*----- Ray casting -----*/
int		ft_raycasting(t_cub3d *data);
void	check_wall_hit(t_cub3d *data, t_ray *ray);

/*----- Image rendering -----*/
int		game_loop(t_cub3d *data);
void	draw_floor(t_cub3d *data, int start, int end, int floor_color);
void	draw_wall_tmp(t_cub3d *data, int x, t_ray *ray); // Temporary version without texture
void	draw_ceiling(t_cub3d *data, int x, int end, int ceiling_color);
int		convert_color(t_color color);
void	put_pxl_color(t_imgdata *img, int x, int y, int color);

/*----- Event handler -----*/
int		handle_keyevents(int keysym, t_cub3d *data);
int		handle_keypress(int keysym, t_cub3d *data);
int		handle_keyrelease(int keysym, t_cub3d *data);
// int		handle_mouseevents(int mousecode, int x, int y, t_cub3d *data);
int 	handle_mousemove(int x, int y, t_cub3d *data);
int		handle_closebutton(t_cub3d *data);
void	close_window(t_cub3d *data);
void	move_forward(t_cub3d *data, double player_dir, int *x, int *y);
void	move_backward(t_cub3d *data, double player_dir, int *x, int *y);
void	move_right(t_cub3d *data, double player_dir, int *x, int *y);
void	move_left(t_cub3d *data, double player_dir, int *x, int *y);
void	move_north_east(t_cub3d *data, int *x, int *y);
void	move_north_west(t_cub3d *data, int *x, int *y);
void	move_south_east(t_cub3d *data, int *x, int *y);
void	move_south_west(t_cub3d *data, int *x, int *y);
void	rotate_counterclockwise(t_cub3d *data);
void	rotate_clockwise(t_cub3d *data);

/*----- Error handling -----*/
void	ft_perror_exit(char *message, int code);
void	ft_error_exit(char *message, int code);

/*----- Minimap -----*/
void	set_minimap(t_cub3d *data);

#endif
