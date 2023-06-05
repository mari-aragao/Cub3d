#include "../../include/cub3d.h"

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
		my_mlx_get_addr(&file->img_txt[i]);
		i++;
	}
	return (0);
}

int	get_textures(t_file *file) 
{
	int	i;

	i = 0;
	while (file->file[i] != NULL)
	{
		if (ft_strnstr(file->file[i], "NO ", ft_strlen(file->file[i])) != NULL)
		{
			if (file->textures[NO] != NULL)
				return (1);
			file->textures[NO] = ft_strdup(file->file[i]);
		}
		else if (ft_strnstr(file->file[i], "SO ", ft_strlen(file->file[i])) != NULL)
		{
			if (file->textures[SO] != NULL)
				return (1);
			file->textures[SO] = ft_strdup(file->file[i]);
		}
		else if (ft_strnstr(file->file[i], "WE ", ft_strlen(file->file[i])) != NULL)
		{
			if (file->textures[WE] != NULL)
				return (1);
			file->textures[WE] = ft_strdup(file->file[i]);
		}
		else if (ft_strnstr(file->file[i], "EA ", ft_strlen(file->file[i])) != NULL)
		{
			if (file->textures[EA] != NULL)
				return (1);
			file->textures[EA] = ft_strdup(file->file[i]);
		}
		i++;
	}
	return (0);
}

int	is_textures(char *str)
{
	if (ft_strcmp(str, "NO") == 0 || ft_strcmp(str, "SO") == 0 \
 	|| ft_strcmp(str, "WE") == 0 || ft_strcmp(str, "EA") == 0)
		return (0);
	return (1);
}

int	check_textures(char **mat)
{
	if (is_textures(mat[0]) == 0 && count_mat_size(mat) == 2)
		return (0);
	return (1);
}

int	split_textures(t_file *file)
{
	int i;
	int error_flag;
	char **mat;

	i = 0;
	error_flag = 0;
	while (file->textures[i] != NULL && error_flag == 0)
	{
		mat = ft_split(file->textures[i], ' ');
		if (check_textures(mat) == 1)
			error_flag = 1;
		if (error_flag == 0)
		{
			free(file->textures[i]);
			file->textures[i] = ft_strdup(mat[1]);
		}
		get_free(mat);
		i++;
	}
	if (error_flag == 1)
		return (1);
	return (0);
}
