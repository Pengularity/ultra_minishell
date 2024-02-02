/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:57:41 by wnguyen           #+#    #+#             */
/*   Updated: 2024/02/02 20:17:44 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	execute_command(t_node *node, char **envp, t_env *env)
{
	char	*cmd_path;

	if (ft_strchr(node->tab_exec[0], '/'))
		cmd_path = ft_strdup(node->tab_exec[0]);
	else
		cmd_path = get_cmd_path(node->tab_exec[0], envp);
	if (!cmd_path)
	{
		env->lst_exit = 127;
		ft_putstr_fd(node->tab_exec[0], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		free(cmd_path);
		return (false);
	}
	if (execve(cmd_path, node->tab_exec, envp) == -1)
	{
		perror("execve error");
		free(cmd_path);
		return (false);
	}
	return (true);
}

static bool	handle_output_redirection(t_node *node, int *pipe_fds)
{
	if (node->next && node->redir_out == NULL && node->redir_append == NULL)
	{
		if (pipe_fds[0] != -1)
			close(pipe_fds[0]);
		if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 error");
			return (false);
		}
		if (pipe_fds[1] != -1)
			close(pipe_fds[1]);
	}
	else if (node->next)
	{
		if (pipe_fds[1] != -1)
			close(pipe_fds[1]);
		if (pipe_fds[0] != -1)
			close(pipe_fds[0]);
	}
	return (true);
}

static bool	setup_child(t_node *node, int in_fd, int *pipe_fds)
{
	if (!exec_redir(node))
		return (false);
	if (in_fd != STDIN_FILENO)
	{
		if (dup2(in_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 error");
			return (false);
		}
		if (in_fd != -1)
			close(in_fd);
	}
	handle_output_redirection(node, pipe_fds);
	return (true);
}

void	exec_child_process(t_node *node, int in_fd, t_env *env, int *pipe_fds)
{
	char	**envp;
	int		exit_status;

	envp = convert_env_to_tab(env);
	exit_status = EXIT_FAILURE;
	if (setup_child(node, in_fd, pipe_fds))
	{
		if (is_builtin(node))
		{
			exec_builtin(node, env);
			exit_status = env->lst_exit;
		}
		else if (execute_command(node, envp, env))
			exit_status = EXIT_SUCCESS;
	}
	free_tab(envp);
	free_nodes(node);
	node = NULL;
	free_env(env);
	exit(exit_status);
}

void	manage_parent_process(int *in_fd, int *pipe_fds, t_node *current_node)
{
	if (*in_fd != STDIN_FILENO && *in_fd != -1)
		close(*in_fd);
	if (current_node->next != NULL)
	{
		if (pipe_fds[0] != -1)
			close(pipe_fds[1]);
		*in_fd = pipe_fds[0];
	}
	else
	{
		if (pipe_fds[1] != -1)
			close(pipe_fds[1]);
		if (pipe_fds[0] != -1)
			close(pipe_fds[0]);
		*in_fd = -1;
	}
}
