/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 16:59:49 by mdiallo           #+#    #+#             */
/*   Updated: 2021/11/04 15:09:04 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_ind
{
	int	i;
	int	j;
	int	w_len;
}t_ind;

typedef struct s_lst
{
	char			**cmd;
	char			*path;
	struct s_lst	*next;
}t_lst;

typedef struct s_data
{
	int		*status;
	int		i;
	int		j;
	int		k;
	int		l;
	int		x;
	int		i_fd;
	int		o_fd;
	pid_t	pid;
	int		*pipes;
	int		nb_pipes;
	int		heredoc;
	char	**env;
	char	*limiter;
	char	*tmp;
}t_data;

void		pipex(t_data *data, int argc, char **argv, char **envp);
int			*creat_pipe(int nb_pipes);
void		push_back(t_lst **lst, t_lst *new);
t_lst		**create_lst(int argc, char **argv, char **envp, t_data *data);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_path(char *cmd, char **envp);
t_lst		*ft_new_elm(char *content, char **envp);
size_t		ft_strlen(char *str);
char		**ft_split(char *s, char c);
void		free_split(char **split);
void		free_lst(t_lst **lst);
int			ft_strcmp(char *s1, char *s2);
t_data		*alloc_data(void);
void		ft_strdel(char **as);
void		ft_putstr_fd(char const *s, int fd);
void		init_data(t_data *data, int argc, char **argv);
void		exec_over(t_data *data, t_lst *tmp, t_lst **lst_cmd);
void		error_fork(t_data *data, t_lst **lst_cmd);
int			get_next_line(char **line, int fd);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*get_path(char **envp, char *cmd, char *pathconf);
void		all_free(t_data *data, t_lst **lst_cmd);
void		check_first_last(t_data *data, int argc, char **argv);
void		close_wait(t_data *data);
void		exec_cmd(t_data *data, t_lst *tmp, t_lst **lst_cmd);
void		check_last(t_data *data, t_lst *tmp, t_lst **lst_cmd);
void		check_first(t_data *data, t_lst **lst_cmd);
void		ft_putendl_fd(char const *s, int fd);
void		init(t_data **data, int argc, char **argv, char **envp);

#endif
