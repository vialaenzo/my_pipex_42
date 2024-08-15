/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:37:22 by eviala            #+#    #+#             */
/*   Updated: 2024/08/15 11:59:23 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipe_fd[2];
	int		argc;
	char	*infile;
	char	*outfile;
	char	**argv;
	char	**env;
}		t_pipex;

int		ft_error(char *str);
int		ft_check_is_path(char *cmd);
char	*get_path(char *cmd, char **env);
void	close_pipes(t_pipex *pipex);
void	first_child(t_pipex pipex);
void	second_child(t_pipex pipex);
#endif
