/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maragao <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:53:36 by maragao           #+#    #+#             */
/*   Updated: 2023/08/02 17:53:37 by maragao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	my_mlx_get_addr(t_img *img)
{
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
			&img->line_lenght, &img->endian);
}

void	init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3d");
}

void	init_image(t_mlx *mlx)
{
	mlx->img = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp,
			&mlx->line_lenght, &mlx->endian);
}

int	exit_hook(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
}

int	key_hook(int key, void *param)
{
	t_all	*all;

	all = (t_all *)param;
	if (key == 65307)
		exit_hook(all->mlx);
	move_player(key, all->file, all->rc, all->mlx);
	return (0);
}
