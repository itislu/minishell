/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:28:20 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/01 21:56:24 by ldulling         ###   ########.fr       */
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
	ft_dprintf(STDERR_FILENO, ERROR_PARSER_SYNTAX,
		PROGRAM_NAME, get_error_token_data(token_list, parse_stack));
}

bool	parse(
	t_list **token_list, t_list **state_stack, t_list **parse_stack)
{
	bool		ret;
	t_pt_node	*pt_entry;

	ret = true;
	while (true)
	{
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
		free(pt_entry);
	}
	free(pt_entry);
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

// TODO: dup the token_list in parse() or init_parse()?
// TODO: Need to refactor the code if AST is not necessary
bool	ft_parse(t_shell *shell)
{
	t_list	*state_stack;
	t_list	*parse_stack;
	t_list	*token_list;

	token_list = dup_token_list(shell->token_list);
	if (!token_list)
		return (false);
	if (!init_parse(&state_stack, &parse_stack))
		return (ft_lstclear(&token_list, (void *)free_token_node), false);
	if (!parse(&token_list, &state_stack, &parse_stack))
		return (ft_lstclear(&token_list, (void *)free_token_node),
			free_parse(&state_stack, &parse_stack), false);
	printf("ACCEPT\n");
	shell->cmd_table_list = build_cmd_table_list(shell->token_list);
	free_parse(&state_stack, &parse_stack);
	ft_lstclear(&shell->token_list, (void *)free_token_node);
	if (!shell->cmd_table_list)
		return (false);
	return (true);
}
