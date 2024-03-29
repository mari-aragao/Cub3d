/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maragao <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:53:22 by maragao           #+#    #+#             */
/*   Updated: 2023/08/03 20:02:58 by maragao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	start_validation(int argc, char **argv, t_file *file)
{
	int	fd;

	if (check_argc(argc) != 0)
		return (1);
	if (check_path(argv[1]) == 1)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (1);
	if (check_empty_file(file, argv[1], fd) != 0)
		return (1);
	if (read_file(argv[1], file) > 0)
	{
		free_all(file);
		return (1);
	}
	if (file->file == NULL)
	{
		free_all(file);
		return (1);
	}
	return (0);
}

int	check_argc(int argc)
{
	if (argc != 2)
	{
		write(2, "Error: Wrong arguments\n", 23);
		return (1);
	}
	return (0);
}

int	check_path(char *path)
{
	int	i;

	i = ft_strlen(path) - 1;
	while (path[i] != '.' && i > 0)
		i--;
	if (ft_strcmp(&path[i], ".cub") == 0 && open(path, O_RDONLY) != -1)
		return (0);
	write(2, "Error: Invalid path\n", 21);
	return (1);
}

int	check_elements(t_file *file)
{
	int	i;
	int	fd;

	i = -1;
	if (split_textures(file) > 0)
		return (write(2, "Error: Wrong textures\n", 22));
	if (split_colors(file) > 0)
		return (write(2, "Error: Wrong colors\n", 20));
	while (++i < 4)
	{
		if (file->textures[i] == NULL)
			return (write(2, "Error: Wrong textures\n", 22));
		fd = open(file->textures[i], O_RDONLY);
		if (fd == -1)
			return (write(2, "Error: Wrong textures\n", 22));
		close(fd);
	}
	i = -1;
	while (++i < 2)
	{
		if (file->colors[i] == NULL)
			return (write(2, "Error: Wrong colors\n", 20));
	}
	return (0);
}

int	check_empty_file(t_file *file, char *path, int fd)
{
	if (fd == -1)
		return (write(2, "Error: Invalid path\n", 20));
	file->file_lines = count_file_lines(path);
	if (file->file_lines == 0)
		return (write(2, "Error: Empty file\n", 19));
	return (0);
}
