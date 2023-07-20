#include "../../include/cub3d.h"

int		get_pixel_texture(t_img *texture, int tex_x, int tex_y);
{

}

void	draw_wall(t_mlx *mlx, t_draw *wall, t_file *file, t_rayc *rc)
{
	int i;

	i = 0;
	(void) file;
	(void) rc;
	while (i < WIN_HEIGHT - 1)
	{
		if (i < wall->y_start)
			my_mlx_pixel_put(mlx, wall->x, i, file->dec_ceiling);
		if (i >= wall->y_end)
			my_mlx_pixel_put(mlx, wall->x, i, file->dec_floor);
		if (i < (wall->y_end - wall->y_start))
		{
			rc->tex_y = (int)rc->tex_pos;
			if (rc->tex_y > rc->tex_height - 1)
				rc->tex_y = rc->tex_height - 1;
			rc->tex_pos += rc->step;
			wall->color = get_pixel_texture(rc->texture, rc->tex_x, rc->tex_y);
			if (rc->side == 1)
				wall->color = (wall->color >> 1) & 8355711;
			my_mlx_pixel_put(mlx, wall->x, wall->y_start + i, wall->color);
		}
		i++;
	}
}

void	set_initial_pos(t_file *file, t_rayc *rc)
{
	int	x;
	int	y;

	x = 0;
	while (x < file->width)
	{
		y = 0;
		while (y < file->height)
		{
			if (is_valid_char(file->map[x][y]) == 2)
			{
				rc->pos_x = (double)x;
				rc->pos_y = (double)y;
				if (file->map[x][y] == 'N')
				{
					rc->dir_x = -1.0;
					rc->dir_y = 0.0;
					rc->plane_x = 0.0;
					rc->plane_y = 0.66;
				}
				if (file->map[x][y] == 'S')
				{
					rc->dir_x = 1.0;
					rc->dir_y = 0.0;
					rc->plane_x = 0.0;
					rc->plane_y = -0.66;
				}
				if (file->map[x][y] == 'W')
				{
					rc->dir_x = 0.0;
					rc->dir_y = -1.0;
					rc->plane_x = -0.66;
					rc->plane_y = 0.0;
				}
				if (file->map[x][y] == 'E')
				{
					rc->dir_x = 0.0;
					rc->dir_y = 1.0;
					rc->plane_x = 0.66;
					rc->plane_y = 0.0;
				}
				file->map[x][y] = '0';
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
	rc->olddir_x = rc->olddir_x;
	rc->olddir_y = rc->olddir_y;
	rc->oldplane_x = rc->plane_x;
	rc->oldplane_y = rc->plane_y;
	rc->hit = 0;
	rc->move_speed = 5.0 * (3.141592 / 180);
	rc->rot_speed = 3.0 * (3.141592 / 180);
	rc->pitch = 100;
}

void	raycasting(t_file *file, t_mlx *mlx, t_rayc *rc)
{
	t_draw wall;

	wall.x = 0;
	while (wall.x < WIN_WIDTH)
	{
		rc->cam_x = 2 * wall.x / (double)WIN_WIDTH - 1;
		rc->raydir_x = rc->dir_x + rc->plane_x * rc->cam_x;
		rc->raydir_y = rc->dir_y + rc->plane_y * rc->cam_x;

		rc->map_x = (int)rc->pos_x;
		rc->map_y = (int)rc->pos_y;
	
		rc->deltadist_x = (rc->raydir_x == 0) ? 1e30 : fabs(1 / rc->raydir_x);
		rc->deltadist_y = (rc->raydir_y == 0) ? 1e30 : fabs(1 / rc->raydir_y);

		if (rc->raydir_x < 0)
		{
			rc->step_x = -1;
			rc->sidedist_x = (rc->pos_x - rc->map_x) * rc->deltadist_x;
		}
		else
		{
			rc->step_x = 1;
			rc->sidedist_x = (rc->map_x + 1.0 - rc->pos_x) * rc->deltadist_x;
		}
		if (rc->raydir_y < 0)
		{
			rc->step_y = -1;
			rc->sidedist_y = (rc->pos_y - rc->map_y) * rc->deltadist_y;
		}
		else
		{
			rc->step_y = 1;
			rc->sidedist_y = (rc->map_y + 1.0 - rc->pos_y) * rc->deltadist_y;
		}
		rc->hit = 0;
		while (rc->hit == 0)
		{
			if (rc->sidedist_x < rc->sidedist_y)
			{
				rc->sidedist_x += rc->deltadist_x;
				rc->map_x += rc->step_x;
				rc->side = 0;
			}
			else
			{
				rc->sidedist_y += rc->deltadist_y;
				rc->map_y += rc->step_y;
				rc->side = 1;
			}
			if (file->map[rc->map_x][rc->map_y] > '0')
				rc->hit = 1;
		}
		if (rc->side == 0)
			rc->perp_wall_dist = (rc->sidedist_x - rc->deltadist_x);
		else
			rc->perp_wall_dist = (rc->sidedist_y - rc->deltadist_y);


		wall.height = (int)(WIN_HEIGHT / rc->perp_wall_dist);
		wall.y_start = -wall.height / 2 + WIN_HEIGHT / 2 + rc->pitch;
		if (wall.y_start < 0)
			wall.y_start = 0;
		wall.y_end = wall.height / 2 + WIN_HEIGHT / 2 + rc->pitch;
		if (wall.y_end >= WIN_HEIGHT)
			wall.y_end = WIN_HEIGHT - 1;

			
		if (rc->side == 0)
		{
			if (rc->map_x < (int)rc->pos_x)
    			rc->texture = &(file->img_txt[NO]);
				//wall.color = 16711680; //vermelho norte
			else
				rc->texture = &(file->img_txt[SO]);
    			//wall.color = 8388608; //marrom sul
		}
		if (rc->side == 1)
		{
			if (rc->map_y < (int)rc->pos_y)
				rc->texture = &(file->img_txt[WE]);
				//wall.color = 16753920; //laranja oeste
			else
				rc->texture = &(file->img_txt[EA]);
				//wall.color = 16766720; //amarelo leste
		}
// adicionei agr
		if (rc->side == 0)
			wall.x = rc->pos_y + rc->perp_wall_dist * rc->raydir_y;
		else
			wall.x = rc->pos_x + rc->perp_wall_dist * rc->raydir_x;


		texture_calc(rc, &wall);
		draw_wall(mlx, &wall, file, rc);
		
		wall.x++;
	}
}

void	render_game(t_mlx *mlx, t_file *file, t_rayc *rc)
{
	init_image(mlx);
	raycasting(file, mlx, rc);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}
