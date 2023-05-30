#include "../../include/cub3d.h"

char	*get_next_line(int fd)
{
	int		i;
	int		bytes_read;
	char	c;
	char	*buff;

	buff = (char *) malloc (5000);
	i = 0;
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, &c, 1);
		if (bytes_read == 0 || bytes_read == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[i] = c;
		if (c == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	buff[i] = '\0';
	return (buff);
}
