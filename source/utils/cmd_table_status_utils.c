/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table_status_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:33:43 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/14 15:11:14 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"

t_cmd_table	*get_last_simple_cmd_table(t_list_d *cmd_table_list)
{
	t_cmd_table	*last_simple_cmd_table;
	int			cur_type;

	last_simple_cmd_table = NULL;
	while (cmd_table_list && cmd_table_list->content)
	{
		cur_type = ((t_cmd_table *)cmd_table_list->content)->type;
		if (cur_type == C_PIPE || cur_type == C_AND || cur_type == C_OR)
			last_simple_cmd_table = NULL;
		else if (cur_type == C_SIMPLE_CMD || cur_type == C_NONE)
			last_simple_cmd_table = cmd_table_list->content;
		cmd_table_list = cmd_table_list->next;
	}
	return (last_simple_cmd_table);
}