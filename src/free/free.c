/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 12:33:07 by blax              #+#    #+#             */
/*   Updated: 2024/02/01 12:48:11 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void free_tab_exec(char **tab_exec)
{
    int i;

    if (!tab_exec)
        return ;
    i = 0;
    while (tab_exec[i])
	{
		free(tab_exec[i]);
		tab_exec[i] = NULL;
        i++;
	}
	free(tab_exec);
    tab_exec = NULL;
}

void free_redirs(t_node *node)
{
    if (node->redir_in)
    {
        free(node->redir_in);
        node->redir_in = NULL;
    }
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
}

void free_nodes(t_node *node)
{
    t_node *tmp_node;

    if (!node)
        return ;
    while (node)
    {
        tmp_node = node;
        node = node->next;
        free_tab_exec(tmp_node->tab_exec);
        free_redirs(tmp_node);
        free(tmp_node);
        tmp_node = NULL;
    }
}

void free_all(t_data *data)
{
    if (data)
    {
        free_tokens(data->token);
        free_nodes(data->node);
        free_data(data);
    }
}