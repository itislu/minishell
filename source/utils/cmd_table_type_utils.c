/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table_type_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:27:56 by lyeh              #+#    #+#             */
/*   Updated: 2024/06/07 09:38:55 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

bool	is_control_op_cmd_table(t_ct *cmd_table)
{
	if (!cmd_table)
		return (false);
	return (cmd_table->type == C_AND || cmd_table->type == C_OR || \
		cmd_table->type == C_PIPE);
}

bool	is_scmd_in_pipeline(t_list_d *cmd_table_node)
{
	if (!cmd_table_node)
		return (false);
	if (get_cmd_table_type_from_list(cmd_table_node) == C_SIMPLE_CMD)
	{
		if (get_cmd_table_type_from_list(cmd_table_node->prev) == C_PIPE || \
			get_cmd_table_type_from_list(cmd_table_node->next) == C_PIPE)
			return (true);
	}
	return (false);
}

t_ct_typ	get_cmd_table_type_from_list(t_list_d *cmd_table_list)
{
	if (!cmd_table_list || !cmd_table_list->content)
		return (C_NONE);
	return (((t_ct *)cmd_table_list->content)->type);
}

bool	is_builtin(char *cmd_name, t_sh *shell)
{
	if (!cmd_name)
		return (false);
	if (ft_strcmp(cmd_name, "echo") == 0 || \
		ft_strcmp(cmd_name, "env") == 0 || \
		ft_strcmp(cmd_name, "unset") == 0 || \
		ft_strcmp(cmd_name, "export") == 0 || \
		ft_strcmp(cmd_name, "cd") == 0 || \
		ft_strcmp(cmd_name, "pwd") == 0 || \
		ft_strcmp(cmd_name, "exit") == 0 || \
		(ft_strcmp(cmd_name, "~") == 0 && shell->is_interactive))
		return (true);
	return (false);
}
