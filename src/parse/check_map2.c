/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maragao <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:54:04 by maragao           #+#    #+#             */
/*   Updated: 2023/08/02 17:54:06 by maragao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
