#include "../include/cub3d.h"

int	init_elements(t_file *file)
{
	int	i;

	i = 0;
	file->textures = (char **) malloc(sizeof(char *) * 5);
	if (file->textures == NULL)
		return (1);
	while (i < 5)
	{
		file->textures[i] = NULL;
		i++;
	}
	file->colors = (char **) malloc(sizeof(char *) * 3);
	if (file->colors == NULL)
		return (1);
	i = 0;
	while (i < 3)
	{
		file->colors[i] = NULL;
		i++;
	}
	return (0);
}

int	main(int argc, char **argv) 
{
	t_file	file;
	t_mlx	mlx;

	if (check_argc(argc) == 1)
		return (1);
	if (check_path(argv[1]) == 1)
		return (1);
	if (read_file(argv[1], &file) > 0)
	{
		free_all(&file);
		return (1);
	}
	if (file.file == NULL)
	{
		free_all(&file);
		return (1);
	}
	init_mlx(&mlx);
	set_hook(&mlx, &file);
	render_game(&mlx, &file);
//	mlx_loop(mlx.mlx);
//	free_all(&file);
	return (0);
}
