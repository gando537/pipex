/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 16:59:30 by mdiallo           #+#    #+#             */
/*   Updated: 2021/11/05 14:48:05 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static int	len_cmd(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
			j++;
		i++;
	}
	return (i);
}

void	free_split(char **split)
{
	int	len;
	int	i;

	if (!*split || !split)
		return ;
	i = 0;
	len = len_cmd(split);
	while (i < len)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_lst(t_lst **lst)
{
	t_lst	*tmp;

	if (!lst)
		return ;
	tmp = *lst;
	while (tmp)
	{
		free_split(tmp->cmd);
		if (tmp->path)
			free(tmp->path);
		tmp = tmp->next;
	}
	free(lst);
}

void	all_free(t_data *data, t_lst **lst_cmd)
{
	if (data->tmp)
		unlink(data->tmp);
	free_lst(lst_cmd);
	free(data->pipes);
	free(data);
}

void	ft_strdel(char **as)
{
	if (as && *as)
	{
		free(*as);
		*as = NULL;
	}
}
