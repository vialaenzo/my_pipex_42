/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:02:50 by eviala            #+#    #+#             */
/*   Updated: 2024/08/17 13:32:47 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	initialiation_var(int argc, char **argv, char **env, t_pipex *pipex)
{
	pipex->infile = argv[1];
	pipex->outfile = argv[argc -1];
	pipex->argv = argv;
	pipex->env = env;
	pipex->argc = argc;
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	if (argc != 5)
		return (ft_error("infile cm1 cm2 outfile"), 1);
	initialiation_var(argc, argv, env, &pipex);
	if (pipe(pipex.pipe_fd) < 0)
		ft_error("Pipe Failed");
	pipex.pid1 = fork();
	if ((pipex.pid1 < 0))
		ft_error("Fork Failed");
	if (pipex.pid1 == 0)
		first_child(pipex);
	pipex.pid2 = fork();
	if ((pipex.pid2 < 0))
		ft_error("Fork Failed");
	if (pipex.pid2 == 0)
		second_child(pipex);
	close_pipes(&pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	return (0);
}
