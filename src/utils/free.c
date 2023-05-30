#include "../../include/cub3d.h"

void	get_free(char **mat)
{
	int i; 

	if (!mat)
		return ;
	i = 0;
	while (mat[i])
		free(mat[i++]);
	free(mat);
}

void	free_all(t_file *file)
{
	if (file->file)
		get_free(file->file);
	get_free(file->textures);
	get_free(file->colors);
	if (file->map)
		get_free(file->map);
	if (file->map_temp)
		get_free(file->map_temp);
}
