/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_set_redirs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:41:59 by edesaint          #+#    #+#             */
/*   Updated: 2024/02/01 15:54:50 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_redir_in(t_node *node, char *name)
{
	if (node->redir_heredoc)
	{
		free(node->redir_heredoc);
		node->redir_heredoc = NULL;
	}
	if (node->redir_in)
	{
		free(node->redir_in);
		node->redir_in = NULL;
	}
	node->redir_in = name;
}

void	set_redir_out(t_node *node, char *name)
{
	if (node->redir_append)
	{
		free(node->redir_append);
		node->redir_append = NULL;
	}
	if (node->redir_out)
	{
		free(node->redir_out);
		node->redir_out = NULL;
	}
	node->redir_out = name;
}

void	set_redir_append(t_node *node, char *name)
{
	if (node->redir_out)
	{
		free(node->redir_out);
		node->redir_out = NULL;
	}
	if (node->redir_append)
	{
		free(node->redir_append);
		node->redir_append = NULL;
	}
	node->redir_append = name;
}

bool	set_redir_heredoc(t_node *node, t_token *token, t_env *env, char *name)
{
	if (node->redir_in)
	{
		free(node->redir_in);
		node->redir_in = NULL;
	}
	if (node->redir_heredoc)
	{
		free(node->redir_heredoc);
		node->redir_heredoc = NULL;
	}
	free(name);
	if (!sub_process_heredoc(env, node, token->next->str))
		return (false);
	return (true);
}