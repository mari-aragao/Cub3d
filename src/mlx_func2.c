#include "../include/cub3d.h"

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dest;

	dest = mlx->addr + (y * mlx->line_lenght + x * (mlx->bpp / 8));
	*(unsigned int *)dest = color;
}

unsigned int	get_pixel_texture(t_img *img, int x, int y)
{
	char	*dest;

	dest = img->addr + (y * img->line_lenght + x * (img->bpp / 8));
	return (*(unsigned int *)dest);
}
