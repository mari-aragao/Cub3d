/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maragao <maragao@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:47:53 by maragao           #+#    #+#             */
/*   Updated: 2023/07/08 17:15:02 by maragao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static char	*return_line(char *bank)
{
	int		i;
	char	*line;
	int		count;

	if (!(*bank))
		return (NULL);
	count = 0;
	while (bank[count] != '\n' && bank[count])
		count++;
	if (bank[count] == '\n')
		count++;
	i = -1;
	line = (char *)malloc(count + 1);
	if (!line)
		return (NULL);
	while (++i < count)
		line[i] = bank[i];
	line[count] = '\0';
	return (line);
}

static char	*last_static(char *bank)
{
	char	*aux;
	int		len_bank;
	int		i;
	int		j;

	len_bank = ft_strlen(bank);
	i = 0;
	while (bank[i] != '\n' && bank[i])
		i++;
	if (bank[i] == 0)
	{
		free(bank);
		return (NULL);
	}
	if (bank[i] == '\n')
		i++;
	aux = (char *) malloc(len_bank - i + 1);
	if (!aux)
		return (NULL);
	j = 0;
	while (bank[i])
		aux[j++] = bank[i++];
	aux[j] = '\0';
	free (bank);
	return (aux);
}

static char	*read_line(int fd, char *bank)
{
	char	*buffer;
	int		bytes_read;

	bytes_read = 1;
	buffer = (char *) malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (bytes_read > 0 && !ft_strchr_mod(bank))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free (buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		bank = ft_strjoin(bank, buffer);
	}
	free (buffer);
	return (bank);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*bank;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bank = read_line(fd, bank);
	if (!bank)
		return (NULL);
	line = return_line(bank);
	bank = last_static(bank);
	return (line);
}
