/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 16:59:16 by mdiallo           #+#    #+#             */
/*   Updated: 2021/11/05 15:32:10 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

t_data	*alloc_data(void)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (0);
	return (data);
}

void	init_data(t_data *data, int argc, char **argv)
{
	data->tmp = (char *) NULL;
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		data->heredoc = 1;
		data->nb_pipes = argc - 5;
		data->limiter = argv[2];
		data->tmp = "/tmp/.heredoc";
	}
	else
	{
		data->nb_pipes = argc - 4;
		data->i_fd = open(argv[1], O_RDONLY);
	}
	data->o_fd = 1;
	check_first_last(data, argc, argv);
	data->pipes = creat_pipe(data->nb_pipes);
	data->j = 0;
}

void	exec_over(t_data *data, t_lst *tmp, t_lst **lst_cmd)
{
	check_last(data, tmp, lst_cmd);
	check_first(data, lst_cmd);
	exec_cmd(data, tmp, lst_cmd);
}

void	error_fork(t_data *data, t_lst **lst_cmd)
{
	all_free(data, lst_cmd);
	perror("error");
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	if (argc != 5)
	{
		ft_putstr_fd("Usage : - ./pipex infile cmd1...cmdn outfile\n", 2);
		ft_putstr_fd("\t-./pipex here_doc LIMITER cmd1...cmdn outfile\n", 2);
		return (0);
	}
	init(&data, argc, argv, envp);
	pipex(data, argc, argv, envp);
	return (0);
}
