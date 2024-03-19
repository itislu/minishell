/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 10:33:59 by ldulling          #+#    #+#             */
/*   Updated: 2024/03/19 15:49:03 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

bool	is_operator(char *token_data)
{
	if (ft_strncmp(token_data, "&&", 2) == 0 || \
		ft_strncmp(token_data, "|", 1) == 0 || \
		ft_strncmp(token_data, "<", 1) == 0 || \
		ft_strncmp(token_data, ">", 1) == 0 || \
		ft_strncmp(token_data, "(", 1) == 0 || \
		ft_strncmp(token_data, ")", 1) == 0)
		return (true);
	return (false);
}

void	print_missing_pair_error(char *str)
{
	char	missing_pair;

	if (ft_strncmp(str, DOLLAR_BRACE, 2) == 0)
		missing_pair = CLOSING_BRACE;
	else
		missing_pair = *str;
	ft_dprintf(STDERR_FILENO, ERROR_LEXER_SYNTAX, PROGRAM_NAME, missing_pair);
}

void	skip_operator(char *token_data, size_t *i)
{
	if (token_data[*i] == '<' || token_data[*i] == '>' || \
		token_data[*i] == '|' || token_data[*i] == '&')
	{
		(*i)++;
		if (token_data[*i] == token_data[*i - 1])
			(*i)++;
	}
	else if (token_data[*i] == '(' || token_data[*i] == ')')
		(*i)++;
}

bool	split_token_node(t_list *lst_node1, size_t i)
{
	t_list	*lst_node2;
	t_token	*new_token;
	char	**token_data_node1;
	char	**token_data_split;

	token_data_node1 = &((t_token *)lst_node1->content)->data;
	token_data_split = ft_split_at_index(*token_data_node1, i);
	if (!token_data_split)
		return (false);
	free(*token_data_node1);
	*token_data_node1 = token_data_split[0];
	new_token = init_token_node(T_UNINITIALIZED, token_data_split[1]);
	free(token_data_split);
	if (!new_token)
		return (free(token_data_split[1]), false);
	lst_node2 = ft_lstnew(new_token);
	if (!lst_node2)
		return (free_token_node(new_token), false);
	ft_lstinsert_after(&lst_node1, lst_node2);
	return (true);
}
