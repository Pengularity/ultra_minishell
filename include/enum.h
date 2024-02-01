/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:22:37 by blax              #+#    #+#             */
/*   Updated: 2024/02/01 17:45:17 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

typedef enum e_status {
	FAILURE = 0,
	SUCCESS = 1,
}	t_status;

typedef enum e_redir {
	IN = 0,
	OUT = 1,
}	t_redir;

typedef enum e_shell_state {
	IN_PROMPT = 1,
	IN_EXEC = 2,
	IN_HEREDOC = 3,
	SIG_INT = 4,
}	t_shell_state;

typedef enum e_state {
	T_NULL,
	T_COMMAND,
	T_ARGUMENT,
	T_PIPE,
	T_FILE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_REDIR_HEREDOC,
}	t_state;

typedef enum e_stick_token {
	S_NULL,
	S_QUOTE,
	D_QUOTE,
	S_CHAR,
	S_SYNTAX,
	S_SPACE,
}	t_stick_token;

#endif