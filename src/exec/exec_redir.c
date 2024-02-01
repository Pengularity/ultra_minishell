/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:15:34 by wnguyen           #+#    #+#             */
/*   Updated: 2024/02/01 15:25:20 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	exec_redir(t_node *node)
{
	if (!exec_redir_1(node))
		return (false);
	if (!exec_redir_2(node))
		return (false);
	return (true);
}

bool	exec_redir_1(t_node *node)
{
	if (node->redir_in)
	{
		if (is_empty_file(node->redir_in) || \
			!is_redir_in(node->redir_in) || \
			!redir_in(node))
		{
			return (false);
		}
	}
	if (node->redir_out)
	{
		if (is_empty_file(node->redir_out)
			|| !is_redir_out(node->redir_out, 0)
			|| !redir_out(STDOUT_FILENO, node->redir_out, 0))
		{
			return (false);
		}
	}	
	return (true);
}

bool	exec_redir_2(t_node *node)
{
	if (node->redir_append)
	{
		if (is_empty_file(node->redir_append) || \
			!is_redir_out(node->redir_append, 1) || \
			!redir_out(STDOUT_FILENO, node->redir_append, 1))
		{
			return (false);
		}
	}
	if (node->redir_heredoc)
	{
		if (is_empty_file(node->redir_heredoc) || \
			!is_redir_in(node->redir_heredoc) || \
			!redir_heredoc(node))
		{
			return (false);
		}
	}
	return (true);
}
