/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fd_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:23:40 by edesaint          #+#    #+#             */
/*   Updated: 2024/02/01 15:24:08 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	redir_in(t_node *node)
{
	int	fd_in;

	fd_in = open(node->redir_in, O_RDONLY);
	if (fd_in < 0)
		return (perror("open"), false);
	if (dup2(fd_in, STDIN_FILENO) < 0)
	{
		close(fd_in);
		return (perror("dup2"), false);
	}
	close(fd_in);
	return (true);
}

bool	redir_heredoc(t_node *node)
{
	int	fd_heredoc;

	fd_heredoc = open(node->redir_heredoc, O_RDONLY);
	if (fd_heredoc < 0)
		return (perror("open"), false);
	if (dup2(fd_heredoc, STDIN_FILENO) < 0)
	{
		unlink(node->redir_heredoc);
		close(fd_heredoc);
		return (perror("dup2"), false);
	}
	unlink(node->redir_heredoc);
	close(fd_heredoc);
	return (true);
}

bool	redir_out(int fd, const char *file, bool type_redir)
{
	int	file_fd;

	if (!type_redir)
		file_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		file_fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (file_fd < 0)
		return (perror("open"), false);
	if (dup2(file_fd, fd) < 0)
	{
		close(file_fd);
		return (perror("dup2"), false);
	}
	close(file_fd);
	return (true);
}