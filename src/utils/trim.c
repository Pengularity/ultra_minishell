/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:38:30 by edesaint          #+#    #+#             */
/*   Updated: 2024/02/01 14:10:39 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	nb_trim_left(char *str)
{
	int	i;

	i = 0;
	while (is_space(str[i]))
		i++;
	return (i);
}

int	nb_trim_right(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i >= 0 && is_space(str[i]))
		i--;
	return (++i);
}

char	*trim_str(char *str)
{
	int	start;
	int	end;

	if (!str)
		return (NULL);
	start = nb_trim_left(str);
	end = nb_trim_right(str);
	return (ft_substr(str, start, end));
}
