#include "../../include/cub3d.h"

void	check_direction(t_rayc *rc, char dir, int x, int y)
{
	rc->pos_x = (double)x;
	rc->pos_y = (double)y;
	if (dir == 'N')
	{
		rc->dir_x = -1.0;
		rc->plane_y = 0.66;
	}
	else if (dir == 'S')
	{
		rc->dir_x = 1.0;
		rc->plane_y = -0.66;
	}
	else if (dir == 'W')
	{
		rc->dir_y = -1.0;
		rc->plane_x = -0.66;
	}
	else if (dir == 'E')
	{
		rc->dir_y = 1.0;
		rc->plane_x = 0.66;
	}
}

void	set_initial_pos(t_file *file, t_rayc *rc)
{
	int	x;
	int	y;

	x = -1;
	while (++x < file->width)
	{
		y = -1;
		while (++y < file->height)
		{
			if (is_valid_char(file->map[x][y]) == 2)
			{
				if (file->map[x][y] == 'N' || file->map[x][y] == 'S')
					rc->dir_y = 0.0;
				if (file->map[x][y] == 'N' || file->map[x][y] == 'S')
					rc->plane_x = 0.0;
				if (file->map[x][y] == 'W' || file->map[x][y] == 'E')
					rc->dir_x = 0.0;
				if (file->map[x][y] == 'W' || file->map[x][y] == 'E')
					rc->plane_y = 0.0;
				check_direction(rc, file->map[x][y], x, y);
				file->map[x][y] = '0';
				return ;
			}
		}
	}
}

void	init_rc(t_file *file, t_rayc *rc)
{
	set_initial_pos(file, rc);
	rc->olddir_x = rc->dir_x;
	rc->olddir_y = rc->dir_y;
	rc->oldplane_x = rc->plane_x;
	rc->oldplane_y = rc->plane_y;
	rc->hit = 0;
	rc->move_speed = 10.0 * (3.141592 / 180);
	rc->rot_speed = 6.0 * (3.141592 / 180);
	rc->pitch = 100;
	rc->tex_x = 0;
	rc->tex_y = 0;
	rc->tex_pos = 0;
	rc->step = 0;
}
