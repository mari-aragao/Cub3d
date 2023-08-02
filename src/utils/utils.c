/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maragao <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:57:32 by maragao           #+#    #+#             */
/*   Updated: 2023/08/02 17:57:33 by maragao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != 0 || s2[i] != 0)
	{
		if (s1[i] - s2[i] > 0 || s1[i] - s2[i] < 0)
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int	ft_strlen(char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strnstr(char *s1, char *s2, int n)
{
	int	i;
	int	j;

	if (*s2 == 0)
		return (s1);
	i = 0;
	while (i < n && s1[i] != 0)
	{
		j = 0;
		while (s1[i + j] == s2[j] && (i + j) < n)
		{
			j++;
			if (s2[j] == 0)
				return (((char *) s1) + i);
		}
		i++;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	boolean;

	i = 0;
	boolean = 0;
	result = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\t' || str[i] == '\v')
		i++;
	if (str[i] == '-')
	{
		boolean = 1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while ((str[i] >= '0' && str[i] <= '9') && str[i])
	{
		result = (result * 10) + str[i] - '0';
		i++;
	}
	if (boolean == 1)
		result *= -1;
	return (result);
}
