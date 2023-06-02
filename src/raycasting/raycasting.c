#include "../../include/cub3d.h"

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char *dest;

	dest = mlx->addr + (y + mlx->line_lenght + x * (mlx->bpp / 8));
	*(unsigned int *)dest = color;
	return ;
}

void	draw_wall(t_mlx *mlx, t_draw *wall)
{
	int i;

	i = 0;
	while (i < (wall->y_end - wall->y_start))
	{	
		my_mlx_pixel_put(mlx->img, wall->x, wall->y_start + i, wall->color);
		i++;
	}
	return ;
}

void	set_initial_pos(t_file *file, t_rayc *rc)
{
	int	x;
	int	y;

	x = 0;
	while (x < file->widht)
	{
		y = 0;
		while (y < file->height)
		{
			if (is_valid_char(file->map[y][x]) == 2)
			{
				rc->pos_x = (double)x;
				rc->pos_y = (double)y;
				return ;
			}
			y++;
		}
		x++; 
	}
}

void	init_rc(t_file *file, t_rayc *rc)
{
	set_initial_pos(file, rc);	
	rc->dir_x = -1;
	rc->dir_y = 0;
	rc->plane_x = 0;
	rc->plane_y = 0.66;
	rc->time = 0;
	rc->oldtime = 0;
	rc->hit = 0;
	

}

void	raycasting(t_mlx *mlx, t_file *file)
{
	t_rayc rc;
	t_draw wall;

	init_rc(file, &rc);
while (1)
{	
	mlx->img = mlx_new_image(mlx->mlx, WIN_WIDHT, WIN_HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line_lenght, &mlx->endian);	
	wall.x = 0;
	while (wall.x < WIN_WIDHT)
	{
		rc.cam_x = 2 * wall.x / (double)WIN_WIDHT - 1;
		rc.raydir_x = rc.dir_x + rc.plane_x * rc.cam_x;
		rc.raydir_y = rc.dir_y + rc.plane_y * rc.cam_x;
	//	printf("pos x = %f && pos y = %f\n", rc.pos_x, rc.pos_y);
	//	printf("cam x = %f\n", rc.cam_x);
	//	printf("raydir x = %f && raydir y = %f\n", rc.raydir_x, rc.raydir_y);

		rc.map_x = (int)rc.pos_x;
		rc.map_y = (int)rc.pos_y;
	//	printf("map x = %i && map y = %i\n", rc.map_x, rc.map_y);
		
		rc.deltadist_x = (rc.raydir_x == 0) ? 1e30 : fabs(1 / rc.raydir_x);
		rc.deltadist_y = (rc.raydir_y == 0) ? 1e30 : fabs(1 / rc.raydir_y);

		if (rc.raydir_x < 0)
		{
			rc.step_x = -1;
			rc.sidedist_x = (rc.pos_x - rc.map_x) * rc.deltadist_x;
		}
		else
		{
			rc.step_x = 1;
			rc.sidedist_x = (rc.map_x + 1.0 - rc.pos_x) * rc.deltadist_x;
			
		}
		if (rc.raydir_y < 0)
		{
			rc.step_y = -1;
			rc.sidedist_y = (rc.pos_y - rc.map_y) * rc.deltadist_y;
		}
		else
		{
			rc.step_y = 1;
			rc.sidedist_y = (rc.map_y + 1.0 - rc.pos_y) * rc.deltadist_y;
		}
		
		rc.hit = 0;
		while (rc.hit == 0)
		{
			if (rc.sidedist_x < rc.sidedist_y)
			{
				rc.sidedist_x += rc.deltadist_x;
				rc.map_x += rc.step_x;
				rc.side = 0;
			}
			else
			{
				rc.sidedist_y += rc.deltadist_y;
				rc.map_y += rc.step_y;
				rc.side = 1;
			}
			printf("map[%i][%i] = %i\n",rc.map_x, rc.map_y, file->map[rc.map_x][rc.map_y]);
			if (file->map[rc.map_x][rc.map_y] > '0')
			{
				rc.hit = 1;
			}
		}

		if (rc.side == 0)
			rc.perp_wall_dist = (rc.sidedist_x - rc.deltadist_x);
		else
			rc.perp_wall_dist = (rc.sidedist_y - rc.deltadist_y);
		
		wall.height = (int)(WIN_HEIGHT / rc.perp_wall_dist);

		wall.y_start = -wall.height / 2 + WIN_HEIGHT / 2;
		if (wall.y_start < 0)
			wall.y_start = 0;
		
		wall.y_end = wall.height / 2 + WIN_HEIGHT / 2;
		if (wall.y_end >= WIN_HEIGHT)
			wall.y_end = WIN_HEIGHT - 1;
		printf("side = %i\n", rc.side);
		printf("deltadist x = %f && deltadist y = %f\n", rc.deltadist_x, rc.deltadist_y);
		printf("sidedist x = %f && sidedist y = %f\n", rc.sidedist_x, rc.sidedist_y);

		printf("wall height = %i\n",wall.height);
		printf("wall.y_start = %i\n", wall.y_start);
		printf("wall.y_end = %i\n", wall.y_end);

    		wall.color = 0x00FF00; //green
//		if (rc.side == 1)
//			wall.color /= 2;
//		draw_wall(mlx, &wall);
		wall.x++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_loop(mlx->mlx);
}
return ;
}
