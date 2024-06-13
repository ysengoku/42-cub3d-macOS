# 42-cub3d

## Usage
```bash
# Mandatory part
> make
> ./cub3D <path to map in .xpm format>

# Bonus part
> make bonus
> ./cub3D_bonus <path to map in .xpm format>
```

## Structures

### < Data >
```c
typedef struct s_cub3d
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_imgdata	img;
	t_map		map;
	t_player	player;
	int		ceiling_color;
	int		floor_color;
	t_xpm_img	wall[4]; // wall textures
	int		key_pressed_left; // flag for key event (press & release)
	int		key_pressed_right; // flag for key event (press & release)
	int		key_pressed_w; // flag for key event (press & release)
	int		key_pressed_s; // flag for key event (press & release)
	int		key_pressed_a; // flag for key event (press & release)
	int		key_pressed_d; // flag for key event (press & release)
	int		previous_mouse_x; // x-coordinate of mouse pointer (to handle mouse move)
	t_minimap	mmap;
}				t_cub3d;
```

### < Map >
```c
typedef struct s_map
{
	char			**data_map;
	char			**map; // will be used to check wall collision
	char			**dup_map;
	char			player;
	int			f_rgb[3]; // floor color
	int			c_rgb[3]; // ceiling color
	int			map_len_x; // max length of x-axis of the map
	int			map_len_y; // max length of y-axis of the map
	int			pos_x; // player's initial position
	int			pos_y; // player's initial position
	enum e_direction	p_dir; // player's initial direction
}				t_map;
```
```c
/* Exemple map */
111111
100101
101001
1100N1
111111

// Player is represented by N : cordinates (4, 3), face to north
// N = North (270°)
// E = East (0°)
// S = South (90°)
// W = West (180°)
```

### < Player >
```c
#define FOV 60
#define M_PI 3.14159265358979323846

ypedef struct s_player
{
	double	fov; // FOV in radians (calculate with FOV° * M_PI / 180.0)
	double	pos_x; // X coordinate on the map
	double	pos_y; // Y coordinate on the map
	double	dir; // direction in degree
	double	dir_x; // direction vector of player
	double	dir_y; // direction vector of player
	double	plane_length;
	double	plane_x;
	double	plane_y;
	int	moved; // Flag to signal player's movement

}		t_player;
```

#### Direction vector (dir_x, dir_y)

```c
t_player	player;
double 		dir_rad;

dir_rad = player.dir * M_PI / 180;
player.dir_x = cos(dir_rad);
player.dir_y = sin(dir_rad);

// In the exemple,  
// dir_x = 0, dir_y = -1
```

#### Camera plane
1. Plane length   
   Plane length determinates the field of view of the camera.   
  `plane_length = tan(fov_radians / 2)`
2. Plane vector (plane_x, plane_y)   
   It is a vector perpendicular to the direction vector (dir_x, dir_y).   
  `plane_x = dir_y * plane_length`   
  `plane_y = dir_x * plane_length`
```c
// In the example,
plane_length = tan(fov / 2) = 1.000000

// The plane_x and plane_y for the initial player's position (dir_x = 0, dir_y = -1) is:
plane_x = -dir_y * plane_length = -1 * 1.000000 = -1.000000
plane_y = dir_x * plane_length = 0 * 1.000000 = 0
```

### < Ray >
In raycasting, each vertical stripe on the screen corresponds to a ray cast.   
```c
enum	e_wallside
{
	NO = 0,
	SO = 1,
	WE = 2,
	EA = 3
};

typedef struct s_ray
{
	double		camera_p; // current X coordinate in camera space
	double		dir_x; // direction vector of ray
	double		dir_y; // direction vector of ray
	int		map_x; // current X coordinate of the ray on the map
	int		map_y; // current Y coordinate of the ray on the map
	int		step_x; // direction to go in x-axis (-1 or 1)
	int		step_y; // direction to go in y-axis (-1 or 1)
	double		sidedist_x; // distance the ray travels on x-axis
	double		sidedist_y; // distance the ray travels on y-axis
	double		delta_x; // distance the ray has to travel to go from a x-side to the next one
	double		delta_y; // distance the ray has to travel to go from a y-side to the next one
	double		distance; // distance from the player position to wall
	int		wall_height; // will be calculated from 'distance'
	enum e_wallside	wall_side; // wall side to which the ray hits (the player sees)
}	t_ray;
```
#### camera_p   
X-coordinate of the current ray position, ranging from `0 (left most pixel)` to `WINDOW_WIDTH - 1 (right most pixel)`.  
```
ray.camera_p = 2 * x / (double)WIN_W - 1
```   

