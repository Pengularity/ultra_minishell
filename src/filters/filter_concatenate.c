/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_concatenate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 22:33:37 by edesaint          #+#    #+#             */
/*   Updated: 2024/02/01 13:54:40 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_merge_token(t_token *token)
{
	if (is_syntax_string(token->next->str) || \
		is_syntax_string(token->str))
	{
		return (false);
	}
	while (token && token->next && !is_space_between_tokens(token))
		merge_token(token, token->next);
	return (true);
}

bool	filter_concatenate(t_token *token)
{
	while (token && token->next)
	{
		ft_merge_token(token);
		token = token->next;
	}
	return (true);
}

bool	is_space_between_tokens(t_token *token)
{
	if (token && token->next)
	{
		if (token->next->is_space)
			return (true);
	}
	return (false);
}

bool	merge_token(t_token *dst, t_token *src)
{
	if (!dst || !src)
		return (false);
	dst->is_space = 0;
	dst->next = src->next;
	dst->type_rstick = src->type_rstick;
	dst->str = merge_token_str(dst, src);
	free(src);
	src = NULL;
	return (true);
}

char	*merge_token_str(t_token *dst, t_token *src)
{
	int		len_new_str;
	char	*new_str;

	len_new_str = ft_strlen(dst->str) + ft_strlen(src->str) + 1;
	new_str = malloc (sizeof(char) * len_new_str);
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, dst->str, len_new_str);
	ft_strlcat(new_str, src->str, len_new_str);
	free(dst->str);
	dst->str = NULL;
	free(src->str);
	src->str = NULL;
	return (new_str);
}
