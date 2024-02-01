/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tab_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 15:22:04 by edesaint          #+#    #+#             */
/*   Updated: 2024/02/01 12:55:31 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char **create_tab_exec(t_data *data, t_token *token, int nb_args)
{
    char **tab_exec;
    int i;

    i = 0;
    if (!token)
        return (NULL);
    tab_exec = malloc(sizeof(char *) * (nb_args + 1));
    if (!tab_exec)
        return (NULL);
    tab_exec[0] = get_command(token);
    if (!tab_exec[0])
        return (free_tab(tab_exec), NULL);
    i++;
    token = token->next;
    while (i < nb_args)
    {
        tab_exec[i] = get_argument(data, token);
        if (!tab_exec[i])
            return (perror("Erreur: argument"), ft_free_tab(tab_exec, i), NULL);
        token = token->next;
        i++;
    }
    tab_exec[i] = NULL;
    return (tab_exec);
}

char **init_tab_exec(t_data *data, t_token *token)
{
    int nb_args;

    nb_args = compt_args(data);
    if (nb_args < 0)
        return (NULL);
    return (create_tab_exec(data, token, nb_args));
}