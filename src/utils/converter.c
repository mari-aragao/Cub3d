/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maragao <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:56:44 by maragao           #+#    #+#             */
/*   Updated: 2023/08/02 17:56:45 by maragao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	*decimal_to_hexa(int *decimal)
{
	int		i;
	int		j;
	int		quo;
	int		res;
	char	*hexa;

	hexa = (char *) malloc(sizeof(char) * 7);
	i = -1;
	j = -1;
	while (++j, ++i < 3)
	{
		quo = decimal[i] / 16;
		if (quo < 10)
			hexa[j] = quo + '0';
		else
			hexa[j] = (quo - 10) + 'A';
		res = decimal[i] % 16;
		j++;
		if (res < 10)
			hexa[j] = res + '0';
		else
			hexa[j] = (res - 10) + 'A';
	}
	hexa[6] = '\0';
	return (hexa);
}

int	hexa_to_decimal(char *hexa)
{
	int	i;
	int	decimal;

	i = 0;
	decimal = 0;
	while (i < 6)
	{
		if (hexa[i] >= '0' && hexa[i] <= '9')
			decimal = decimal * 16 + (hexa[i] - '0');
		else if (hexa[i] >= 'A' && hexa[i] <= 'F')
			decimal = decimal * 16 + (hexa[i] - 'A' + 10);
		i++;
	}
	return (decimal);
}

void	calculate_decimal_color(t_file *file)
{
	char	*hexa_color;

	hexa_color = decimal_to_hexa(file->ceiling);
	file->dec_ceiling = hexa_to_decimal(hexa_color);
	free(hexa_color);
	hexa_color = decimal_to_hexa(file->floor);
	file->dec_floor = hexa_to_decimal(hexa_color);
	free(hexa_color);
}
