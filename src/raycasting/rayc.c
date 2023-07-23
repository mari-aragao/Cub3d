#include "../../include/cub3d.h"

void	draw_wall(t_mlx *mlx, t_draw *wall, t_file *file, t_rayc *rc)
{
	rc->y = 0;
	while (rc->y < WIN_HEIGHT - 1)
	{
		if (rc->y < wall->y_start)
			my_mlx_pixel_put(mlx, rc->x, rc->y, file->dec_ceiling);
		if (rc->y >= wall->y_end)
			my_mlx_pixel_put(mlx, rc->x, rc->y, file->dec_floor);
		if (rc->y < (wall->y_end - wall->y_start))
		{
			rc->tex_y = (int)rc->tex_pos;
			if (rc->tex_y > TEX_HEIGHT - 1)
				rc->tex_y = TEX_HEIGHT - 1;
			rc->tex_pos += rc->step;
			wall->color = get_pixel_texture(rc->texture, rc->tex_x, rc->tex_y);
			if (rc->side == 1)
				wall->color = (wall->color >> 1) & 8355711;
			my_mlx_pixel_put(mlx, rc->x, wall->y_start + rc->y, wall->color);
		}
		rc->y++;
	}
}

void	set_texture(t_rayc *rc, t_file *file)
{
	if (rc->side == 0)
	{
		if (rc->map_x < (int)rc->pos_x)
			rc->texture = &(file->img_txt[NO]);
		else
			rc->texture = &(file->img_txt[SO]);
	}
	if (rc->side == 1)
	{
		if (rc->map_y < (int)rc->pos_y)
			rc->texture = &(file->img_txt[WE]);
		else
			rc->texture = &(file->img_txt[EA]);
	}
}

void	calc_texture_pixel(t_file *file, t_rayc *rc, t_draw *wall)
{
	wall->height = (int)(WIN_HEIGHT / rc->perp_wall_dist);
	wall->y_start = -wall->height / 2 + WIN_HEIGHT / 2 + rc->pitch;
	if (wall->y_start < 0)
		wall->y_start = 0;
	wall->y_end = wall->height / 2 + WIN_HEIGHT / 2 + rc->pitch;
	if (wall->y_end >= WIN_HEIGHT)
		wall->y_end = WIN_HEIGHT - 1;
	set_texture(rc, file);
	if (rc->side == 0)
		wall->x = rc->pos_y + rc->perp_wall_dist * rc->raydir_y;
	else
		wall->x = rc->pos_x + rc->perp_wall_dist * rc->raydir_x;
	wall->x -= floor((wall->x));
	rc->tex_x = (int)(wall->x * (double)TEX_WIDTH);
	if (rc->side == 0 && rc->raydir_x > 0)
		rc->tex_x = TEX_WIDTH - rc->tex_x - 1;
	if (rc->side == 1 && rc->raydir_y < 0)
		rc->tex_x = TEX_WIDTH - rc->tex_x - 1;
	rc->step = 1.0 * TEX_HEIGHT / wall->height;
	rc->tex_pos = (wall->y_start - rc->pitch - WIN_HEIGHT / 2
			+ wall->height / 2) * rc->step;
}

void	calc_side_dist(t_rayc *rc)
{
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
}
