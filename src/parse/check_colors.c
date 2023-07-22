#include "../../include/cub3d.h"

int	check_numbers(int *number)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (number[i] < 0 || number[i] > 255)
			return (1);
		i++;
	}
	return (0);
}

int	check_is_digit(char **mat)
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (mat[i][j])
		{
			if (ft_isdigit(mat[i][j]) != 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	set_colors(char *str, t_file *file, int type)
{
	int		i;
	int		ret;
	char	**mat;

	ret = 0;
	mat = ft_split(str, ',');
	if (count_mat_size(mat) != 3)
		ret = 1;
	if (ret == 0 && check_is_digit(mat) > 0)
		ret = 1;
	i = 0;
	while (i < 3)
	{
		if (type == 0)
			file->floor[i] = ft_atoi(mat[i]);
		else if (type == 1)
			file->ceiling[i] = ft_atoi(mat[i]);
		i++;
	}
	get_free(mat);
	return (0);
}

int	validate_colors(t_file *file)
{
	if (set_colors(file->colors[0], file, 0) > 0)
	{
		write(2, "cub3d: Error: Wrong colors\n", 28);
		return (1);
	}
	if (set_colors(file->colors[1], file, 1) > 0)
	{
		write(2, "cub3d: Error: Wrong colors\n", 28);
		return (1);
	}
	calculate_decimal_color(file);
	if (check_numbers(file->floor) > 0)
	{
		write(2, "cub3d: Error: Wrong colors\n", 28);
		return (1);
	}
	if (check_numbers(file->ceiling) > 0)
	{
		write(2, "cub3d: Error: Wrong colors\n", 28);
		return (1);
	}
	return (0);
}
