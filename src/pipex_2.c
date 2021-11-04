/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 16:59:22 by mdiallo           #+#    #+#             */
/*   Updated: 2021/11/04 16:47:25 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	check_first(t_data *data, t_lst **lst_cmd)
{
	if (data->j != 0)
	{
		if (dup2(data->pipes[data->j - 2], 0) < 0)
		{
			all_free(data, lst_cmd);
			perror("dup2");
			exit(EXIT_FAILURE);
		}
	}
	else if (data->j == 0)
	{
		close(0);
		if (dup(data->i_fd) < 0)
		{
			all_free(data, lst_cmd);
			perror("dup");
			exit(EXIT_FAILURE);
		}
	}
}

void	check_last(t_data *data, t_lst *tmp, t_lst **lst_cmd)
{
	if (tmp->next)
	{
		if (dup2(data->pipes[data->j + 1], 1) < 0)
		{
			all_free(data, lst_cmd);
			perror("dup2");
			exit(EXIT_FAILURE);
		}
	}
	else if (tmp->next == NULL)
	{
		if (dup2(data->o_fd, 1) < 0)
		{
			all_free(data, lst_cmd);
			perror("dup2");
			exit(EXIT_FAILURE);
		}
	}
}

void	exec_cmd(t_data *data, t_lst *tmp, t_lst **lst_cmd)
{
	data->i = 0;
	while (data->i < 2 * data->nb_pipes)
	{
		close(data->pipes[data->i]);
		data->i++;
	}
	if (execve(tmp->path, tmp->cmd, data->env) < 0)
	{
		all_free(data, lst_cmd);
		perror(*(tmp->cmd));
		exit(EXIT_FAILURE);
	}
}

void	close_wait(t_data *data)
{
	data->k = 0;
	while (data->k < 2 * data->nb_pipes)
	{
		close(data->pipes[data->k]);
		data->k++;
	}
	data->l = 0;
	while (data->l < data->nb_pipes + 1)
	{
		wait(data->status);
		data->l++;
	}
}

void	check_first_last(t_data *data, int argc, char **argv)
{
	data->x = 3;
	if (data->heredoc)
	{
		data->o_fd = open(argv[argc - 1], O_WRONLY | O_APPEND | O_CREAT, 0777);
		data->x = 4;
	}
	else
		data->o_fd = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
}
