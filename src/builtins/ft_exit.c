/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 21:22:06 by wnguyen           #+#    #+#             */
/*   Updated: 2024/02/01 13:10:44 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_valid_exit_num(const char *str)
{
	int	i;
	int	num;

	i = 0;
	if (str[i] == '-')
		return (0);
	while (str[i] == '0')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	num = ft_atoi(str);
	if (num < 0 || num > 255)
		return (0);
	return (1);
}

static void	exit_with_error(char *arg)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	exit(2);
}

bool	ft_exit(t_node *node, t_env *env)
{
	char	**args;
	int		exit_status;

	args = node->tab_exec;
	exit_status = 0;
	if (!args[1])
	{
		env->lst_exit = 0;
		return (true);
	}
	if (!is_valid_exit_num(args[1]))
		exit_with_error(args[1]);
	if (args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		env->lst_exit = 1;
		return (false);
	}
	exit_status = ft_atoi(args[1]);
	env->lst_exit = exit_status;
	return (true);
}