/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 16:59:27 by mdiallo           #+#    #+#             */
/*   Updated: 2021/11/04 16:47:28 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	size;
	char	*p_s;
	char	*new_str;
	char	*p_new_str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	new_str = (char *)malloc(sizeof(char) * (size + 1));
	if (!new_str)
		return (NULL);
	p_s = s1;
	p_new_str = new_str;
	while (*p_s)
		*p_new_str++ = *p_s++;
	p_s = s2;
	while (*p_s)
		*p_new_str++ = *p_s++;
	*p_new_str = '\0';
	return (new_str);
}

char	*search_path(char **paths, char *cmd)
{
	int		i;
	char	*path;
	char	*part_path;

	i = 0;
	while (paths[i] && cmd[1] != '/')
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		ft_strdel(&part_path);
		if (access(path, F_OK) == 0)
			return (path);
		ft_strdel(&path);
		i++;
	}
	return (NULL);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (*s1 && *s1 == *s2 && --n)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	findi(char **src, char *to_find)
{
	int	i;

	i = 0;
	while (src[i] && ft_strncmp(src[i], to_find, ft_strlen(to_find)))
		i++;
	return (i);
}

char	*get_path(char **envp, char *cmd, char *path)
{
	char	**paths;
	char	*pth;
	int		i;

	i = findi(envp, path);
	paths = ft_split(envp[i] + 5, ':');
	pth = search_path(paths, cmd);
	free_split(paths);
	return (pth);
}
