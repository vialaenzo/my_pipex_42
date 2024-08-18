/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 10:49:40 by eviala            #+#    #+#             */
/*   Updated: 2024/08/18 12:11:39 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

char	**init_var(char *cmd, char **env, char ***s_cmd)
{
	char *(get_env_tmp) = my_getenv("PATH", env);
	if (!(get_env_tmp))
		return (NULL);
	char **(allpath) = ft_split(get_env_tmp, ':');
	if (!(allpath))
		return (NULL);
	*s_cmd = ft_split(cmd, ' ');
	if (!(s_cmd))
		return (ft_free_tab((allpath)), NULL);
	return (allpath);
}

char	*get_path(char *cmd, char **env)
{
	char	*exec;
	char	*path_part;
	char	**s_cmd;

	if (!cmd)
		return (NULL);
	int (i) = -1;
	char **(allpath) = init_var(cmd, env, &s_cmd);
	if (!(allpath))
		return (NULL);
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
