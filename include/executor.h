/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:05:16 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/11 21:14:13 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "defines.h"

void	ft_executor(t_shell *shell);

bool	ft_heredoc(t_list_d *cmd_table_list);

void	handle_process(t_shell *shell, t_list_d *cmd_table_node);
void	handle_subshell(t_shell *shell, t_list_d **cmd_table_node);
void    handle_control_op(t_shell *shell, t_list_d **cmd_table_node);
void	handle_pipeline(t_shell *shell, t_list_d **cmd_table_list);
void	handle_simple_cmd(t_shell *shell, t_list_d **cmd_table_list);
void    handle_builtin(t_shell *shell, t_list_d **cmd_table_node);

/* Error checker */
bool	check_executable(char *filename);
bool	check_file(char *filename, int o_flag, int permission);

/* Utils */
char	*get_exec_path(char *cmd_name, char **envp);

/* Redirection - Pipe */
bool	setup_subshell_pipe(t_list_d *cmd_table_node);
bool	setup_normal_pipe(t_list_d *cmd_table_node);

#endif