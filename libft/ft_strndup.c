/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:46:45 by blax              #+#    #+#             */
/*   Updated: 2024/02/01 13:40:09 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strndup(const char *str, size_t n)
{
	size_t	slen;
	char	*result;
	size_t	i;

	slen = ft_strlen(str);
	if (n < slen)
		slen = n;
	result = (char *)malloc(sizeof(char) * (slen + 1));
	if (!result)
		return (0);
	i = 0;
	while (i < slen)
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
