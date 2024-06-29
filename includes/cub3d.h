/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 08:09:43 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/05 16:11:23 by yusengok         ###   ########.fr       */
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
# include <stdbool.h>
# include "libft.h"
# include "mlx.h"

/*===== paths sprits ======================================================*/
# define SPRITE_NO "./path_to_the_north_texture"
# define SPRITE_SO "./path_to_the_south_texture"
# define SPRITE_WE "./path_to_the_west_texture"
# define SPRITE_EA "./path_to_the_east_texture"

/*===== colors ======================================================*/
# define RGB_F "169,169,169"
# define RGB_C "52,52,52"

/*===== math definition ======================================================*/
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# define TWO_PI 6.28318530717958647692

/*===== macro definition =====================================================*/
# define WINNAME "cub3D"
# define WIN_W 960
# define WIN_H 720

# ifndef FOV
#  define FOV 90
# endif
# define MOVE 0.1
# define ROTATE 0.03
/*+++++ BONUS ++++++++++++++++++++++++++++++++++++++++++++++*/
# define MINI_MAP_W 100
# define MINI_MAP_H 100

# define MOUSE_DOWN 4
# define MOUSE_UP 5

# define MMAP_SCALE 20
# define MMAP_SIZE 9
# define MMAP_BORDER 1
# define MMAP_EMPTY 0
# define MMAP_WALL 4868682
# define MMAP_FLOOR 13816530
# define MMAP_P 12915042
# define MMAP_DIR 13959168
# define MMAP_RAY 16776623
# define MMAP_SPACE 11977418
# define MMAP_DOOR 9868950

# define DOOR_TEX_CLOSE "./assets/texture/door/door.xpm"
# define DOOR_TEX1 "./assets/texture/door/door1.xpm"
# define DOOR_TEX2 "./assets/texture/door/door2.xpm"
# define DOOR_TEX3 "./assets/texture/door/door3.xpm"
# define DOOR_TEX4 "./assets/texture/door/door4.xpm"
# define DOOR_TEX5 "./assets/texture/door/door5.xpm"
# define DOOR_TEX_OPEN "./assets/texture/door/door6.xpm"

# define TREASURE_TEX "./assets/texture/pikachu.xpm"
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

# ifndef BONUS
#  define BONUS 1
# endif

/*===== keysym definition ====================================================*/
# define XK_Escape 53
# define XK_Left 123
# define XK_Right 124
# define XK_a 0
# define XK_d 2
# define XK_s 1
# define XK_w 13
# define XK_e 14
# define XK_x 7
# define KeyPress 2
# define KeyRelease 3
# define KeyPressMask (1L<<0)
# define KeyReleaseMask (1L<<1)
# define MotionNotify 6
# define PointerMotionMask (1L<<6)
# define DestroyNotify 17
# define StructureNotifyMask (1L<<17)
# define MOUSE_DOWN 4
# define MOUSE_UP 5

/*===== enum definition =====================================================*/
enum	e_direction
{
	N = 270,
	E = 0,
	S = 90,
	W = 180
};

enum	e_wallside
{
	NO,
	SO,
	WE,
	EA,
	DR_C,
	DR1,
	DR2,
	DR3,
	DR4,
	DR5,
	DR_O,
	TR
};

/*===== structures ===========================================================*/
typedef struct s_vector
{
	double	x;
	double	y;
}				t_vector;

typedef struct s_imgdata
{
	void	*img;
	char	*addr;
	int		bits_per_pxl;
	int		line_len;
	int		endian;
}				t_imgdata;

typedef struct s_xpm_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			w;
	int			h;
	char		*path;
}				t_xpm_img;

typedef struct s_check_map
{
	int						limit_recursiv;
	int						x;
	int						y;
	int						nbr_data;
	int						player;
	int						treasure;
	bool					catch_treasure;
	bool					invalid_map;
	bool					in_map;
	bool					so;
	bool					no;
	bool					we;
	bool					ea;
	bool					f;
	bool					c;
}	t_check_map;

typedef struct s_map
{
	t_check_map			check;
	char				**data_map;
	char				**map;
	char				**dup_map;
	char				player;
	int					f_rgb[3];
	int					c_rgb[3];
	int					map_len_x;
	int					map_len_y;
	int					pos_x;
	int					pos_y;
	enum e_direction	p_dir;
}				t_map;

typedef struct s_player
{
	double				fov;
	t_vector			pos;
	t_vector			start_pos;	
	double				dir_rad;
	t_vector			dir;
	double				plane_length;
	t_vector			plane;
}				t_player;

typedef struct s_hit
{
	int				hit;
	double			dist;
	int				h;
	enum e_wallside	side;
	enum e_wallside	tex;
}				t_hit;

typedef struct s_ray
{
	double		current_camera_x;
	t_vector	dir;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	t_vector	sidedist;
	t_vector	delta;
	t_hit		wall;
	t_hit		closed_d;
	t_hit		open_d;
	t_hit		anim_d;
	double		nearest_sprite_dist;
}			t_ray;

typedef struct s_line
{
	int		y;
	int		y_start;
	int		y_end;
	int		tx_x;
	int		tx_y;
	double	tx_start_y;
	double	span;
	int		color;
}				t_line;

typedef struct s_minimap
{
	t_imgdata	img;
	int			minimap_x;
	int			minimap_y;
	int			totalsize;
}				t_minimap;

