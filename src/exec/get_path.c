/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:26:37 by wnguyen           #+#    #+#             */
/*   Updated: 2024/02/08 13:56:45 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*search_in_path(char *cmd, char **paths)
{
	char	*full_path;
	char	*path_with_slash;
	int		i;

	full_path = NULL;
	i = 0;
	while (paths[i])
	{
		path_with_slash = ft_strjoin(paths[i], "/");
		if (!path_with_slash)
			return (NULL);
		full_path = ft_strjoin(path_with_slash, cmd);
		free(path_with_slash);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK | X_OK) != -1)
			break ;
		free(full_path);
		full_path = NULL;
		i++;
	}
	return (full_path);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*full_path;
	int		i;
	int		j;

	paths = NULL;
	full_path = NULL;
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (envp[i])
	{
		paths = ft_split(envp[i] + 5, ':');
		full_path = search_in_path(cmd, paths);
		j = 0;
		while (paths[j])
		{
			free(paths[j]);
			j++;
		}
		free(paths);
		if (!full_path)
			return (NULL);
	}
	return (full_path);
}

void	display_history(void)
{
	HIST_ENTRY	**the_history_list;
	int			i;

	i = 0;
	the_history_list = history_list();
	while (the_history_list[i])
	{
		printf("%d: %s\n", i + 1, the_history_list[i]->line);
		i++;
	}
}
