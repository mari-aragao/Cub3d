/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maragao <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:53:36 by maragao           #+#    #+#             */
/*   Updated: 2023/08/03 18:45:47 by maragao          ###   ########.fr       */
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

int	exit_hook(t_all *all)
{
	mlx_clear_window(all->mlx->mlx, all->mlx->win);
	mlx_destroy_window(all->mlx->mlx, all->mlx->win);
	mlx_destroy_image(all->mlx->mlx, all->mlx->img);
	mlx_destroy_image(all->mlx->mlx, all->file->img_txt[0].img);
	mlx_destroy_image(all->mlx->mlx, all->file->img_txt[1].img);
	mlx_destroy_image(all->mlx->mlx, all->file->img_txt[2].img);
	mlx_destroy_image(all->mlx->mlx, all->file->img_txt[3].img);
	/*free(all->file->img_txt[0].img);
	free(all->file->img_txt[1].img);
	free(all->file->img_txt[2].img);
	free(all->file->img_txt[3].img);
	*/free_all(all->file);
	mlx_destroy_display(all->mlx->mlx);
	free(all->mlx->mlx);

	exit(0);
}

int	key_hook(int key, void *param)
{
	t_all	*all;

	all = (t_all *)param;
	if (key == 65307)
		exit_hook(all);
	move_player(key, all->file, all->rc, all->mlx);
	return (0);
}
