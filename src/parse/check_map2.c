#include "../../include/cub3d.h"

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

int	check_empty_line_map(t_file *file)
{
	int	i;

	i = 0;
	while (i <= file->map_size)
	{
		if (file->map[i] == NULL)
			return (write(2, "Error: Invalid map\n", 19));
		i++;
	}
	return (0);
}
