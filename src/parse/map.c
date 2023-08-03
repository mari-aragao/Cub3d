/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maragao <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:54:26 by maragao           #+#    #+#             */
/*   Updated: 2023/08/03 19:33:49 by maragao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (str[0] == '\0')
		return (2);
	return (1);
}

int	get_map(t_file *file)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (file->file[i])
	{
		if (is_element(file->file[i]) == 0)
			count++;
		if (is_element(file->file[i]) == 1)
			break ;
		i++;
	}
	if (count != 6)
		return (1);
	file->height = file->file_lines - i;
	file->map = (char **) malloc(sizeof(char *) * (file->height + 1));
	j = -1;
	while (++j < file->height)
		file->map[j] = ft_strdup(file->file[i++]);
	file->map[j] = NULL;
	return (0);
}
