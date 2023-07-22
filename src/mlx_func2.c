#include "../include/cub3d.h"

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dest;

	dest = mlx->addr + (y * mlx->line_lenght + x * (mlx->bpp / 8));
	*(unsigned int *)dest = color;
}
