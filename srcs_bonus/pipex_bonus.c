/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:33:44 by eviala            #+#    #+#             */
/*   Updated: 2024/08/18 16:34:57 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	pipe_gen(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_nbrs - 1)
	{
		if (pipe(pipex->pipe + 2 * i) < 0)
		{
			free(pipex->pipe);
			ft_error("Pipe Gen Failed");
		}
		i++;
	}
}

void	init_var_base(t_pipex *pipex, int argc, char **argv, char **env)
{
	pipex->argv = argv;
	pipex->env = env;
	pipex->argc = argc;
	pipex->idx = -1;
	pipex->infile_char = pipex->argv[1];
	pipex->outfile_char = pipex->argv[pipex->argc - 1];
	pipex->cmd_nbrs = pipex->argc - 3 - pipex->here_doc;
	pipex->pipe_nbrs = 2 * (pipex->cmd_nbrs - 1);
	pipex->pipe = (int *)malloc(sizeof(int) * pipex->pipe_nbrs);
	if (!(pipex->pipe))
		ft_error("Pipe malloc failed");
}

void	cleanup(t_pipex *pipex)
{
	if (pipex->pipe)
		free(pipex->pipe);
	if (pipex->here_doc)
		unlink(".heredoc_tmp");
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	if (argc < args_in(argv[1], &pipex))
		ft_error("Invalid Arguments");
	init_var_base(&pipex, argc, argv, env);
	if (pipex.argv[1] && !ft_strncmp("here_doc", pipex.argv[1], 8))
		here_doc(&pipex);
	pipe_gen(&pipex);
	while (++(pipex.idx) < pipex.cmd_nbrs)
	{
		pipex.pid = fork();
		if (!pipex.pid)
			child(&pipex);
	}
	close_pipes(&pipex);
	int (i) = 0;
	while ((++i) <= pipex.cmd_nbrs)
		wait(NULL);
	cleanup(&pipex);
	return (0);
}