typedef struct s_keys
{
	int			key_pressed_left;
	int			key_pressed_right;
	int			key_pressed_w;
	int			key_pressed_s;
	int			key_pressed_a;
	int			key_pressed_d;
	int			key_pressed_m;
	/*++++++ Bonus +++++++++++++++++++*/
	int			key_pressed_x;
	/*++++++++++++++++++++++++++++++++*/
}	t_keys;

typedef struct s_treasure
{
	t_vector	map;
	t_vector	relative_pos;
	t_vector	camera;
	int			screen_x;
	int			draw_height;
	int			draw_width;
	int			start_x;
	int			end_x;
	int			start_y;
	int			end_y;
	int			visible;
}				t_treasure;

typedef struct s_cub3d
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			win_half_w;
	int			win_half_h;
	t_imgdata	img;
	t_map		map;
	t_player	player;
	int			ceiling_color;
	int			floor_color;
	t_xpm_img	wall[12];
	t_keys		keys;
	/*++++++ Bonus +++++++++++++++++++*/
	int			previous_mouse_x;
	t_minimap	mmap;
	bool		anim_open;
	bool		anim_close;
	bool		anim;
	int			animation;
	t_treasure	treasure;
	double		wall_zbuffer[WIN_W];
	/*+++++++++++++++++++++++++++++++++*/
}				t_cub3d;

/*===== functions ============================================================*/

/*----- Parsing -----*/
int				parsing(char *file, t_cub3d *map);
char			**get_file(t_cub3d *data, char *file);
int				get_data(t_cub3d *data);
int				get_sprites_path(t_cub3d *map);
int				get_colors_rgb(t_cub3d *data);
int				get_maps(t_cub3d *data);
int				check_map(t_cub3d *data);
int				check_file(t_cub3d *data);
int				line_is_map(char *line, char c);
int				line_is_data(char *line);
int				line_is_space(char *line);
int				apply_flood_fill(t_cub3d *data);
void			flood_fill_rec(t_cub3d *data, char **dup_map, int pos_x,
					int pos_y);
void			flood_fill_iter(t_cub3d *data, char **dup_map);
void			free_split(char **map);
void			free_data_map(t_map *data_map);
int				exit_parsing(t_cub3d *data, char *message, bool perror_msg);
void			set_data(t_cub3d *data, t_player *player, t_map *map);
int				set_wall_texture(t_cub3d *data, t_xpm_img *wall);

/*----- Ray casting -----*/
int				display(t_cub3d *data);
void			raycasting(t_cub3d *data, int x, t_xpm_img *door);
void			check_hit(t_cub3d *data, t_ray *ray);

/*----- Image rendering -----*/
int				game_loop(t_cub3d *data);
void			draw_wall(t_cub3d *data, int x, t_ray *ray);
void			draw_ceiling_and_floor(t_cub3d *data, int x);
void			draw_minimap(t_cub3d *data);
void			draw_minimap_zone(t_cub3d *data, int size);
int				convert_color(int rgb[3]);
unsigned int	get_txcolor(t_xpm_img *texture, int x, int y);
void			put_pxl_color(t_imgdata *img, int x, int y, int color);

/*----- Event handler -----*/
int				keypress(int keysym, t_cub3d *data);
int				keyrelease(int keysym, t_cub3d *data);
int				closebutton(t_cub3d *data);
void			close_window(t_cub3d *data);
void			move_forward(t_cub3d *data, t_player *player, t_map *map);
void			move_backward(t_cub3d *data, t_player *player, t_map *map);
void			move_right(t_cub3d *data, t_player *player, t_map *map);
void			move_left(t_cub3d *data, t_player *player, t_map *map);
void			rotate_counterclockwise(t_cub3d *data);
void			rotate_clockwise(t_cub3d *data);

/*----- Error handling & free -----*/
void			ft_perror_exit(char *message, int code);
void			ft_error_exit(char *message, int code);
int				free_all(t_cub3d *data, int status);
void			free_texture_paths(t_xpm_img *wall, int size);
void			clear_data(t_cub3d *data);
void			clear_texture_img(t_cub3d *data);

/*===== bonus part functions =================================================*/

/*----- Minimap -----*/
int				create_minimap_img(t_cub3d *data, t_minimap *mmap);
void			draw_mmap_player_dir(t_cub3d *data);
void			draw_ray_mmap(t_cub3d *data, t_ray *ray);
void			draw_scales(t_cub3d *data, int *cam_x, int *cam_y);
void			draw_player(t_cub3d *data, int xc, int yc, int r);

/*----- Event -----*/
int				mousemove(int x, int y, t_cub3d *data);
void			action_event(t_cub3d *data);

/*----- Doors -----*/
int				get_door_and_treasure_texture_paths(t_cub3d *data);
void			draw_door(t_cub3d *data, int x, t_ray *r, t_hit *door);
void			draw_anim_door(t_cub3d *data, int x, t_ray *r, t_xpm_img *tex);
void			animations(t_cub3d *data);
void			anim_door(t_cub3d *data, int target_y, int target_x);

/*----- Treasures -----*/
void			set_treasure_data(t_cub3d *data, t_treasure *treasures);
void			draw_treasure(t_cub3d *data, t_treasure *treasure, int x);

#endif
