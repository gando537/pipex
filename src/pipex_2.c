/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 16:59:22 by mdiallo           #+#    #+#             */
/*   Updated: 2021/07/07 20:07:15 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	check_first(t_data *data, int *my_pipes, t_lst **lst_cmd)
{
	if (data->j != 0)
	{
		if (dup2(my_pipes[data->j - 2], 0) < 0)
		{
			all_free(data, lst_cmd, my_pipes);
			perror("dup2");
			exit(EXIT_FAILURE);
		}
	}
	else if (data->j == 0 && data->here_doc == 0)
	{
		close(0);
		if (dup(data->i_fd) < 0)
		{
			all_free(data, lst_cmd, my_pipes);
			perror("dup");
			exit(EXIT_FAILURE);
		}
	}
}

void	check_last(t_data *data, t_lst *tmp, int *my_pipes, t_lst **lst_cmd)
{
	if (tmp->next)
	{
		if (dup2(my_pipes[data->j + 1], 1) < 0)
		{
			all_free(data, lst_cmd, my_pipes);
			perror("dup2");
			exit(EXIT_FAILURE);
		}
	}
	else if (tmp->next == NULL)
	{
		if (dup2(data->o_fd, 1) < 0)
		{
			all_free(data, lst_cmd, my_pipes);
			perror("dup2");
			exit(EXIT_FAILURE);
		}
	}
}

void	exec_cmd(t_data *data, t_lst *tmp, int *my_pipes, t_lst **lst_cmd)
{
	data->i = 0;
	while (data->i < 2 * data->nb_pipes)
	{
		close(my_pipes[data->i]);
		data->i++;
	}
	if (execve(tmp->path, tmp->cmd, data->env) < 0)
	{
		all_free(data, lst_cmd, my_pipes);
		perror(*(tmp->cmd));
		exit(EXIT_FAILURE);
	}
}

void	close_wait(t_data *data, int *my_pipes)
{
	data->k = 0;
	while (data->k < 2 * data->nb_pipes)
	{
		close(my_pipes[data->k]);
		data->k++;
	}
	data->l = 0;
	while (data->l < data->nb_pipes + 1)
	{
		wait(data->status);
		data->l++;
	}
}

void	check_first_last(t_data *data, int argc, char **argv, char **envp)
{
	char	**tmp;
	char	*path;

	data->x = 3;
	tmp = ft_split(argv[argc - 1], ' ');
	path = get_path(envp, tmp[0], "PATH");
	if (path == NULL && data->here_doc == 1)
	{
		data->o_fd = open(argv[argc - 1], O_WRONLY | O_APPEND | O_CREAT, 0777);
		data->x = 4;
	}
	else if (path == NULL)
		data->o_fd = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	else
	{
		data->nb_pipes += 1;
		if (data->here_doc == 0)
			data->x = 2;
	}
	free(path);
	free_split(tmp);
}
