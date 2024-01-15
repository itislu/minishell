/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table_type_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:27:56 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/14 15:09:04 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"

int	get_cmd_table_type_from_list(t_list_d *cmd_table_list)
{
	t_cmd_table	*cmd_table;

	if (!cmd_table_list || !cmd_table_list->content)
		return (C_NONE);
	cmd_table = cmd_table_list->content;
	return (cmd_table->type);
}

bool	is_control_op_cmd_table(int cmd_table_type)
{
	return (cmd_table_type == C_AND || cmd_table_type == C_OR || \
		cmd_table_type == C_PIPE);
}

bool	is_builtin(t_cmd_table *cmd_table)
{
	if (!cmd_table || !cmd_table->cmd_name)
		return (false);
	if (ft_strcmp(cmd_table->cmd_name, "echo") == 0 || \
		ft_strcmp(cmd_table->cmd_name, "env") == 0 || \
		ft_strcmp(cmd_table->cmd_name, "unset") == 0 || \
		ft_strcmp(cmd_table->cmd_name, "export") == 0 || \
		ft_strcmp(cmd_table->cmd_name, "cd") == 0 || \
		ft_strcmp(cmd_table->cmd_name, "pwd") == 0 || \
		ft_strcmp(cmd_table->cmd_name, "exit") == 0)
		return (true);
	return (false);
}

bool	is_scmd_in_pipeline(t_list_d *cmd_table_node)
{
	if (!cmd_table_node)
		return (false);
	if (get_cmd_table_type_from_list(cmd_table_node) == C_SIMPLE_CMD)
	{
		if (get_cmd_table_type_from_list(cmd_table_node->prev) != C_PIPE && \
			get_cmd_table_type_from_list(cmd_table_node->next) != C_PIPE)
			return (true);
	}
	return (false);
}