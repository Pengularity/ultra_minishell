/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:53:36 by wnguyen           #+#    #+#             */
/*   Updated: 2024/02/01 19:29:48 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_sigint(int signum)
{
	(void)signum;
	ft_putstr_fd("\n", STDERR_FILENO);
	if (g_signal == IN_PROMPT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (g_signal == IN_EXEC)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	g_signal = SIG_INT;
}

bool	handle_ctrl_d(char *input)
{
	if (input == NULL)
	{
		ft_putstr_fd("exit\n", 1);
		return (true);
	}
	return (false);
}
