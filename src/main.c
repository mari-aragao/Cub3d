/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maragao <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:53:09 by maragao           #+#    #+#             */
/*   Updated: 2023/08/03 19:53:23 by maragao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	init_elements(t_file *file)
{
	int	i;

	i = 0;
	file->textures = (char **) malloc(sizeof(char *) * 5);
	if (file->textures == NULL)
		return (1);
	while (i < 5)
	{
		file->textures[i] = NULL;
		i++;
	}
	file->colors = (char **) malloc(sizeof(char *) * 3);
	if (file->colors == NULL)
		return (1);
	i = 0;
	while (i < 3)
	{
		file->colors[i] = NULL;
		i++;
	}
	file->map = NULL;
	return (0);
}

int	main(int argc, char **argv)
{
	t_file	file;
	t_rayc	rc;
	t_mlx	mlx;
	t_all	all;

	if (start_validation(argc, argv, &file) != 0)
		return (1);
	init_rc(&file, &rc);
	init_mlx(&mlx);
	if (set_xpm_img(&file, &mlx) == 1)
	{
		free_all(&file);
		return (1);
	}
	all.mlx = &mlx;
	all.file = &file;
	all.rc = &rc;
	mlx_hook(mlx.win, 17, 0, exit_hook, &all);
	mlx_hook(mlx.win, 2, 1L << 0, key_hook, &all);
	render_game(&mlx, &file, &rc);
	mlx_loop(mlx.mlx);
	free_all(&file);
	return (0);
}
