/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:15:57 by edesaint          #+#    #+#             */
/*   Updated: 2024/02/01 15:44:02 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	sub_process_heredoc(t_env *env, t_node *node, char *delimiter)
{
	int	fd;

	node->redir_heredoc = get_name_heredoc();
	fd = open(node->redir_heredoc, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (false);
	get_and_save_heredoc_content(env, fd, delimiter);
	close(fd);
	return (true);
}

bool	update_redir(t_env *env, t_node *node, t_token *token)
{
	char	*name;

	name = get_name_redir(token);
	if (is_file_redir(token))
	{
		if (token->type_token == T_REDIR_IN)
			set_redir_in(node, name);
		if (token->type_token == T_REDIR_OUT)
			set_redir_out(node, name);
		if (token->type_token == T_REDIR_APPEND)
			set_redir_append(node, name);
		if (token->type_token == T_REDIR_HEREDOC)
			set_redir_heredoc(node, token, env, name);
	}
	return (true);
}

bool	init_redir(t_data *data, t_node *node, t_token *token)
{
	while (token && in_node(data, token))
	{
		if (!update_redir(data->env, node, token))
			return (perror("fd in redir failed !"), false);
		token = token->next;
	}
	return (true);
}
