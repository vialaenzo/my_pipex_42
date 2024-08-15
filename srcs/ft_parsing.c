/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 15:15:29 by eviala            #+#    #+#             */
/*   Updated: 2024/08/11 17:40:15 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*my_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (sub && ft_strcmp(sub, name) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	char	*exec;
	char	*path_part;

	int (i) = -1;
	char **(allpath) = ft_split(my_getenv("PATH", env), ':');
	if (!(allpath))
		return (NULL);
	char **(s_cmd) = ft_split(cmd, ' ');
	if (!(s_cmd))
		return (ft_free_tab(allpath), NULL);
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		if (!(path_part))
			return (ft_free_tab(allpath), ft_free_tab(s_cmd), NULL);
		exec = ft_strjoin(path_part, s_cmd[0]);
		if (!(exec))
			return (free(path_part), ft_free_tab(allpath), ft_free_tab(s_cmd),
				NULL);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
			return (ft_free_tab(allpath), ft_free_tab(s_cmd), exec);
		free(exec);
	}
	return (ft_free_tab(allpath), ft_free_tab(s_cmd), ft_strdup(cmd));
}
