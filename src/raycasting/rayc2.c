/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayc2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maragao <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:55:51 by maragao           #+#    #+#             */
/*   Updated: 2023/08/02 17:55:57 by maragao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	dda(t_rayc *rc, t_file *file)
{
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
}

void	raycasting(t_file *file, t_mlx *mlx, t_rayc *rc)
{
	t_draw	wall;

	rc->x = 0;
	while (rc->x < WIN_WIDTH)
	{
		rc->cam_x = 2 * rc->x / (double)WIN_WIDTH - 1;
		rc->raydir_x = rc->dir_x + (rc->plane_x * rc->cam_x);
		rc->raydir_y = rc->dir_y + (rc->plane_y * rc->cam_x);
		rc->map_x = (int)rc->pos_x;
		rc->map_y = (int)rc->pos_y;
		if (rc->raydir_x == 0)
			rc->deltadist_x = 1e30;
		else
			rc->deltadist_x = fabs(1 / rc->raydir_x);
		if (rc->raydir_y == 0)
			rc->deltadist_y = 1e30;
		else
			rc->deltadist_y = fabs(1 / rc->raydir_y);
		calc_side_dist(rc);
		dda(rc, file);
		calc_texture_pixel(file, rc, &wall);
		draw_wall(mlx, &wall, file, rc);
		rc->x++;
	}
}

void	render_game(t_mlx *mlx, t_file *file, t_rayc *rc)
{
	init_image(mlx);
	raycasting(file, mlx, rc);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}
