/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:54:32 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/20 18:09:34 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include "utils.h"

bool	create_token_list(t_list **token_list, t_list **token_data_list)
{
	t_list	*new_nodes;
	t_token	*token;

	new_nodes = NULL;
	while (*token_data_list)
	{
		token = init_token_node(T_UNINITIALIZED, (*token_data_list)->content);
		if (!token)
			break ;
		new_nodes = ft_lstnew(token);
		if (!new_nodes || !separate_operators(new_nodes, 0))
			break ;
		ft_lstadd_back(token_list, new_nodes);
		free(ft_lstpop(token_data_list));
	}
	if (*token_data_list)
		return (ft_lstclear(token_data_list, free), free_token_node(token), \
				ft_lstclear(&new_nodes, free), false);
	return (true);
}

bool	separate_operators(t_list *lst_node, size_t i)
{
	char	*token_data;

	token_data = ((t_token *) lst_node->content)->data;
	while (token_data[i])
	{
		if (ft_strchr(TOK_SYMBOLS, token_data[i]))
		{
			if (i == 0)
				skip_operator(token_data, &i);
			if (token_data[i])
			{
				if (!split_node(lst_node, i))
					return (false);
				lst_node = lst_node->next;
				token_data = ((t_token *) lst_node->content)->data;
				i = 0;
			}
		}
		else if (ft_strchr(QUOTES, token_data[i]))
			skip_past_same_quote(token_data, &i);
		else
			i++;
	}
	return (true);
}

bool	add_end_node(t_list	**token_list)
{
	t_list	*new_node;
	t_token	*token;

	token = init_token_node(T_END, NULL);
	if (!token)
		return (false);
	new_node = (ft_lstnew(token));
	if (!new_node)
		return (free(token), false);
	ft_lstadd_back(token_list, new_node);
	return (true);
}
