/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanglai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 11:36:30 by clanglai          #+#    #+#             */
/*   Updated: 2018/03/14 13:47:16 by clanglai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			find_next_line(char *str)
{
	int i;
	
	i = 0;
	if (!str[i])
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int			get_next_line(const int fd, char **line)
{
	static char *save;
	int			ret;

	if (!save)
		save = ft_strnew(BUFF_SIZE);
	if (fd == -1 || line == NULL)
		return (-1);
	*line = ft_strdup(save);
	ret = 0;
	if (ft_strchr(save, '\n'))
		save = ft_strchr(save, '\n') + 1;
	else
	{
		ft_strclr(save);
		while ((ret = read(fd, save, BUFF_SIZE)) > 0)
		{
			save[ret] = '\0';
			*line = ft_strjoin(*line, save);
			if (find_next_line(*line) >= 0)
			{
				save = ft_strchr(save, '\n') + 1;
				break;
			}
		}
	}
	if (find_next_line(*line) != -1)
		(*line)[find_next_line(*line)] = '\0';
	if (ret < 0)
		return (-1);
	return (ret == 0 && ft_strlen(*line) == 0 ? 0 : 1);
}

int main(int argc, char **argv)
{
	char *line;
	int fd;

	fd = open(argv[argc - 1], O_RDONLY);
	while(get_next_line(fd, &line) == 1)
	{
	printf("%s\n", line);
		free(line);
	}
	free(line);
	return (0);
}
