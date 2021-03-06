/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 16:20:24 by mdiallo           #+#    #+#             */
/*   Updated: 2021/11/04 11:37:39 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char const *s, int fd)
{
	while (*s)
		ft_putchar_fd(*s++, fd);
}

void	ft_putendl_fd(char const *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

void	get_next_line_bis(char **line, char *tmp, int l, char c)
{
	int		i;

	i = -1;
	while (++i < l - 2)
		tmp[i] = (*line)[i];
	tmp[i] = c;
	tmp[i + 1] = 0;
	free(*line);
	*line = tmp;
}

int	get_next_line(char **line, int fd)
{
	int		l;
	int		r;
	char	c;
	char	*tmp;

	r = 0;
	l = 1;
	*line = malloc(l);
	if (!*line)
		return (-1);
	(*line)[0] = 0;
	r = read(fd, &c, 1);
	while (r && l++ && c != '\n')
	{
		tmp = malloc(l);
		if (!tmp)
		{
			free(*line);
			return (-1);
		}
		get_next_line_bis(line, tmp, l, c);
		r = read(fd, &c, 1);
	}
	return (r);
}
