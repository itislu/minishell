/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:28:20 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/23 19:02:55 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "utils.h"

bool	parse_step(t_pt_node *pt_entry,
	t_list **token_list, t_list **state_stack, t_list **parse_stack)
{
	bool		ret;

	ret = false;

	if (pt_entry && pt_entry->action == A_SHIFT)
		ret = parse_shift(ft_lstpop_front_content(token_list),
				state_stack, parse_stack, pt_entry->next_state);
	else if (pt_entry && pt_entry->action == A_REDUCE)
	{
		if (parse_reduce(state_stack, parse_stack, pt_entry) && \
			parse_goto(state_stack, get_token_from_stack(*parse_stack)->type))
			ret = true;
	}
	else
		ret = false;
	return (ret);
}

// TODO: Need to verify if the return value always be one of the operators
char	*get_error_token_data(t_list *token_list, t_list *parse_stack)
{
	char	*error_token_data;

	if (token_list)
		error_token_data = get_token_data_from_list(token_list);
	else
		error_token_data = get_ast_from_stack(parse_stack)->data;
	return (error_token_data);
}

void	report_syntax_error(t_list *token_list, t_list *parse_stack)
{
	ft_dprintf(2, "%s: syntax error near unexpected token `%s'\n",
		PROGRAM_NAME,
		get_error_token_data(token_list, parse_stack));
}

bool	parse(
	t_list **token_list, t_list **state_stack, t_list **parse_stack)
{
	bool		ret;
	t_pt_node	*pt_entry;

	ret = true;
	while (true)
	{
		print_token_list(*token_list);
		pt_entry = get_next_pt_entry(
				get_state_from_stack(*state_stack),
				get_token_type_from_list(*token_list),
				A_SHIFT | A_REDUCE | A_ACCEPT);
		if (pt_entry && pt_entry->action == A_ACCEPT)
			break ;
		if (!parse_step(pt_entry, token_list, state_stack, parse_stack))
		{
			report_syntax_error(*token_list, *parse_stack);
			ret = false;
			break ;
		}
		ft_free_and_null((void **)&pt_entry);
	}
	ft_free_and_null((void **)&pt_entry);
	return (ret);
}

t_ast	*extract_ast_from_parse_stack(t_list **parse_stack)
{
	t_ast	*ast;

	if (ft_lstsize(*parse_stack) != 2 || \
		get_ast_from_stack(*parse_stack)->type != T_END)
		return (NULL);
	drop_num_stack(parse_stack, 1, (void *)free_ast_node);
	ast = ft_lstpop_front_content(parse_stack);
	return (ast);
}

// TODO: Should we free the token_list here?
bool	ft_parse(t_shell *shell)
{
	t_list	*state_stack;
	t_list	*parse_stack;

	if (!init_parse(&state_stack, &parse_stack))
		return (false);
	if (!parse(&shell->token_list, &state_stack, &parse_stack))
		return (free_parse(&state_stack, &parse_stack), false);
	printf("ACCEPT\n");
	shell->ast = extract_ast_from_parse_stack(&parse_stack);
	ft_lstclear(&shell->token_list, free_token_node);
	return (free_parse(&state_stack, &parse_stack), true);
}
