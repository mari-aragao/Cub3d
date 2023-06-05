#include "../../include/cub3d.h"

int	count_map_width(char **mat)
{
	int	i;
	int	count;

	i = 1;
	count = ft_strlen(mat[0]); 
	while (mat[i] != NULL)
	{
		if (ft_strlen(mat[i]) > count)
			count = ft_strlen(mat[i]);
		i++;
	}
	return (count);
}

int	is_valid_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (2);
	else if (c != '0' && c != '1' && c != ' ')
		return (1);
	return (0);
}

int	check_player(t_file *file)
{
	int	i;
	int	j;
	int	error;

	error = 0;
	i = 2;
	while (i < file->height - 3)
	{
		j = 2;
		while (j < file->width - 3)
		{
			if (is_valid_char(file->map_temp[i][j]) == 2 && error == 0)
				error = 1;
			else if (is_valid_char(file->map_temp[i][j]) == 2 && error == 1)
				return (write(2, "Error: Invalid map\n", 19));
			else if (is_valid_char(file->map_temp[i][j]) == 1)
				return (write(2, "Error: Invalid map\n", 19));
			j++;
		}
		i++;
	}
	if (error != 1)
		return (write(2, "Error: Invalid map\n", 19));
	return (0);
}

int	check_around_spaces(char **map, int i, int j)
{
	if (map[i][j - 1] != ' ' && map[i][j - 1] != '1')
		return (write(2, "Error: Invalid map\n", 19));
	if (map[i][j + 1] != ' ' && map[i][j + 1] != '1')
		return (write(2, "Error: Invalid map\n", 19));
	if (map[i - 1][j] != ' ' && map[i - 1][j] != '1')
		return (write(2, "Error: Invalid map\n", 19));
	if (map[i + 1][j] != ' ' && map[i + 1][j] != '1')
		return (write(2, "Error: Invalid map\n", 19));
	if (map[i - 1][j - 1] != ' ' && map[i - 1][j - 1] != '1')
		return (write(2, "Error: Invalid map\n", 19));
	if (map[i - 1][j + 1] != ' ' && map[i - 1][j + 1] != '1')
		return (write(2, "Error: Invalid map\n", 19));
	if (map[i + 1][j - 1] != ' ' && map[i + 1][j - 1] != '1')
		return (write(2, "Error: Invalid map\n", 19));
	if (map[i + 1][j + 1] != ' ' && map[i + 1][j + 1] != '1')
		return (write(2, "Error: Invalid map\n", 19));
	return (0);
}

int	check_around_player(char **map, int i, int j)
{
	if (map[i][j - 1] == ' ')
		return (write(2, "Error: Invalid map\n", 19));
	if (map[i][j + 1] == ' ')
		return (write(2, "Error: Invalid map\n", 19));
	if (map[i - 1][j] == ' ')
		return (write(2, "Error: Invalid map\n", 19));
	if (map[i + 1][j] == ' ')
		return (write(2, "Error: Invalid map\n", 19));
	if (map[i - 1][j - 1] == ' ')
		return (write(2, "Error: Invalid map\n", 19));
	if (map[i - 1][j + 1] == ' ')
		return (write(2, "Error: Invalid map\n", 19));
	if (map[i + 1][j - 1] == ' ')
		return (write(2, "Error: Invalid map\n", 19));
	if (map[i + 1][j + 1] == ' ')
		return (write(2, "Error: Invalid map\n", 19));
	return (0);
}

int	check_spaces(t_file *file)
{
	int	i;
	int	j;

	i = 1;
	while (i < file->height - 1)
	{
		j = 1;
		while (j < file->width - 1)
		{
			if (file->map_temp[i][j] == ' ')
			{
				if (check_around_spaces(file->map_temp, i, j) != 0)
					return (1);
			}
			if (is_valid_char(file->map_temp[i][j]) == 2)
			{
				if (check_around_player(file->map_temp, i, j) != 0)
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int validate_map(t_file *file)
{
	file->width = count_map_width(file->map) + 4;
	file->height += 4;
	set_map_temp(file);
	if (check_player(file) != 0)
		return (1);
	if (check_spaces(file) != 0)
		return (1);
	get_free(file->map_temp);
	file->width -= 4;
	file->height -= 4;
	return (0);
}
