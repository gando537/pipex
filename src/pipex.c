/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 16:59:16 by mdiallo           #+#    #+#             */
/*   Updated: 2021/07/07 20:14:31 by mdiallo          ###   ########.fr       */
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

void	init_data(t_data *data, int **my_pipes, int argc, char **argv)
{
	if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0)
	{
		data->here_doc = 1;
		data->nb_pipes = argc - 5;
		data->i_fd = 0;
	}
	else
	{
		data->here_doc = 0;
		data->nb_pipes = argc - 4;
		data->i_fd = open(argv[1], O_RDONLY);
	}
	data->o_fd = 1;
	check_first_last(data, argc, argv, data->env);
	*my_pipes = creat_pipe(data->nb_pipes);
	data->j = 0;
}

void	exec_over(t_data *data, t_lst *tmp, int *my_pipes, t_lst **lst_cmd)
{
	check_last(data, tmp, my_pipes, lst_cmd);
	check_first(data, my_pipes, lst_cmd);
	exec_cmd(data, tmp, my_pipes, lst_cmd);
}

void	error_fork(t_data *data, t_lst **lst_cmd, int *my_pipes)
{
	all_free(data, lst_cmd, my_pipes);
	perror("error");
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc < 4)
	{
		ft_putstr_fd("Usage : - ./pipex infile cmd1...cmdn outfile\n", 2);
		ft_putstr_fd("\t-./pipex here_doc LIMITER cmd1...cmdn outfile\n", 2);
		return (0);
	}
	pipex(argc, argv, envp);
	return (0);
}
