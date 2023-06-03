#include "../../include/cub3d.h"

void	init_map(t_file *file, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (i < file->height)
	{
		map[i] = (char *) malloc(sizeof(char) * (file->widht + 1));
		j = 0;
		while (j < file->widht)
		{
			map[i][j] = ' ';
			j++;
		}
		map[i][j] = '\0';
		i++;
	}
	map[i] = NULL;
}

void	cpy_map_to_temp(t_file *file)
{
	int i;
	int j;

	i = 0;
	while (file->map[i])
	{
		j = 0;
		while (j < ft_strlen(file->map[i]))
		{
			file->map_temp[i + 2][j + 2] = file->map[i][j];
			j++;
		}
		i++;
	}
}

void	set_map_temp(t_file *file)
{
	file->map_temp = (char **) malloc(sizeof(char *) * (file->height + 1));
	if (file->map_temp == NULL)
		return ;
	init_map(file, file->map_temp);
	cpy_map_to_temp(file);
}