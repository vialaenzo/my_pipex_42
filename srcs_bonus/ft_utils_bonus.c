/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 10:49:39 by eviala            #+#    #+#             */
/*   Updated: 2024/08/15 12:18:19 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_error(char *str)
{
	perror(str);
	exit(1);
}

void	close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < (pipex->pipe_nbrs))
	{
		close(pipex->pipe[i]);
		i++;
	}
}

int	ft_check_is_path(char *cmd)
{
	if (!(ft_strchr(cmd, '/')))
		return (0);
	return (1);
}

void	get_infile(t_pipex *pipex)
{
	pipex->infile = open(pipex->infile_char, O_RDONLY);
	if (pipex->infile < 0)
	{
		pipe_free(pipex);
		ft_error("Infile invalid but pass");
	}
}

void	get_outfile(t_pipex *pipex)
{
	if (pipex->here_doc)
		pipex->outfile = open(pipex->argv[pipex->argc - 1], O_WRONLY
				| O_CREAT | O_APPEND, 0000644);
	else
		pipex->outfile = open(pipex->argv[pipex->argc - 1], O_CREAT
				| O_RDWR | O_TRUNC, 0000644);
	if (pipex->outfile < 0)
	{
		pipe_free(pipex);
		ft_error("Outfile invalid");
	}
}
