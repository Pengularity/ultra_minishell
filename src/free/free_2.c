/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 22:31:24 by edesaint          #+#    #+#             */
/*   Updated: 2024/02/01 13:50:53 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free_tab(char **s, int i)
{
	while (i-- > 0)
	{
		if (s[i])
		{
			free(s[i]);
			s[i] = NULL;
		}
	}
	free(s);
}

void	free_tokens(t_token *token)
{
	t_token	*tmp_token;

	if (!token)
		return ;
	while (token)
	{
		tmp_token = token->next;
		if (token->str)
		{
			free(token->str);
			token->str = NULL;
		}
		free(token);
		token = tmp_token;
	}
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->str)
	{
		free(data->str);
		data->str = NULL;
	}
	free(data);
	data = NULL;
}
