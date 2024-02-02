/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:04:08 by blax              #+#    #+#             */
/*   Updated: 2024/02/02 20:22:38 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	execute_single_child(t_node *node, t_env *env)
{
	char	**envp;

	if (!exec_redir(node))
		exit(EXIT_FAILURE);
	envp = convert_env_to_tab(env);
	if (!execute_command(node, envp, env))
	{
		free_tab(envp);
		free_node(node);
		free_env(env);
		exit(127);
	}
	free_tab(envp);
	free_node(node);
	free_env(env);
	exit(EXIT_SUCCESS);
}

bool	execute_single_cmd(t_node *node, t_env *env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		(perror("fork"), exit(EXIT_FAILURE));
	if (pid == 0)
		execute_single_child(node, env);
	else
	{
		free_node(node);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			env->lst_exit = WEXITSTATUS(status);
	}
	return (true);
}

static void	execute_exit_command(t_node *node, t_env *env)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (ft_exit(node, env))
	{
		free_node(node);
		free_env(env);
		exit(EXIT_SUCCESS);
	}
	else
		free_node(node);
}

static void	exec_single_builtin(t_node *node, t_env *env,
	int stdout_backup, int stdin_backup)
{
	if (!exec_redir(node))
		return (free_nodes(node));
	if (node->tab_exec[0] && ft_strcmp(node->tab_exec[0], "exit") == 0)
		execute_exit_command(node, env);
	else
	{
		exec_builtin(node, env);
		free_node(node);
	}
	if (dup2(stdout_backup, STDOUT_FILENO) < 0)
	{
		close(stdout_backup);
		perror("Error restoring STDOUT");
		exit(1);
	}
	if (dup2(stdin_backup, STDIN_FILENO) < 0)
	{
		close(stdin_backup);
		perror("Error restoring STDIN");
		exit(1);
	}
	close(stdout_backup);
	close(stdin_backup);
}

void	execute_command_node(t_node *node, t_env *env)
{
	int	stdout_backup;
	int	stdin_backup;

	g_signal = IN_EXEC;
	if (!node)
		return ;
	stdout_backup = dup(STDOUT_FILENO);
	stdin_backup = dup(STDIN_FILENO);
	if (!node->tab_exec || !node->tab_exec[0] || !node->type)
	{
		free_nodes(node);
		return ;
	}
	if (node->id == 0 && node->next == NULL && is_builtin(node))
		exec_single_builtin(node, env, stdout_backup, stdin_backup);
	else if (node->next != NULL)
		exec_pipeline(node, env);
	else
		execute_single_cmd(node, env);
}
