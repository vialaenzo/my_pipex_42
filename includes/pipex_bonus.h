/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:37:22 by eviala            #+#    #+#             */
/*   Updated: 2024/08/15 13:01:27 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		argc;
	char	*infile_char;
	char	*outfile_char;
	char	**env;
	char	**argv;
	char	**cmd_args;
	int		here_doc;
	pid_t	pid;
	int		cmd_nbrs;
	int		pipe_nbrs;
	int		*pipe;
	int		idx;
}			t_pipex;

void		get_infile(t_pipex *pipex);
void		get_outfile(t_pipex *pipex);
int			ft_error(char *str);
int			ft_check_is_path(char *cmd);
char		*get_path(char *cmd, char **env);
char		*verif_path_cmd(t_pipex *pipex);
void		parent_free(t_pipex *pipex);
void		child_free(t_pipex *pipex, char *path);
void		pipe_free(t_pipex *pipex);
void		close_pipes(t_pipex *pipex);
void		child(t_pipex *pipex);

/*_    _ ______ _____  ______   _____   ____   _____
 | |  | |  ____|  __ \|  ____| |  __ \ / __ \ / ____|
 | |__| | |__  | |__) | |__    | |  | | |  | | |
 |  __  |  __| |  _  /|  __|   | |  | | |  | | |
 | |  | | |____| | \ \| |____  | |__| | |__| | |____
 |_|  |_|______|_|  \_\______| |_____/ \____/ \_____|
                             ______
			    |______|                   */

void		here_doc(char *argv, t_pipex *pipex);
int			args_in(char *arg, t_pipex *pipex);

#endif
