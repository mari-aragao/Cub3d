/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maragao <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:55:35 by maragao           #+#    #+#             */
/*   Updated: 2023/08/02 17:55:36 by maragao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	is_wall(t_file *file, int x, int y)
{
	if (file->map[x][y] == '1')
		return (1);
	return (0);
}

void	move_w_and_s(int key, t_file *file, t_rayc *rc)
{
	if (key == 119)
	{
		if (is_wall (file, (int)(rc->pos_x + rc->dir_x
				* rc->move_speed), (int)rc->pos_y) == 0)
			rc->pos_x += rc->dir_x * rc->move_speed;
		if (is_wall(file, (int)rc->pos_x, (int)(rc->pos_y
				+ rc->dir_y * rc->move_speed)) == 0)
			rc->pos_y += rc->dir_y * rc->move_speed;
	}
	else if (key == 115)
	{
		if (is_wall(file, (int)(rc->pos_x - rc->dir_x
				* rc->move_speed), (int)rc->pos_y) == 0)
			rc->pos_x -= rc->dir_x * rc->move_speed;
		if (is_wall(file, (int)rc->pos_x, (int)(rc->pos_y
				- rc->dir_y * rc->move_speed)) == 0)
			rc->pos_y -= rc->dir_y * rc->move_speed;
	}
}

void	move_a_and_d(int key, t_file *file, t_rayc *rc)
{
	if (key == 97)
	{
		if (is_wall(file, (int)(rc->pos_x - rc->plane_x
				* rc->move_speed), (int)rc->pos_y) == 0)
			rc->pos_x -= rc->plane_x * rc->move_speed;
		if (is_wall(file, (int)rc->pos_x, (int)(rc->pos_y
				- rc->plane_y * rc->move_speed)) == 0)
			rc->pos_y -= rc->plane_y * rc->move_speed;
	}
	else if (key == 100)
	{
		if (file->map[(int)(rc->pos_x + rc->plane_x
				* rc->move_speed)][(int)rc->pos_y] != 0)
			rc->pos_x += rc->plane_x * rc->move_speed;
		if (file->map[(int)rc->pos_x][(int)(rc->pos_y
			+ rc->plane_y * rc->move_speed)] != 0)
			rc->pos_y += rc->plane_y * rc->move_speed;
	}
}

int	move_player(int key, t_file *file, t_rayc *rc, t_mlx *mlx)
{
	move_w_and_s(key, file, rc);
	move_a_and_d(key, file, rc);
	rotate_left(key, rc);
	rotate_right(key, rc);
	mlx_destroy_image(mlx->mlx, mlx->img);
	render_game(mlx, file, rc);
	return (0);
}
