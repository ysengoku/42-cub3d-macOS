# cub3d
This project aims to create a game similar to Wolfenstein 3D using the __raycasting__ technique.  
Raycasting is used to create a 3D effect by casting rays from the player's position to detect sprites(walls, doors, objects, etc.). It allows the game to render a first-person perspective in a 2D game world, making it appear three-dimensional.

## Usage
```bash
# Mandatory part
> make
> ./cub3D <path to map in .xpm format>

# Bonus part
> make bonus
> ./cub3D_bonus <path to map in .xpm format>
```

## Raycasting & rendering overview

We will cast rays from the player's current position in the direction ranging from (player.dir - plane) to (player.dir + plane). The interval at which rays are cast depends on the screen's width in pixels (we cast the same number of rays as the screen's width).

### Raycasting steps:   
1. Ray Initialization   
Start from the player's position and determine the direction the ray is cast based on the player's view.   
   
2. Grid Traversal:   
When casting rays, randomly casting them won't determine which wall they hit.   
Therefore, we use a method called DDA (Digital Differential Analysis) to advance the ray incrementally through the grid, one cell at a time, in both x and y directions.   

3. Intersection Check:   
At each step, check if the ray has hit a wall or sprite in the grid.

4. Stop on Collision:   
When a wall is hit, record the intersection point and stop the ray.   
Calculate the perpendicular distance from the player to the wall. This information is used for rendering.  (If we use the actual distance (euclidean distance), we'll get the fish-eye effect.)   

### Rendering steps:

1. Determine Wall Height:   
Based on the distance to the wall, calculate the height of the wall slice to be drawn on the screen. Closer walls will appear taller, and farther walls will appear shorter.   

2. Render Wall Slice:   
Draw the corresponding vertical slice of the wall at the appropriate position on the screen, using the calculated height.   

3. Texture Mapping:   
If we use textures, calculate which part of the wall texture to display on the slice. This involves determining the exact texture coordinate based on the intersection point.   

   
Repeat the entire process for each ray cast from the player's position.   
After rendering all walls, render additional elements like sprites.

## Structures

### < Data >
```c
typedef struct s_keys
{
	int			key_pressed_left;
	int			key_pressed_right;
	int			key_pressed_w;
	int			key_pressed_s;
	int			key_pressed_a;
	int			key_pressed_d;
	int			key_pressed_m;
	int			key_pressed_x;
}	t_keys;

typedef struct s_cub3d
{
	void		*mlx_ptr;
	void		*win_ptr;
	int		win_half_w; // half width of window
	int		win_half_h; // half height of window
	t_imgdata	img; // main image
	t_map		map;
	t_player	player;
	int		ceiling_color;
	int		floor_color;
	t_xpm_img	wall[12]; // array of wall & door texture
	t_keys		keys; // flags for key event
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
```

### < Map >
```c
typedef struct s_map
{
	char			**data_map;
	char			**map; // used to check wall collision
	char			**dup_map; // used to blood fill
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
#define FOV 90
#define M_PI 3.14159265358979323846

typedef struct s_vector
{
	double	x;
	double	y;
}				t_vector;

typedef struct s_player
{
	double				fov; // FOV in radians (FOV° * M_PI / 180.0)
	t_vector			pos; // player's coordinate on the map
	t_vector			start_pos; // player's coordinate on the map at game start
	double				dir_rad; // player's direction in radians
	t_vector			dir; // player's direction vector
	double				plane_length;
	t_vector			plane;
}				t_player;

```

### < Ray >
In raycasting, each vertical stripe on the screen corresponds to a ray cast.   
```c
enum	e_wallside
{
	NO,
	SO,
	WE,
	EA,
	DR_C, // closed door
	DR1, // opening/closing door frame 1
	DR2, // opening/closing door frame 2
	DR3, // opening/closing door frame 3
	DR4, // opening/closing door frame 4
	DR5, // opening/closing door frame 5
	DR_O, // open door
	TR
};

typedef struct s_hit
{
	int		hit; // if the rays hit the sprite or not
	double		dist; // distance from player to the sprite
	int		h; // height of the sprite
	enum e_wallside	side; // side to which the ray hits (the player sees): North, South, East or West
	enum e_wallside	tex; // texture index of sprite
}				t_hit;

typedef struct s_ray
{
	double		current_camera_x; // current X coordinate in camera space
	t_vector	dir; // direction vector of ray
	int		map_x; // current X coordinate of the ray on the map
	int		map_y; // current Y coordinate of the ray on the map
	int		step_x; // direction to go in x-axis (-1 or 1)
	int		step_y; // direction to go in y-axis (-1 or 1)
	t_vector	sidedist; // distance the ray travels on x-axis or y-axis
	t_vector	delta; // distance the ray has to travel to go from a x-side or y-side to the next one
	t_hit		wall; // wall hit data structure
	t_hit		closed_d; // closed door hit data structure
	t_hit		open_d; // open door hit data structure
	t_hit		anim_d; // animated door (opening or closing) hit data structure
	double		nearest_sprite_dist; // distance from player to the nearest sprite (wall or closed door)
}			t_ray;
```

## Detailed explanation 
```c
int	display(t_cub3d *data, int i)
{
	int	x = 0;

	init_camera(data);
	while (x < WIN_W)
	{
		ft_memset(&ray, 0, sizeof(ray));
		set_ray(data, &ray, x);
		draw_ceiling(data, x, data->win_half_h + data->player.pitch, data->ceiling_color);
		draw_floor(data, x, data->win_half_h + data->player.pitch, data->floor_color);
		check_wall_hit(data, &ray);
		draw_wall(data, x, &ray);
	}
	return (0);
}
```

### Camera initialization
```c
static void	init_camera(t_cub3d *data)
{
	double	direction_rad;

	direction_rad = data->player.dir * M_PI / 180;
	data->player.dir_x = cos(direction_rad);
	data->player.dir_y = sin(direction_rad);
	data->player.plane_x = -data->player.dir_y * data->player.plane_length;
	data->player.plane_y = data->player.dir_x * data->player.plane_length;
}
```
#### 1. Direction vector (dir_x, dir_y)
Player's direction is converted in a vector (x, y).  
It can be used for things like moving the player in the direction they're facing or casting rays in the direction the player is looking.

1. `data->player.dir_x = cos(direction_rad);`:　In a unit circle, the cosine of an angle gives the x-coordinate of a point on the circle.

2. `data->player.dir_y = sin(direction_rad);`:　In a unit circle, the sine of an angle gives the y-coordinate of a point on the circle.

```c
t_player	player;
double 		dir_rad;

dir_rad = player.dir * M_PI / 180;
player.dir_x = cos(dir_rad);
player.dir_y = sin(dir_rad);

// If the player's direction is North (270°)   
// dir_x = 0, dir_y = -1
```
<p align="center"><img style="width: 40%" alt="sin cos" src="https://github.com/ysengoku/42-cub3d-macOS/assets/130462445/5377d587-8097-4f47-8efa-259bbd638dd4"></p>

<p align="center"><img style="width: 80%" alt="player's direction vector" src="https://github.com/ysengoku/42-cub3d-macOS/assets/130462445/5c611b99-584d-4f14-ae39-8da2563c577d"</p>

#### 2. Camera plane
1. Plane length   
   Plane length represents the length of projection plane. The projection plane is where the 3D world is projected onto to create a 2D image. This length affects the field of view.   
  `plane_length = tan(fov_radians / 2)`
2. Plane vector (plane_x, plane_y)   
   It is a vector perpendicular to the direction vector (dir_x, dir_y). This is used to calculate the direction of the rays cast.
   It can be obtained by rotating the player's direction 90 degrees. This rotation can be done by swapping th x and y and changing the sign of new y. So, (x, y) becomes (-y, x) and we need to multiplie it by plane length.  
  `plane_x = -dir_y * plane_length`   
  `plane_y = dir_x * plane_length`
```c
// If FOV is 90°
plane_length = tan(fov / 2) = 1.000000

// If player's direction is　dir_x = 0, dir_y = -1
plane_x = -dir_y * plane_length = (-1 * -1) * 1.000000 = 1.000000
plane_y = dir_x * plane_length = 0 * 1.000000 = 0
```
<p align="center"><img style="width: 30%" src="https://github.com/ysengoku/42-cub3d-macOS/assets/130462445/f9e691b5-c17e-4eed-a810-638977ff8138"></p>

### Ray casting & Drawing loop
#### 1. Ray initialization
```c
enum	e_hit
{
	WALL = 1,
	DOOR = 2,
	NOTHING = 0
};

static void	set_ray(t_cub3d *data, t_ray *ray, int x)
{
	ray->hit = NOTHING;
	ray->w_dist = 0;
	ray->camera_x = 2 * x / (double)WIN_W - 1;
	ray->dir_x = data->player.dir_x + data->player.plane_x * ray->camera_p;
	ray->dir_y = data->player.dir_y + data->player.plane_y * ray->camera_p;
	ray->map_x = (int)data->player.pos_x;
	ray->map_y = (int)data->player.pos_y;
	ray->delta_x = fabs(1 / ray->dir_x);
	ray->delta_y = fabs(1 / ray->dir_y);
	set_sidedist(ray, &data->player);
}
```
##### a. camera_x   
X-coordinate of the current ray position on camera plane, ranging from `0 (left most pixel)` to `WINDOW_WIDTH - 1 (right most pixel)`.  
```
ray.camera_x = 2 * x / (double)WIN_W - 1

// x is current x-coordinate on window ranging from 0 to window width - 1.  
``` 

<p align="center"><img style="width: 50%;" src="https://github.com/ysengoku/42-cub3d-macOS/assets/130462445/72806dad-5230-4ad9-ba1e-1280c5f361da"></p>

##### b. dir_x, dir_y
Direction vector of ray   
```
ray.dir_x = player.dir_x + player.plane_x * ray.camera_p;   
ray.dir_y = player.dir_y + player.plane_y * ray.camera_p;   
```
<p align="center"><img style="width: 50%;" src="https://github.com/ysengoku/42-cub3d-macOS/assets/130462445/6a3fa421-fb03-46b6-8d52-36ab7d6145dd"</p>

##### c. map_x, map_y
Current coordinate of ray on the map   
We initialize to player's coordinate on the map and will move during raycasting to check wall collision.
```
ray.map_x = (int)player.pos_x;   
ray.map_y = (int)player.pos_y;   
```

##### d. delta_x, delta_y / sidedist_x, sidedist_y / step_x, step_y
   
<p align="center"><img style="width: 50%;" alt="delta_x, delta_y / sidedist_x, sidedist_y" src="https://github.com/ysengoku/42-cub3d-macOS/assets/130462445/dea8f7a3-79a3-41e2-9d55-5c12a8ae8750">

* delta_x, delta_y   
Distance to the next vertical or horizontal grid line that the ray intersects.  
   
delta_x and delta_y can be calculated as following:   
```
ray.delta.x = sqrt((ray.dir.x² + ray.dir.y²) / ray.dir.x²)   
ray.delta.y = sqrt((ray.dir.x² + ray.dir.y²) / ray.dir.y²)
```
<p align="center"><img style="width: 80%;" src="https://github.com/ysengoku/42-cub3d-macOS/assets/130462445/48f04ab1-c73f-41c2-a7b9-7d71541bcb6e"></p>

Because the ray is cast in grid-based environment where each grid cell is of size 1x1 (ray always moves one unit in the X or Y direction), we can simplify them like:
```
ray.delta.x = fabs(1 / ray->dir_x)   
ray.delta.y = fabs(1 / ray->dir_y)
``` 

* sidedist_x, sidedist_y   
Distance the ray travels on x-axis or y-axis.   
Before starting raycasting loop, it is initially the distance from its start position to the first x-side and the first y-side.   
It will be incremented until the ray hits to wall.

<p align="center"><img style="width: 80%;" src="https://github.com/ysengoku/42-cub3d-macOS/assets/130462445/8d4b81a2-9700-4f3a-bf65-732647104ca8"></p>


* step_x, step_y      
`step_x` and `step_y` represent the direction of the ray in the x-axis and y-axis respectively. They are set to -1 or 1, indicating that the ray moves one grid unit in the x or y direction at each step.

<p align="center"><img style="width: 30%;" src="https://github.com/ysengoku/42-cub3d-macOS/assets/130462445/78601747-bb24-43c8-a0aa-f0653acc0303"</p>

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
#### 2. Wall (& door for bonus) hit check
The ray continues until it hits a wall (or a closed door), using the DDA (Digital Differential Analyzer) algorithm.   
The DDA algorithm steps through the map grid, moving the ray to the next grid line. When a wall (or a closed door) is hit, the algorithm stops, and the distance to the hit is calculated. This distance is used to determine the height of the wall (or the closed door) slice to be drawn, creating a 3D perspective from a 2D map.

```c
void	check_hit(t_cub3d *data, t_ray *ray)
{
	int		is_y_axis;

	is_y_axis = 0;
	while (!ray->wall.hit && !ray->closed_d.hit)
	{
		// Check if current map coordinates of the ray(data->map.map[ray->map_y][ray->map_x]) is a wall ('1')
		if (data->map.map[ray->map_y][ray->map_x] == '1')
		{
			set_hit_data(data, ray, &ray->wall, is_y_axis);
			if (ray->nearest_sprite_dist == 0)
				ray->nearest_sprite_dist = ray->wall.dist;
		}
		if (BONUS)
			check_door_hit(data, ray, is_y_axis);
		next_step(ray, &is_y_axis);
	}
}

static void	check_door_hit(t_cub3d *data, t_ray *ray, int is_y_axis)
{
	// Check if current map coordinates of the ray is a closed door ('D')
	if (data->map.map[ray->map_y][ray->map_x] == 'D'
		&& !ray->closed_d.hit)
	{
		set_hit_data(data, ray, &ray->closed_d, is_y_axis);
		if (ray->nearest_sprite_dist == 0)
			ray->nearest_sprite_dist = ray->closed_d.dist;
	}

	// Check if current map coordinates of the ray is an open door ('O')
	if (data->map.map[ray->map_y][ray->map_x] == 'O'
		&& !ray->open_d.hit)
		set_hit_data(data, ray, &ray->open_d, is_y_axis);

	// Check if current map coordinates of the ray is an opening or closing door ('d' or 'o')
	if ((data->map.map[ray->map_y][ray->map_x] == 'd'
		|| data->map.map[ray->map_y][ray->map_x] == 'o'))
		set_anim_door_hit_data(data, ray, is_y_axis);
}
```
   
The `next_step` function determines the next grid cell the ray should move to.   
If ray->sidedist.x is smaller, the ray moves one grid cell in the x direction, and the side distance is incremented by ray->delta.x. The is_vertical_side flag is set to 0, indicating a horizontal wall hit will be checking at the next step.   
If ray->sidedist.y is smaller, the ray moves one grid cell in the y direction, and the side distance is incremented by ray->delta.y. The is_vertical_side flag is set to 1, indicating a vertical wall hit will be checking at the next step.

```c
static void	next_step(t_ray *ray, int *is_y_axis)
{
	if (ray->sidedist_x < ray->sidedist_y)
	{
		ray->sidedist_x += ray->delta_x; //the side distance is incremented by ray->delta.x
		ray->map_x += ray->step_x; //the ray moves one grid cell in the X-direction
		*is_y_axis = 0; // x-axis wall hit will be checking
	}
	else
	{
		ray->sidedist_y += ray->delta_y; //the side distance is incremented by ray->delta.y
		ray->map_y += ray->step_y; //the ray moves one grid cell in the Y-direction
		*is_y_axis = 1; // y-axis wall hit will be checking
	}
}
```
<p align="center"><img style="width: 90%;" src="https://github.com/ysengoku/42-cub3d-macOS/assets/130462445/54b67e9a-0a9c-4b9f-ac15-e15375d340a2"></p>

<p align="center"><img style="width: 90%;" src="https://github.com/ysengoku/42-cub3d-macOS/assets/130462445/02958f20-c40a-4d7d-a94c-c9bf464d2bbc"></p>

If the ray hits a sprite (wall, closed door, open door or animated door), we stock the hit side and distance and calculate the height of the line to draw on screen.   

```c
static void	set_hit_data(t_cub3d *data, t_ray *ray, t_hit *sprite, int y_axis)
{
	// set 'hit' to 1(true)
	sprite->hit = 1;

	// Calculate the perpendicular distance from camera plane to the sprite
	if (y_axis)
		sprite->dist = ray->sidedist.y - ray->delta.y;
	else
		sprite->dist = ray->sidedist.x - ray->delta.x;
	if (sprite->dist < 0.0001)
		sprite->dist = 0.0001;

	// Determines which side of a wall the ray has hit 
	if (y_axis && ray->map_y < data->player.pos.y)
		sprite->side = SO;
	else if (y_axis && ray->map_y > data->player.pos.y)
		sprite->side = NO;
	else if (!y_axis && ray->map_x < data->player.pos.x)
		sprite->side = EA;
	else
		sprite->side = WE;

	// Calculate the height of line to draw on screen
	sprite->h = (int)(WIN_H / sprite->dist);
}
```

##### Calculate the perpendicular distance from camera plane to the sprite
The `ray->sidedist.x` and `ray->sidedist.y` values represent the distance the ray has to travel along the x and y axes, respectively, to hit a sprite.   
If the ray has hit on Y-axis grid line, the distance from the player to the sprite is calculated as `ray->sidedist.y - ray->delta.y`.   
If the ray has hit on X-axis grid line, the distance from the player to the wall is calculated as `ray->sidedist.x - ray->delta.x`.   
(Due to how deltaDist and sideDist were scaled by a factor of |rayDir|, the length of sideDist already almost equals perpWallDist.)   

##### Determines which side of a wall the ray has hit   
If the hit is on a vertical wall, it checks whether the ray's y-coordinate on the map is less than the player's y-coordinate. If it is, the function returns NO (North), otherwise it returns SO (South).   
If the hit is not on a vertical wall, it checks whether the ray's x-coordinate on the map is less than the player's x-coordinate. If it is, the function returns WE (West), otherwise it returns EA (East).   

##### Calculate the height of line to draw on screen
The height of the line on the screen is inversely proportional to the distance to the sprite. This means that as the distance to the sprite increases, the height of the line on the screen decreases. Therefore, we calculate the height of the line by dividing the height of the window by the distance to the sprite. This can be represented as `Height of line = Window height / Distance to the sprite`. It ensures that distant sprites appear smaller on the screen, providing a sense of depth and perspective in the game.


#### 3. Draw wall
The function `draw_wall` draws a vertical slice of a wall on the screen. We have same type of functions for closed/open door and animated door.

```c
void	draw_wall(t_cub3d *data, int x, t_ray *r)
{
	t_line	line;
	double	wall_x;

	// Initialize a line structure
	ft_memset(&line, 0, sizeof(line));
	line.y_start = data->win_half_h - r->wall.h * 0.5;
	if (line.y_start < 0)
		line.y_start = 0;
	line.y_end = data->win_half_h + r->wall.h * 0.5;
	if (line.y_end > WIN_H)
		line.y_end = WIN_H -1;
	line.y = line.y_start;

	// Get the exact horizontal position of a wall hit by a ray
	wall_x = get_wall_x(data, r, &r->wall);

	// Calculate span
	if (r->wall.h != 0)
		line.span = (double)data->wall[r->wall.side].h / r->wall.h;

	// Calculate the horizontal position in the texture corresponding to wall_x
	line.tx_x = (int)(wall_x * (double)data->wall[r->wall.side].w);

	// Recalculate the vertical offset in the texture if wall height is grater than window height
	if (r->wall.h > WIN_H)
		line.tx_start_y = (r->wall.h - WIN_H) * 0.5;

	// Draw each pixel in the wall slice
	while (++line.y < line.y_end)
	{
		line.tx_y = (int)(((double)line.y - (double)line.y_start
					+ line.tx_start_y) * line.span);
		line.color = get_txcolor(&data->wall[r->wall.side],
				line.tx_x, line.tx_y);
		put_pxl_color(&data->img, x, line.y, line.color);
	}
}
```

1. Initializes a `line` structure, which represents the vertical line to be drawn on the screen.
The `y_start` and `y_end` values are calculated based on the height of the wall (`r->wall.h`) and the vertical midpoint of the window (`data->win_half_h`).   
These values are clamped to be within the window's height (`WIN_H`).   

2. Get `wall_x` value   
It is calculated by calling the `get_wall_x` function. This value represents the exact horizontal position where a ray hits a wall block, which is used for texture mapping.   

3. Calculate the `span` value is calculated as the ratio of the texture height to the wall height.   
This is used to correctly map the texture to the wall slice.   

4. Calculate the `tx_x` value   
It is the horizontal position in the texture that corresponds to the `wall_x` value.   
This is used to get the correct color from the texture for each pixel in the wall slice.   

5. Recalculate the `tx_start_y` value if the wall height is greater than the window height.   
This is the vertical offset in the texture that corresponds to the top of the wall slice.   

6. Loop to draw each pixel in the wall slice.   
For each pixel, the `tx_y` value is calculated as the vertical position in the texture that corresponds to the current pixel.   
The color of the pixel is then retrieved from the texture using the `get_txcolor` function, and the pixel is drawn on the screen.   
   
##### wall_x
The `wall_x` value represents the exact position where a ray hits a wall block.
This is used to determine which part of the texture to display for that wall slice.

```c
static double	get_wall_x(t_cub3d *data, t_ray *ray, t_hit *sprite)
{
	double	wall_x;

	if (sprite->side == WE)
		wall_x = data->player.pos.y + sprite->dist * ray->dir.y;
	else if (sprite->side == EA)
		wall_x = data->wall[WE].w - (data->player.pos.y + sprite->dist * ray->dir.y);
	else if (sprite->side == SO)
		wall_x = data->player.pos.x + sprite->dist * ray->dir.x;
	else
		wall_x = data->wall[SO].w - (data->player.pos.x + sprite->dist * ray->dir.x);
	if (wall_x != floor(wall_x))
		wall_x -= floor(wall_x);
	else
		wall_x = 1;
	return (wall_x);
}
```
* The wall hit is on the west (`WE`) or east (`EA`)
`wall_x` is calculated using the player's y position, the distance to the wall (`sprite->dist`), and the y direction of the ray (`ray->dir.y`). 
If the wall is on the east, the calculation is inverted by subtracting it from the width of the west wall.

* The wall hit is on the south (`SO`) or north ('NO')
`wall_x` is calculated using the player's x position, the distance to the wall, and the x direction of the ray. 
If the wall is on the north, the calculation is inverted by subtracting it from the width of the south wall.
   
The fractional part is kept by subtracting the floor of `wall_x` from `wall_x`. 
If the fractional part is zero, it is set to 1 to avoid a division by zero error later in the texture mapping process.   

<p align="center"><img style="width: 50%;" src="https://github.com/ysengoku/42-cub3d-macOS/assets/130462445/03aebd3c-dd90-4f07-beaf-e3e2023c0f59"></p>

##### Retrieve the color of the pixel from the texture
```c
typedef struct s_xpm_img
{
	void		*img;
	char		*addr; // memory address of the texture image
	int		bpp; // number of bytes per pixel
	int		line_len; // length of each line of pixels
	int		endian;
	int		w;
	int		h;
	char		*path;
}				t_xpm_img;

unsigned int	get_txcolor(t_xpm_img *texture, int x, int y)
{
	char	*pxl; // pointer to the color data of the specified pixel

	pxl = texture->addr + (y * texture->line_len + x * (texture->bpp / 8));
	return (*(unsigned int *)pxl);
}
```
The `pxl` variable is a pointer to the color data of the specified pixel. It's calculated by adding the offset of the pixel to the start address of the texture. The offset is calculated as `y * texture->line_len + x * (texture->bpp / 8)`, which gives the number of bytes from the start of the texture to the pixel.   

The function returns the color of the pixel as an `unsigned int`. This is done by dereferencing the `pxl` pointer with `(unsigned int *)pxl`. This casts the `pxl` pointer to an `unsigned int` pointer, and then dereferences it to get the `unsigned int` value that it points to, which is the color of the pixel.   


### Sprite draw (perspective projection transformation)
We use another method to draw sprites  (like objects or characters).   
Instead of using Ray casting, it involves calculating the position and size of the 2D image based on the the relative position of the sprite to the player. This determines where and how large the sprite should appear on the screen. Technically, this method is known as perspective projection transformation.

#### Overview
1. During the Raycasting loop, we store the perpendicular distance to the wall or closed door (which is for each ray in an array called `wall_zbuffer`.
2. Convert the coordinates of the sprites from the map coordinates to coordinates relative to the player.
3. By applying the inverse of the camera matrix, we determine the x-coordinate on the screen and the depth of the sprite (Z-axis in 3D space) from the player.
4. Calculate the width and height for rendering the sprite based on the x-coordinate on the screen and the sprite's depth. 
5. For each x-coordinate from the left edge to the right edge of the sprite on the screen, the sprite is drawn. During this process, if the wall_zbuffer[x] value is greater than the sprite's depth (indicating the sprite is closer to the player than the wall), the sprite is rendered.

```c
typedef struct s_treasure
{
	/* map world coordinates */
	t_vector	map; // sprite x and y coodinate on map
	t_vector	relative_pos; // sprite x and y coodinate relative to playeryer

	/* camera coordinates */
	t_vector	camera; // treasure's position relative to the player's perspective
		// X = whether the sprite is to the left or right of the player's viewpoint and by how much.
		// Y = distance(depth, Z-axis in 3D space) of the sprite from player

	/* screen coordinates */
	int		screen_x; // sprite x-coodinate on screen
	int		draw_height; // sprite height on screen
	int		draw_width; // sprite width on screen
	int		start_x; // start x-coodinate to draw sprite
	int		end_x; // end x-coodinate to draw sprite
	int		start_y; //	start y-coodinate to draw sprite
	int		end_y; // end y-coodinate to draw sprite
	int		visible; // whether the sprite is visible or not
}		t_treasure;

void	set_treasure_data(t_cub3d *data, t_treasure *treasure)
{
	treasure->visible = 0;
	calculate_camera_coordinates(data, treasure);
	if (treasure->camera.y > 0 && fabs(treasure->camera.x / treasure->camera.y) < data->player.plane_length)
	{
		get_draw_range(data, treasure);
		treasure->visible = 1;
	}
}

static void	calculate_camera_coordinates(t_cub3d *data, t_treasure *treasure)
{
	double	inverse_matrix_factor;

	// This is a value used to scale these positions based on the player's direction and field of view.
	// The `1.0 /` part is calculating the inverse (or reciprocal) of the value.
	inverse_matrix_factor = 1.0 / (data->player.plane.x * data->player.dir.y - data->player.dir.x * data->player.plane.y);

	// Calculate relative position of sprite to player
	treasure->relative_pos.x = treasure->map.x - data->player.pos.x;
	treasure->relative_pos.y = treasure->map.y - data->player.pos.y;

	// Transform the treasure's position from map world coordinates to camera coordinates.
	//`camera.x` and `camera.y` represent how far the sprite is from the center of the player's field of view, both horizontally and vertically. 
	treasure->camera.x = inverse_matrix_factor * (data->player.dir.y * treasure->relative_pos.x - data->player.dir.x * treasure->relative_pos.y);
	treasure->camera.y = inverse_matrix_factor * (-data->player.plane.y * treasure->relative_pos.x + data->player.plane.x * treasure->relative_pos.y);
}

static void	get_draw_range(t_cub3d *data, t_treasure *treasure)
{
	
	// Calculate the x-coordinate on the screen where the sprite should be displayed
	// By dividing the sprite's camera-relative x-coordinate by the sprite's camera-relative y-coordinate,
	// we calculate the direction and distance of the sprite from the camera.
	// Adding this value to the screen center (WIN_W / 2) gives the x-coordinate on the screen where the sprite should be displayed.
	treasure->screen_x = (int)(data->win_half_w * (1 + treasure->camera.x / treasure->camera.y));

	// Calculate the height that the sprite should occupy on the screen
	treasure->draw_height = ft_abs((int)(WIN_H / treasure->camera.y));
	// Calculate the y-coordinate range on the screen where the sprite should be displayed
	treasure->start_y = -treasure->draw_height / 2 + data->win_half_h;
	if (treasure->start_y < 0)
		treasure->start_y = 0;
	treasure->end_y = treasure->draw_height / 2 + data->win_half_h;
	if (treasure->end_y >= WIN_H)
		treasure->end_y = WIN_H - 1;

	// Calculate the width that the sprite should occupy on the screen
	treasure->draw_width = treasure->draw_height;
	// Calculate the x-coordinate range on the screen where the sprite should be displayed
	treasure->start_x = -treasure->draw_width / 2 + treasure->screen_x;
	if (treasure->start_x < 0)
		treasure->start_x = 0;
	treasure->end_x = treasure->draw_width / 2 + treasure->screen_x;
	if (treasure->end_x >= WIN_W)
		treasure->end_x = WIN_W - 1;
}
```
##### Sprite's coordinates relative to the player
<p align="center"><img style="width: 50%;" src="https://github.com/ysengoku/42-cub3d-macOS/assets/130462445/4aae7d77-c3eb-4e4e-b26c-9c8c03fee23b"></p>



## References
### Tutorials
* [Lode's Computer Graphics Tutorial - Raycasting](https://lodev.org/cgtutor/raycasting.html)
* [cub3d - HackMD](https://hackmd.io/@nszl/H1LXByIE2)
* [Cub3D Tutorial - Using angles](https://medium.com/@afatir.ahmedfatir/cub3d-tutorial-af5dd31d2fcf)
* [42 Docs - cub3d](https://harm-smits.github.io/42docs/projects/cub3d)
* [Algorithme_Cub3D](https://github.com/Qpupier/Cub3D/blob/master/Algorithme_Cub3D.pdf)
* [Raycasting in Cub3d 42 Network Project : A Practical Tutorial Using Vectors LODEV Documentation](https://medium.com/@rtailidounia/raycasting-in-cub3d-42-network-project-a-practical-tutorial-using-vectors-68eeb16b3de2)

### Videos
* [Make Your Own Raycaster Part 1](https://youtu.be/gYRrGTC7GtA?si=7KRnt_PSqn4lz4DD)
* [Make Your Own Raycaster Part 2](https://youtu.be/PC1RaETIx3Y?si=7rDwE_DvbRc79vQm)
* [Make Your Own Raycaster Part 3](https://youtu.be/w0Bm4IA-Ii8?si=aKqqxShLYT1G48O2)
* [Super Fast Ray Casting in Tiled Worlds using DDA](https://youtu.be/NbSee-XM7WA?si=HxCH4AbdRUjJhC7v)
* [Making my First RAYCASTING Game in C++ - SFML Gamedev - Devlog 1](https://youtu.be/LUYxLjic0Bc?si=18f9-hw6lV903EaB)

### Turorial in Japanese
* [42Tokyo C言語で一人称視点のゲームを作った](https://qiita.com/susasaki/items/c74a228d7ddd48b818bd)
* [C言語で3Dゲームを作った](https://jun-networks.hatenablog.com/entry/2021/03/04/130629)

### Textures
Treasure texture credit: <a href="https://www.freepik.com/free-vector/wooden-chest-realistic-set-with-images-opened-closed-empty-treasure-coffers-white_7497393.htm#query=treasure%20box&position=10&from_view=keyword&track=ais_user&uuid=aac9961d-90f6-43f3-aba7-2832a8b81de0">macrovector</a> on Freepik
