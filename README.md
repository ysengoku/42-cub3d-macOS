# 42-cub3d

## Structure

### Player
```c
#define FOV 60
#define M_PI 3.14159265358979323846

enum	e_direction
{
	NORTH = 90,
	EAST = 0,
	SOUTH = 270,
	WEST = 180
};

typedef struct s_player
{
	double			angle; // FOV in radians
	int			pos_x;
	int			pos_y;
	enum e_direction	initial_dir;
	double			dir; //direction in degree
	double			dir_x; 
	double			dir_y;
	double			plane_x;
	double			plane_y;
	
}				t_player;
```
```c
/* Exemple map */
111111
100101
101001
1100N1
111111
// Player is represented by N (north direction)
```

#### Player's position (pos_x, pos_y)
Player's initial map coordinates (not pixel coordinate). He must be placed at the center of cell.
```c
In the exemple,  
pos_x = 4.5, pos_y = 3.5
// Coordinate on the map is (4, 3)
```

#### Direction vector (dir_x, dir_y)
Player's initial direction
- NORTH : 90°
- SOUTH : 270°
- EAST : 0°
- WEST : 180°  

```c
t_player	player;
double 		dir_rad;

dir_rad = player.dir * M_PI / 180;
player.dir_x = cos(dir_rad);
player.dir_y = -sin(dir_rad);

// result
// NORTH (0, -1)
// SOUTH (0, 1)
// EAST : (1, 0)
// WEST : (-1, 0)
```

```c
In the exemple,  
dir_x = 0, dir_y = -1
```

#### Camera plane vector (plane_x, plane_y)
1. Convert FOV° in radian  
  fov_radians = FOV * M_PI / 180.0
2. Calculate plane length  
  plane_length = tan(fov_radians / 2)
3. Calculate plane vector  
  plane_x = dir_y * plane_length  
  plane_y = dir_x * plane_length
```c
In the example,
fov_rad = 60 * M_PI / 180 = 1.047198
plane_length = tan(fov_rad / 2) = 0.57735
plane_x = dir_y * plane_length = -1 * 0.57735 = -0.57735
plane_y = dir_x * plane_length = 0 * 0.57735 = 0
```
