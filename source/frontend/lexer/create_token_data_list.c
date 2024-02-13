/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_data_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:30:35 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/02 21:07:33 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

bool	create_token_data_list(t_list **token_data_list, char *input_line)
{
	size_t	i;
	t_list	*new_node;
	char	*token_data;

	i = 0;
	while (input_line[i])
	{
		while (ft_strchr(WHITESPACE, input_line[i]) && input_line[i])
			i++;
		if (!input_line[i])
			break ;
		if (!set_token_data(&token_data, input_line, &i))
			return (false);
		if (!token_data)
			return (ft_lstclear(token_data_list, free), true);
		new_node = ft_lstnew(token_data);
		if (!new_node)
			return (free(token_data), false);
		ft_lstadd_back(token_data_list, new_node);
	}
	return (true);
}

bool	set_token_data(char **token_data, char *input_line, size_t *i)
{
	bool	is_missing_pair;
	size_t	start;

	start = *i;
	is_missing_pair = false;
	while (input_line[*i] && !is_missing_pair && \
		!ft_strchr(WHITESPACE, input_line[*i]))
	{
		if (input_line[*i] == '\'')
			is_missing_pair = !skip_single_quote(input_line, i);
		else if (input_line[*i] == '"')
			is_missing_pair = !skip_double_quote(input_line, i);
		else if (ft_strncmp(&input_line[*i], DOLLAR_BRACE, 2) == 0)
			is_missing_pair = !skip_dollar_brace(input_line, i, false);
		if (!is_missing_pair)
			(*i)++;
	}
	if (is_missing_pair)
		return (print_missing_pair_error(&input_line[*i]),
			*token_data = NULL, true);
	*token_data = ft_substr(input_line, start, *i - start);
	if (!*token_data)
		return (false);
	return (true);
}
