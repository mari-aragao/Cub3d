#include "../include/cub3d.h"

void	init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIN_WIDHT, WIN_HEIGHT, "Cub3d");
}

void	init_image(t_mlx *mlx)
{
	mlx->img = mlx_new_image(mlx->mlx, WIN_WIDHT, WIN_HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line_lenght, &mlx->endian);
}

int	exit_hook(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);

}
int	move_player(int key, t_rayc *rc)
{
	//move
	if (key == 13) // w
		rc->pos_x += rc->dir_x * rc->move_speed;
	else if (key == 1) //s
		rc->pos_x -= rc->dir_x * rc->move_speed;
	else if (key == 123) // >
	{
		rc->olddir_x = rc->dir_x;
		rc->dir_x = rc->dir_x * acos(rc->rot_speed) - rc->dir_y * asin(rc->rot_speed);
		rc->dir_y = rc->olddir_x * asin(rc->rot_speed) + rc->dir_y * acos(rc->rot_speed);
		rc->oldplane_x = rc->plane_x;
		rc->plane_x = rc->plane_x * acos(rc->rot_speed) - rc->plane_y * asin(rc->rot_speed);
		rc->plane_y = rc->oldplane_x * asin(rc->rot_speed) + rc->plane_y * acos(rc->rot_speed);
	}
	else if (key == 124) // <
	{
		rc->olddir_x = rc->dir_x;
		rc->dir_x = rc->dir_x * acos(-rc->rot_speed) - rc->dir_y * asin(-rc->rot_speed);
		rc->dir_y = rc->olddir_x * asin(-rc->rot_speed) + rc->dir_y * acos(-rc->rot_speed);
		rc->oldplane_x = rc->plane_x;
		rc->plane_x = rc->plane_x * acos(-rc->rot_speed) - rc->plane_y * asin(-rc->rot_speed);
		rc->plane_y = rc->oldplane_x * asin(-rc->rot_speed) + rc->plane_y * acos(-rc->rot_speed);
	}
	//mlx_destroy_image(mlx->mlx, mlx->img);
//	render_game(mlx, file);
	return (0);
}

int	key_hook(int key, t_mlx *mlx, t_rayc *rc)
{
//	t_rayc *rc;

//	rc = (t_rayc *) param;
	if (key == 53)
		exit_hook(mlx);
	move_player(key, rc);
	return (0);

}

/*void	set_hook(t_mlx *mlx, t_file *file, t_rayc *rc)
{
	(void)file;
	(void)rc;
//	mlx_key_hook(mlx->win, key_hook, mlx);
//	mlx_hook(mlx->win, 17, 0, exit_hook, mlx);
	return ;
}*/
