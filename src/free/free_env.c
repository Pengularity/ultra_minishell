/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:02:01 by edesaint          #+#    #+#             */
/*   Updated: 2024/02/01 13:14:19 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void    free_env_link(t_env_link *link)
{
    if (link)
    {
        free(link->name);
        link->name = NULL;
        free(link->content);
        link->content = NULL;
        free(link);
        link = NULL;
    }
}

void    free_env(t_env *env)
{
    t_env_link    *current;
    t_env_link    *tmp;

    if (env && env->first)
    {
        current = env->first;
        while (current)
        {
            tmp = current;
            current = current->next;
            free_env_link(tmp);
        }
        free(env);
        env = NULL;
    }
}

void	free_node(t_node *node)
{
	if (!node)
		return ;
	free_tab_exec(node->tab_exec);
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
	free(node);
	node = NULL;
}

void	free_node_list(t_node *head)
{
	t_node	*current;
	t_node	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free_node(current);
		current = next;
	}
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}