#### dir_x, dir_y
Direction vector of ray   
```
ray.dir_x = player.dir_x + player.plane_x * ray.camera_p;   
ray.dir_y = player.dir_y + player.plane_y * ray.camera_p;   
```

#### map_x, map_y
Current coordinate of ray on the map   
We initialize to player's coordinate on the map and will move during raycasting to check wall collision.
```
ray.map_x = (int)player.pos_x;   
ray.map_y = (int)player.pos_y;   
```

#### step_x, step_y & sidedist_x, sidedist_y
* step_x, step_y      
Direction to which the ray goes in x-axis or y-axis. Defined to -1 or 1.
   
* sidedist_x, sidedist_y   
Distance the ray travals on x-axis or y-axis.   
Before starting raycasting loop, it is initially the distance from its start position to the first x-side and the first y-side.   
It will be incremented until the ray hits to wall.

```
# For x-axis
if (ray->dir_x < 0)
{
	ray->step_x = -1;
	ray->sidedist_x = (player->pos_x - ray->map_x) * ray->delta_x;
}
else
{
	ray->step_x = 1;
	ray->sidedist_x = (ray->map_x + 1.0 - player->pos_x) * ray->delta_x;
}

# For y-axis
if (ray->dir_y < 0)
{
	ray->step_y = -1;
	ray->sidedist_y = (player->pos_y - ray->map_y) * ray->delta_y;
}
else
{
	ray->step_y = 1;
	ray->sidedist_y = (ray->map_y + 1.0 - player->pos_y) * ray->delta_y;
}
```   

#### delta_x, delta_y
Distance to the next vertical or horizontal grid line that the ray intersects.  
```
ray.delta_x = fabs(1 / ray->dir_x);
ray.delta_y = fabs(1 / ray->dir_y);
```   

## References
### Tutorials
* [Lode's Computer Graphics Tutorial - Raycasting](https://lodev.org/cgtutor/raycasting.html)
* [cub3d - HackMD](https://hackmd.io/@nszl/H1LXByIE2)
* [Cub3D Tutorial - Using angles](https://medium.com/@afatir.ahmedfatir/cub3d-tutorial-af5dd31d2fcf)
* [42 Docs - cub3d](https://harm-smits.github.io/42docs/projects/cub3d)
* [Algorithme_Cub3D](https://github.com/Qpupier/Cub3D/blob/master/Algorithme_Cub3D.pdf)

### Videos
* [Make Your Own Raycaster Part 1](https://youtu.be/gYRrGTC7GtA?si=7KRnt_PSqn4lz4DD)
* [Make Your Own Raycaster Part 2](https://youtu.be/PC1RaETIx3Y?si=7rDwE_DvbRc79vQm)
* [Make Your Own Raycaster Part 3](https://youtu.be/w0Bm4IA-Ii8?si=aKqqxShLYT1G48O2)
* [Super Fast Ray Casting in Tiled Worlds using DDA](https://youtu.be/NbSee-XM7WA?si=HxCH4AbdRUjJhC7v)
* [Making my First RAYCASTING Game in C++ - SFML Gamedev - Devlog 1](https://youtu.be/LUYxLjic0Bc?si=18f9-hw6lV903EaB)

### Turorial in Japanese
* [42Tokyo C言語で一人称視点のゲームを作った](https://qiita.com/susasaki/items/c74a228d7ddd48b818bd)
