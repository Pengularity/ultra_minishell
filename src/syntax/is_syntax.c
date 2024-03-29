/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 13:48:45 by edesaint          #+#    #+#             */
/*   Updated: 2024/02/01 14:08:52 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_syntax_char(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

bool	is_syntax(char c)
{
	return (is_space(c) || is_quote(c) || is_syntax_char(c));
}

bool	is_syntax_string(char *str)
{
	return (ft_strcmp(str, "|") == 0 || \
			ft_strcmp(str, ">") == 0 || \
			ft_strcmp(str, "<") == 0 || \
			is_syntax_redir(str));
}

bool	is_syntax_redir(char *str)
{
	return (ft_strcmp(str, ">") == 0 || \
		ft_strcmp(str, "<") == 0 || \
		ft_strcmp(str, ">>") == 0 || \
		ft_strcmp(str, "<<") == 0);
}
