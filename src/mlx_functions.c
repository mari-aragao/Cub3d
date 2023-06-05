#include "../include/cub3d.h"

void	my_mlx_get_addr(t_img *img)
{
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_lenght, &img->endian);
	
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char *dest;
	
	dest = mlx->addr + (y * mlx->line_lenght + x * (mlx->bpp / 8));
	*(unsigned int *)dest = color;
	return ;
}

void	init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3d");
}

void	init_image(t_mlx *mlx)
{
	mlx->img = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line_lenght, &mlx->endian);
}

int	exit_hook(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
}

int	is_wall(t_file *file, int x, int y)
{
	if (file->map[x][y] == '1')
		return (1);
	return (0);
}

int	move_player(int key, t_file *file, t_rayc *rc, t_mlx *mlx)
{
	if (key == 119) // w
	{
		if (is_wall (file, (int)(rc->pos_x + rc->dir_x * rc->move_speed), (int)rc->pos_y) == 0)
			rc->pos_x += rc->dir_x * rc->move_speed;
		if (is_wall(file, (int)rc->pos_x, (int)(rc->pos_y + rc->dir_y * rc->move_speed)) == 0)
			rc->pos_y += rc->dir_y * rc->move_speed;
	}
	else if (key == 115) //s
	{
		if (is_wall(file, (int)(rc->pos_x - rc->dir_x * rc->move_speed), (int)rc->pos_y) == 0)
			rc->pos_x -= rc->dir_x * rc->move_speed;
		if (is_wall(file, (int)rc->pos_x, (int)(rc->pos_y - rc->dir_y * rc->move_speed)) == 0)
			rc->pos_y -= rc->dir_y * rc->move_speed;
	}
	else if (key == 97) //a
	{
		if (is_wall(file, (int)(rc->pos_x - rc->plane_x * rc->move_speed), (int)rc->pos_y) == 0)
			rc->pos_x -= rc->plane_x * rc->move_speed;
		if (is_wall(file, (int)rc->pos_x, (int)(rc->pos_y - rc->plane_y * rc->move_speed)) == 0)
			rc->pos_y -= rc->plane_y * rc->move_speed;
	}
	else if (key == 100) //d
	{
		if (file->map[(int)(rc->pos_x + rc->plane_x * rc->move_speed)][(int)rc->pos_y] != 0)
			rc->pos_x += rc->plane_x * rc->move_speed;
		if (file->map[(int)rc->pos_x][(int)(rc->pos_y + rc->plane_y * rc->move_speed)] != 0)
			rc->pos_y += rc->plane_y * rc->move_speed;
	}
	else if (key == 65361) // >
	{
		rc->olddir_x = rc->dir_x;
		rc->dir_x = rc->dir_x * cosf(rc->rot_speed) - rc->dir_y * sinf(rc->rot_speed);
		rc->dir_y = rc->olddir_x * sinf(rc->rot_speed) + rc->dir_y * cosf(rc->rot_speed);
		rc->oldplane_x = rc->plane_x;
		rc->plane_x = rc->plane_x * cosf(rc->rot_speed) - rc->plane_y * sinf(rc->rot_speed);
		rc->plane_y = rc->oldplane_x * sinf(rc->rot_speed) + rc->plane_y * cosf(rc->rot_speed);
	}
	else if (key == 65363) // <
	{
		rc->olddir_x = rc->dir_x;
		rc->dir_x = rc->dir_x * cos(-rc->rot_speed) - rc->dir_y * sin(-rc->rot_speed);
		rc->dir_y = rc->olddir_x * sin(-rc->rot_speed) + rc->dir_y * cos(-rc->rot_speed);
		rc->oldplane_x = rc->plane_x;
		rc->plane_x = rc->plane_x * cos(-rc->rot_speed) - rc->plane_y * sin(-rc->rot_speed);
		rc->plane_y = rc->oldplane_x * sin(-rc->rot_speed) + rc->plane_y * cos(-rc->rot_speed);
	}
	mlx_destroy_image(mlx->mlx, mlx->img);
	render_game(mlx, file, rc);
	return (0);
}

int	key_hook(int key, void *param)
{
	t_all *all;

	all = (t_all *)param;
	if (key == 65307)
		exit_hook(all->mlx);
	move_player(key, all->file, all->rc, all->mlx);
	return (0);

}
