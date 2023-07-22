#include "../../include/cub3d.h"

void	rotate_left(int key, t_rayc *rc)
{
	if (key == 65361)
	{
		rc->olddir_x = rc->dir_x;
		rc->dir_x = rc->dir_x * cosf(rc->rot_speed)
			- rc->dir_y * sinf(rc->rot_speed);
		rc->dir_y = rc->olddir_x * sinf(rc->rot_speed)
			+ rc->dir_y * cosf(rc->rot_speed);
		rc->oldplane_x = rc->plane_x;
		rc->plane_x = rc->plane_x * cosf(rc->rot_speed)
			- rc->plane_y * sinf(rc->rot_speed);
		rc->plane_y = rc->oldplane_x * sinf(rc->rot_speed)
			+ rc->plane_y * cosf(rc->rot_speed);
	}
}

void	rotate_right(int key, t_rayc *rc)
{
	if (key == 65363)
	{
		rc->olddir_x = rc->dir_x;
		rc->dir_x = rc->dir_x * cos(-rc->rot_speed)
			- rc->dir_y * sin(-rc->rot_speed);
		rc->dir_y = rc->olddir_x * sin(-rc->rot_speed)
			+ rc->dir_y * cos(-rc->rot_speed);
		rc->oldplane_x = rc->plane_x;
		rc->plane_x = rc->plane_x * cos(-rc->rot_speed)
			- rc->plane_y * sin(-rc->rot_speed);
		rc->plane_y = rc->oldplane_x * sin(-rc->rot_speed)
			+ rc->plane_y * cos(-rc->rot_speed);
	}
}
