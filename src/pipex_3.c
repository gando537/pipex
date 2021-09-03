/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 16:26:46 by mdiallo           #+#    #+#             */
/*   Updated: 2021/07/07 20:13:43 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	limiter(char *str)
{
	char	*readop;
	int		r;

	while (1)
	{
		ft_putstr_fd("pipe heredoc> ", 1);
		r = get_next_line(&readop, 0);
		if (ft_strncmp(str, readop, ft_strlen(readop)) == 0)
		{
			free(readop);
			return ;
		}
		free(readop);
	}
}

void	pipex(int argc, char **argv, char **envp)
{
	int		*my_pipes;
	t_data	*data;
	t_lst	**lst_cmd;
	t_lst	*tmp;

	data = alloc_data();
	data->env = envp;
	init_data(data, &my_pipes, argc, argv);
	lst_cmd = create_lst(argc, argv, envp, data);
	tmp = *lst_cmd;
	while (tmp)
	{
		data->pid = fork();
		if (data->pid == 0)
			exec_over(data, tmp, my_pipes, lst_cmd);
		else if (data->pid < 0)
			error_fork(data, lst_cmd, my_pipes);
		tmp = tmp->next;
		data->j += 2;
	}
	if (data->here_doc == 1)
		limiter(argv[2]);
	close_wait(data, my_pipes);
	all_free(data, lst_cmd, my_pipes);
}
