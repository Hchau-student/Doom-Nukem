/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 18:17:38 by hchau             #+#    #+#             */
/*   Updated: 2019/05/18 17:22:36 by hchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int				read_this(int fd, char **line, char **str_fd)
{
	ssize_t				ret;
	char				buf[BUFF_SIZE + 1];
	char				*to_free;

	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		to_free = *line;
		if (!(ft_strchr(buf, '\n')))
			*line = ft_strjoin(*line, buf);
		if ((ft_strchr(buf, '\n')))
		{
			str_fd[fd] = ft_strcdup(buf, '\n');
			*line = ft_strjoin(*line, (str_fd[fd]));
			ft_strdel(&to_free);
			ft_strdel(&str_fd[fd]);
			str_fd[fd] = ft_strdup(ft_strchr(buf, '\n') + 1);
			ft_strdel(&to_free);
			return (1);
		}
		ft_strdel(&to_free);
	}
	if (*line[0] == '\0' && !ret)
		return (0);
	return (1);
}

int						get_next_line(int fd, char **line)
{
	static char			*str_fd[10000];
	char				*to_free;
	char				buf[BUFF_SIZE];

	if (fd < 0 || !line || BUFF_SIZE < 0 || (read(fd, buf, 0)) < 0)
		return (-1);
	*line = ft_strnew(0);
	to_free = *line;
	if (str_fd[fd] != NULL)
	{
		*line = ft_strcdup(str_fd[fd], '\n');
		ft_strdel(&to_free);
		if ((ft_strchr(str_fd[fd], '\n')))
		{
			to_free = str_fd[fd];
			str_fd[fd] = ft_strdup((ft_strchr(str_fd[fd], '\n') + 1));
			ft_strdel(&to_free);
			return (1);
		}
		free(str_fd[fd]);
		str_fd[fd] = NULL;
	}
	return ((read_this(fd, line, str_fd)));
}
