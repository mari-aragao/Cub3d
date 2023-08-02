/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maragao <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:56:57 by maragao           #+#    #+#             */
/*   Updated: 2023/08/02 17:56:59 by maragao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	mat_len(char *s, char c)
{
	int	len;
	int	w_found;

	len = 0;
	w_found = 0;
	while (s && *s)
	{
		if (*s != c && w_found == 0)
		{
			len++;
			w_found = 1;
		}
		if (*s == c)
			w_found = 0;
		s++;
	}
	return (len);
}

static char	**name_split(char **mat, char *s, char c, int mat_size)
{
	int	i;
	int	mat_count;

	mat_count = 0;
	while (*s && mat_count < mat_size)
	{
		i = 0;
		while (s[i] != c && s[i])
			i++;
		mat[mat_count] = strdup_mod(s, i);
		if (!mat[mat_count])
			return (NULL);
		while (s[i] == c)
			i++;
		mat_count++;
		s += i;
	}
	mat[mat_count] = NULL;
	return (mat);
}

char	**ft_split(char *s, char c)
{
	char	**mat;
	int		mat_size;

	if (!s)
		return (NULL);
	while (*s && *s == c)
		s++;
	mat_size = mat_len(s, c);
	mat = (char **) malloc((mat_size + 1) * sizeof(char *));
	if (!mat)
		return (NULL);
	mat = name_split(mat, s, c, mat_size);
	return (mat);
}
