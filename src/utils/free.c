/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maragao <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:56:50 by maragao           #+#    #+#             */
/*   Updated: 2023/08/03 19:54:43 by maragao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	get_free(char **mat)
{
	int	i;

	if (!mat || mat == NULL)
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
}
