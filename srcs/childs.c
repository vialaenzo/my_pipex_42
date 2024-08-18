/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 15:45:04 by eviala            #+#    #+#             */
/*   Updated: 2024/08/18 12:12:22 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_child(char *str, char **cmd_args)
{
	ft_free_tab(cmd_args);
	ft_error(str);
}

void	both_child(t_pipex *pipex, char **cmd_args)
{
	char *(path) = NULL;
	if (!ft_check_is_path(cmd_args[0]))
	{
		if (pipex->env)
			path = get_path(cmd_args[0], pipex->env);
		else
			ft_free_child("Environment", cmd_args);
	}
	else
		path = ft_strdup(cmd_args[0]);
	if (!path)
		ft_free_child("Command argv[1] not found", cmd_args);
	if ((access(path, X_OK | F_OK) != 0))
	{
		free(path);
		ft_printf(2, "command not found : %s\n", cmd_args[0]);
		ft_free_tab(cmd_args);
		exit(1);
	}
	execve(path, cmd_args, pipex->env);
	free(path);
	ft_free_tab(cmd_args);
	exit(1);
}

void	first_child(t_pipex pipex)
{
	char	**cmd_args;

	close(pipex.pipe_fd[0]);
	dup2(pipex.pipe_fd[1], 1);
	close(pipex.pipe_fd[1]);
	int (fd) = open(pipex.argv[1], O_RDONLY);
	if (fd < 0)
		ft_error("Infile");
	dup2(fd, 0);
	close(fd);
	cmd_args = ft_split(pipex.argv[2], ' ');
	if (!(cmd_args))
		ft_error("CMDS_ARGS");
	both_child(&pipex, cmd_args);
}

void	second_child(t_pipex pipex)
{
	char	**cmd_args;

	close(pipex.pipe_fd[1]);
	dup2(pipex.pipe_fd[0], 0);
	close(pipex.pipe_fd[0]);
	int (fd) = open(pipex.argv[pipex.argc - 1], O_CREAT
			| O_RDWR | O_TRUNC, 0000644);
	if (fd < 0)
		ft_error("Outfile");
	dup2(fd, 1);
	close(fd);
	cmd_args = ft_split(pipex.argv[pipex.argc - 2], ' ');
	if (!(cmd_args))
		ft_error("CMD_ARGS");
	both_child(&pipex, cmd_args);
}
