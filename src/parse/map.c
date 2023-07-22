#include "../../include/cub3d.h"

int	is_element(char *str)
{
	if (ft_strnstr(str, "NO ", ft_strlen(str)) != NULL \
			|| ft_strnstr(str, "SO ", ft_strlen(str)) != NULL \
			|| ft_strnstr(str, "WE ", ft_strlen(str)) != NULL \
			|| ft_strnstr(str, "EA ", ft_strlen(str)) != NULL \
			|| ft_strnstr(str, "F ", ft_strlen(str)) != NULL \
			|| ft_strnstr(str, "C ", ft_strlen(str)) != NULL)
		return (0);
	return (1);
}

void	remap(t_file *file)
{
	int		i;
	int		j;
	char	**remap;

	remap = (char **) malloc(sizeof(char *) * (file->height + 1));
	if (remap == NULL)
		return ;
	init_map(file, remap);
	i = 0;
	while (file->map[i])
	{
		j = 0;
		while (j < ft_strlen(file->map[i]))
		{
			remap[i][j] = file->map[i][j];
			j++;
		}
		i++;
	}
	get_free(file->map);
	file->map = remap;
}

void	get_map(t_file *file)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (file->file[i])
	{
		if (is_element(file->file[i++]) == 0)
			count++;
		if (count == 6)
		{
			while (file->file[i][0] == '\0' && file->file[i] != NULL)
				i++;
			break ;
		}
	}
	file->height = file->file_lines - i;
	file->map = (char **) malloc(sizeof(char *) * (file->height + 1));
	j = -1;
	while (++j < file->height)
		file->map[j] = ft_strdup(file->file[i++]);
	file->map[j] = NULL;
}
