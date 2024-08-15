/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 15:15:05 by eviala            #+#    #+#             */
/*   Updated: 2024/08/15 11:59:13 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_error(char *str)
{
	perror(str);
	exit(1);
}

void	close_pipes(t_pipex *pipex)
{
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
}

int	ft_check_is_path(char *cmd)
{
	if (!(ft_strchr(cmd, '/')))
		return (0);
	return (1);
}
