/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 11:51:05 by eviala            #+#    #+#             */
/*   Updated: 2024/08/15 13:01:08 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	child_free(t_pipex *pipex, char *path)
{
	if (path)
		free(path);
	ft_free_tab(pipex->cmd_args);
	ft_error("exit child");
}

void	pipe_free(t_pipex *pipex)
{
	close_pipes(pipex);
	free(pipex->pipe);
}
