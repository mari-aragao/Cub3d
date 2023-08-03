/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maragao <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:57:25 by maragao           #+#    #+#             */
/*   Updated: 2023/08/03 17:11:47 by maragao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	*cpy_no_endl(char *s1)
{
	char	*ret;
	int		i;

	ret = (char *) malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (s1[i] && s1[i] != '\n')
	{
		ret[i] = s1[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

int	count_mat_size(char **mat)
{
	int	len;

	len = 0;
	while (mat[len])
		len++;
	return (len);
}

char	*ft_strdup(char *s)
{
	int		i;
	int		len;
	char	*ptr;

	if (!s || s == NULL)
		return (NULL);
	len = 0;
	while (s[len])
		len++;
	ptr = (char *) malloc((len + 1));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*strdup_mod(char *s, int n)
{
	int		i;
	char	*ptr;

	ptr = NULL;
	if (!s || s == NULL)
		return (NULL);
	ptr = (char *) malloc((n + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < n)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

void	print_mat(char **mat)
{
	int	i;

	i = 0;
	while (mat[i])
	{
		printf("%s\n", mat[i]);
		i++;
	}
}
