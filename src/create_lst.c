/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 16:59:09 by mdiallo           #+#    #+#             */
/*   Updated: 2021/07/07 18:20:32 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

t_lst	*ft_new_elm(char *content, char **envp)
{
	t_lst	*new_maillon;

	new_maillon = malloc(sizeof(t_lst));
	if (!new_maillon)
		return (NULL);
	new_maillon->cmd = ft_split(content, ' ');
	new_maillon->path = get_path(envp, new_maillon->cmd[0], "PATH");
	new_maillon->next = NULL;
	return (new_maillon);
}

void	push_back(t_lst **lst, t_lst *new)
{
	t_lst		*p_lst;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	p_lst = *lst;
	while (p_lst->next != NULL)
		p_lst = p_lst->next;
	p_lst->next = new;
}

t_lst	**create_lst(int argc, char **argv, char **envp, t_data *data)
{
	int		i;
	t_lst	**new_lst;
	t_lst	*new_elm;

	new_lst = (t_lst **)malloc(sizeof(t_lst *));
	if (!new_lst)
		return (NULL);
	*new_lst = NULL;
	i = 0;
	while (i < argc - data->x)
	{
		if (data->here_doc == 0)
			new_elm = ft_new_elm(argv[i + 2], envp);
		else
			new_elm = ft_new_elm(argv[i + 3], envp);
		push_back(new_lst, new_elm);
		i++;
	}
	return (new_lst);
}

int	*creat_pipe(int nb_pipes)
{
	int	i;
	int	*_pipes;

	_pipes = (int *)malloc(sizeof(int) * 2 * nb_pipes);
	if (!_pipes)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < nb_pipes)
	{
		if (pipe(_pipes + i * 2) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (_pipes);
}
