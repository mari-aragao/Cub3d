#include "../include/cub3d.h"

void	init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIN_WIDHT, WIN_HEIGHT, "Cub3d");
}

void	render_game(t_mlx *mlx, t_file *file)
{
	(void)file;
	mlx->img = mlx_new_image(mlx->mlx, WIN_WIDHT, WIN_HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line_lenght, &mlx->endian);
//	raycasting(file);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

int	exit_hook(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);

}
int	key_press_hook(int key, t_mlx *mlx, t_file *file)
{
	if (key == 53)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		exit(0);
	}
	mlx_destroy_image(mlx->mlx, mlx->img);
	render_game(mlx, file);
	return (0);
}

void	set_hook(t_mlx *mlx, t_file *file)
{
	(void)file;
	mlx_key_hook(mlx->win, key_press_hook, mlx);
	mlx_hook(mlx->win, 17, 0, exit_hook, mlx);
}
