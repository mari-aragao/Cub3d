/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maragao <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:54:54 by maragao           #+#    #+#             */
/*   Updated: 2023/08/03 20:02:40 by maragao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	count_file_lines(char *path)
{
	int		count;
	int		fd;
	char	*buff;

	fd = open(path, O_RDONLY);
	count = 0;
	while (1)
	{
		buff = get_next_line(fd);
		if (buff == NULL)
			break ;
		free(buff);
		count++;
	}
	close(fd);
	return (count);
}

void	remove_file_endl(t_file *file)
{
	int		i;
	char	**aux;

	aux = (char **) malloc(sizeof(char *) * (file->file_lines + 1));
	i = -1;
	while (++i < file->file_lines)
		aux[i] = cpy_no_endl(file->file[i]);
	aux[i] = NULL;
	get_free(file->file);
	file->file = aux;
}

int	valid_file(t_file *file)
{
	if (get_textures(file) == 1)
		return (write(2, "Error: Wrong textures\n", 22));
	if (get_colors(file) == 1)
		return (write(2, "Error: Wrong colors\n", 20));
	if (check_elements(file) > 0)
		return (1);
	if (validate_colors(file) > 0)
		return (1);
	return (0);
}

int	read_file(char *path, t_file *file)
{
	int	i;
	int	fd;

	i = 0;
	fd = open(path, O_RDONLY);
	file->file = (char **) malloc(sizeof(char *) * (file->file_lines + 1));
	while (i < file->file_lines)
	{
		file->file[i] = get_next_line(fd);
		i++;
	}
	file->file[i] = NULL;
	close(fd);
	remove_file_endl(file);
	init_elements(file);
	if (valid_file(file) != 0)
		return (1);
	if (get_map(file) != 0)
		return (write(2, "Error: invalid map\n", 20));
	if (validate_map(file) > 0)
		return (1);
	return (0);
}
