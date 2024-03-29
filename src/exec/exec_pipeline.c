/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:04:50 by wnguyen           #+#    #+#             */
/*   Updated: 2024/02/01 13:42:35 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	init_pipe_fds(int *pipe_fds, t_node *node)
{
	if (node->next != NULL)
	{
		if (pipe(pipe_fds) == -1)
		{
			perror("pipe error");
			return (EXIT_FAILURE);
		}
	}
	else
	{
		pipe_fds[0] = -1;
		pipe_fds[1] = -1;
	}
	return (EXIT_SUCCESS);
}

void	finalize_pipeline(int last_pid, t_node **node, int *in_fd, t_env *env)
{
	int	status;

	if (*in_fd != -1)
		close(*in_fd);
	if (last_pid != -1)
	{
		waitpid(last_pid, &status, 0);
		if (WIFEXITED(status))
			env->lst_exit = WEXITSTATUS(status);
	}
	free_nodes(*node);
}

void	exec_pipeline(t_node *node, t_env *env)
{
	int		pipe_fds[2];
	int		last_pid;
	int		in_fd;
	t_node	*tmp;

	last_pid = -1;
	in_fd = STDIN_FILENO;
	while (node != NULL)
	{
		if (init_pipe_fds(pipe_fds, node) == -1)
			break ;
		last_pid = fork();
		if (last_pid == -1)
			break ;
		if (last_pid == 0)
			exec_child_process(node, in_fd, env, pipe_fds);
		else
			manage_parent_process(&in_fd, pipe_fds, node);
		tmp = node->next;
		free_node(node);
		node = tmp;
	}
	finalize_pipeline(last_pid, &node, &in_fd, env);
}
