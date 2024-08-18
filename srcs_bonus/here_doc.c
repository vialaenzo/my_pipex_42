/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:34:39 by eviala            #+#    #+#             */
/*   Updated: 2024/08/18 16:43:01 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	args_in(char *arg, t_pipex *pipex)
{
	if (arg && !ft_strncmp("here_doc", arg, 8))
	{
		pipex->here_doc = 1;
		return (6);
	}
	else
	{
		pipex->here_doc = 0;
		return (5);
	}
}

void	here_doc(t_pipex *pipex)
{
	char *(buf);
	int (file) = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file < 0)
		ft_error("Here_doc Failed");
	while (1)
	{
		ft_printf(1, "heredoc> ");
		buf = get_next_line(0);
		if (!buf)
			break ;
		if (!ft_strncmp(pipex->argv[2], buf, ft_strlen(pipex->argv[2]))
			&& buf[ft_strlen(pipex->argv[2])] == '\n')
		{
			free(buf);
			break ;
		}
		ft_printf(file, "%s", buf);
		free(buf);
	}
	close(file);
	pipex->infile_char = ".heredoc_tmp";
}
