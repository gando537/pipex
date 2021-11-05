/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 16:26:46 by mdiallo           #+#    #+#             */
/*   Updated: 2021/11/05 14:43:33 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	limiter(t_data *data)
{
	char	*readop;
	int		r;

	while (1)
	{
		ft_putstr_fd("pipe heredoc> ", 1);
		r = get_next_line(&readop, 0);
		if (ft_strcmp(data->limiter, readop) == 0 && ft_strlen(readop) != 0)
		{
			free(readop);
			close(data->i_fd);
			return ;
		}
		ft_putendl_fd(readop, data->i_fd);
		free(readop);
	}
}

void	init(t_data **data, int argc, char **argv, char **envp)
{
	*data = alloc_data();
	(*data)->env = envp;
	(*data)->heredoc = 0;
	init_data(*data, argc, argv);
	if ((*data)->heredoc)
	{
		(*data)->i_fd = open((*data)->tmp, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		limiter(*data);
		(*data)->i_fd = open((*data)->tmp, O_RDONLY);
	}
}

void	pipex(t_data *data, int argc, char **argv, char **envp)
{
	t_lst	**lst_cmd;
	t_lst	*tmp;

	lst_cmd = create_lst(argc, argv, envp, data);
	tmp = *lst_cmd;
	while (tmp)
	{
		data->pid = fork();
		if (data->pid == 0)
			exec_over(data, tmp, lst_cmd);
		else if (data->pid < 0)
			error_fork(data, lst_cmd);
		tmp = tmp->next;
		data->j += 2;
	}
	close_wait(data);
	all_free(data, lst_cmd);
}
