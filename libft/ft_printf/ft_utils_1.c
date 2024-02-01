/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 07:15:00 by edesaint          #+#    #+#             */
/*   Updated: 2024/02/01 13:08:29 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_len(int n, int int_convert)
{
	int				len;
	unsigned int	nbr;

	len = 0;
	if (n == 0)
		return (1);
	if (!int_convert && n < 0)
	{
		if (n == INT_MIN)
			return (11);
		len++;
		n *= -1;
	}
	nbr = n;
	if (int_convert && n < 0)
		nbr = 4294967296 + n;
	while (nbr != 0)
	{
		len++;
		nbr /= 10;
	}
	return (len);
}