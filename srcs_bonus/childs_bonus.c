/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 10:49:41 by eviala            #+#    #+#             */
/*   Updated: 2024/08/29 10:44:56 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// char	*verif_path_cmd(t_pipex *pipex)
// {
// 	char	*path;

// 	if (!ft_check_is_path(pipex->cmd_args[0]))
// 	{
// 		path = get_path(pipex->cmd_args[0], pipex->env);
// 	}
// 	else
// 	{
// 		if (access(pipex->cmd_args[0], F_OK | X_OK) == -1)
// 		{
// 			ft_free_tab(pipex->cmd_args);
// 			ft_error("Path Not Valide");
// 		}
// 		path = ft_strdup(pipex->cmd_args[0]);
// 	}
// 	if (!path)
// 	{
// 		ft_free_tab(pipex->cmd_args);
// 		ft_error("Command argv[1] not found");
// 	}
// 	return (path);
// }

char	*verif_path_cmd(t_pipex *pipex)
{
	char	*path;

	if (!ft_check_is_path(pipex->cmd_args[0]))
	{
		if (pipex->env)
			path = get_path(pipex->cmd_args[0], pipex->env);
		else
			return (perror("Environment"), NULL);
	}
	else
		path = ft_strdup(pipex->cmd_args[0]);
	if (!path)
	{
		ft_free_tab(pipex->cmd_args);
		ft_error("Command argv[1] not found");
	}
	if ((access(path, X_OK | F_OK) != 0))
	{
		free(path);
		ft_printf(2, "command not found : %s\n", pipex->cmd_args[0]);
		ft_free_tab(pipex->cmd_args);
		free(pipex->pipe);
		exit(1);
	}
	return (path);
}

static void	aux_dup2(int zero, int first, t_pipex *pipex)
{
	if (dup2(zero, 0) == -1 || dup2(first, 1) == -1)
	{
		pipe_free(pipex);
		if (pipex->idx == 0)
			close(pipex->infile);
		else if (pipex->idx == pipex->cmd_nbrs - 1)
			close(pipex->outfile);
		ft_error("dup2 failed");
	}
}

void	child(t_pipex *pipex)
{
	if (pipex->idx == 0)
	{
		get_infile(pipex);
		aux_dup2(pipex->infile, pipex->pipe[1], pipex);
		close(pipex->infile);
	}
	else if (pipex->idx == pipex->cmd_nbrs - 1)
	{
		get_outfile(pipex);
		aux_dup2(pipex->pipe[2 * pipex->idx - 2], pipex->outfile, pipex);
		close(pipex->outfile);
	}
	else
		aux_dup2(pipex->pipe[2 * pipex->idx - 2], pipex->pipe[2 * pipex->idx
			+ 1], pipex);
	close_pipes(pipex);
	pipex->cmd_args = ft_split(pipex->argv[2 + pipex->here_doc + pipex->idx],
			' ');
	if (!(pipex->cmd_args))
		ft_error("Memory Alloc Failed");
	char *(path) = verif_path_cmd(pipex);
	execve(path, pipex->cmd_args, pipex->env);
	child_free(pipex, path);
}

	// if (!(path))
	// 	child_free(pipex, path);
