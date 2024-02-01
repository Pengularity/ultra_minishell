/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 20:07:13 by edesaint          #+#    #+#             */
/*   Updated: 2024/02/01 12:38:53 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*find_name_heredoc(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	if (i < 0)
		return (NULL);
	str[i] = 'a';
	while (str[i] <= 'z' && access(str, F_OK) == 0)
		str[i]++;
	return (str);
}

char	*get_name_heredoc(void)
{
	char	*temp;
	char	*new_temp;

	temp = malloc(6);
	if (!temp)
		return (NULL);
	ft_strcpy(temp, "/tmp/");
	while (access(temp, F_OK) == 0)
	{
		new_temp = ft_strjoin(temp, "a");
		free(temp);
		if (!new_temp)
			return (NULL);
		temp = find_name_heredoc(new_temp);
		if (!temp)
		{
			free(new_temp);
			return (NULL);
		}
	}
	return (temp);
}

void	get_and_save_heredoc_content(t_env *env, int fd, char *delimiter)
{
	char *line;

	line = readline("> ");
	while (line != NULL && ft_strcmp(line, delimiter) != 0 && errno != EINTR)
	{
		line = expand_string(env, line);
		write(fd, line, ft_strlen(line));
		free(line);
		line = readline("> ");
		if (!line && errno != EINTR && errno != EBADF)
			write(STDERR_FILENO, "\n", 1);
		if (errno == EINTR || errno == EBADF)
		{
			free (line);
			line = NULL;
			env->lst_exit = 128 + SIGINT;
		}
		write(fd, "\n", 1);
	}
}