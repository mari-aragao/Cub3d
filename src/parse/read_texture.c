#include "../../include/cub3d.h"

unsigned int    get_pixel_texture(t_img *img, int x, int y)
{
    char    *dest;
    
    dest = img->addr + (y * img->line_lenght + x * (img->bpp / 8));
    return (*(unsigned int *)dest);
}

void    texture_calc(t_rayc *rc, t_draw *wall) // calculo do pixel da textura
{
	if (rc->side == 0)
		wall->x = rc->pos_y + rc->perp_wall_dist * rc->raydir_y;
	else
		wall->x = rc->pos_x + rc->perp_wall_dist * rc->raydir_x;
    
	rc->tex_x = (int)(wall->x * (double)TEX_WIDTH);
	if (rc->side == 0 && rc->raydir_x > 0)
        	rc->tex_x = TEX_WIDTH - rc->tex_x - 1;
	if (rc->side == 1 && rc->raydir_y < 0)
        	rc->tex_x = TEX_WIDTH - rc->tex_x - 1;
	rc->step = 1.0 * TEX_HEIGHT / wall->height;
    	rc->tex_pos = (wall->y_start - rc->pitch - WIN_HEIGHT / 2 + wall->height / 2) * rc->step; 
}

int	is_xpm_file(char *path)
{
	int i;

	i = ft_strlen(path) - 1;
	while (path[i] != '.' && i > 0)
		i--;
	if (ft_strcmp(&path[i], ".xpm") == 0)
		return (0);
	return (1);
}

int	set_xpm_img(t_file *file, t_mlx *mlx)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (is_xpm_file(file->textures[i]) != 0)
			return (1);
		file->img_txt[i].img = mlx_xpm_file_to_image(mlx->mlx, file->textures[i], &file->img_txt[i].width, &file->img_txt[i].height);
		if (file->img_txt[i].img == NULL)
			return (1);
		//file->img_txt[i].addr = mlx_get_data_addr(file->img_txt[i].img, &file->img_txt[i].bpp, &file->img_txt[i].line_lenght, &file->img_txt[i].endian);
		my_mlx_get_addr(&file->img_txt[i]);
		i++;
	}
	return (0);
}
