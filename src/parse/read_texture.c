#include "../../include/cub3d.h"

int	is_xpm_file(char *path)
{
	int	i;

	i = ft_strlen(path) - 1;
	while (path[i] != '.' && i > 0)
		i--;
	if (ft_strcmp(&path[i], ".xpm") == 0)
		return (0);
	return (1);
}

int	set_xpm_img(t_file *file, t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (is_xpm_file(file->textures[i]) != 0)
			return (1);
		file->img_txt[i].img = mlx_xpm_file_to_image(mlx->mlx,
				file->textures[i], &file->img_txt[i].width,
				&file->img_txt[i].height);
		if (file->img_txt[i].img == NULL)
			return (1);
		my_mlx_get_addr(&file->img_txt[i]);
		i++;
	}
	return (0);
}
