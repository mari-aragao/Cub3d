#include "../../include/cub3d.h"

int	get_colors(t_file *file)
{
	int	i;

	i = 0;
	while (file->file[i] != NULL)
	{
		if (ft_strnstr(file->file[i], "F ", ft_strlen(file->file[i])) != NULL)
		{
			if (file->colors[0] != NULL)
				return (1);
			file->colors[0] = ft_strdup(file->file[i]);
		}
		else if (ft_strnstr(file->file[i], "C ", ft_strlen(file->file[i])) != NULL)
		{
			if (file->colors[1] != NULL)
				return (1);
			file->colors[1] = ft_strdup(file->file[i]);
		}
		i++;
	}
	return (0);
}

int is_colors(char *str)
{
	if (ft_strcmp(str, "C") == 0 || ft_strcmp(str, "F") == 0)
		return (0);
	return (1);
}

int	check_colors(char **mat)
{
	if (is_colors(mat[0]) == 0 && count_mat_size(mat) == 2)
		return (0);
	return (1);
}

int	split_colors(t_file *file)
{
	int i;
	int error_flag;
	char **mat;

	i = 0;
	error_flag = 0;
	while (file->colors[i] != NULL && error_flag == 0)
	{
		mat = ft_split(file->colors[i], ' ');
		if (check_colors(mat) == 1)
			error_flag = 1;
		if (error_flag == 0)
		{
			free(file->colors[i]);
			file->colors[i] = ft_strdup(mat[1]);
		}
		get_free(mat);
		i++;
	}
	if (error_flag == 1)
		return (1);
	return (0);
}
