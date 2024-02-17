/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 23:25:46 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/27 22:07:39 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "defines.h"

/* bad_substitution.c */
bool			is_bad_substitution(char *str, t_expander_op op_mask);

/* expander.c */
int				ft_expander(char *str, t_list **lst, t_shell *shell,
					t_expander_op op_mask);

/* expander_task_stack.c */
bool			create_expander_task_stack(t_list **task_stack, char *new_str,
					t_expander_op op_mask);
bool			push_quote_task(t_list **task_stack, char *new_str, size_t *i);
bool			push_parameter_task(t_list **task_stack, char *new_str,
					size_t *i);

/* expander_task_stack_utils.c */
void			free_expander_task(t_expander_task *task);
char			*get_varname(char *str);
size_t			get_varname_len(char *str);
t_expander_task	*init_expander_task(t_expander_task_type type, size_t start,
					size_t replace_len, char *str);

/* expander_utils.c */
size_t			get_offset(char *str);
size_t			get_replace_len(char *str);
void			skip_to_dollar_not_in_single_quotes(char *str, size_t *i);
void			skip_to_expander_symbol(char *str, size_t *i);

/* expansion_handler.c */
bool			expand(char **new_str, t_list **lst, t_shell *shell,
					t_expander_op op_mask);
bool			execute_expander_task_stack(char **new_str, t_list *task_stack,
					t_list **lst, t_shell *shell);
bool			is_null_expansion(char *dup, t_list *task_stack);

/* quote_removal.c */
bool			remove_quote(char **new_str, t_expander_task *task);

/* special_param_expansion.c */
bool			expand_exit_code(char **new_str, t_expander_task *task,
					int exit_code);

/* variable_expansion.c */
bool			expand_variable(char **new_str, t_expander_task *task,
					t_list *env_list);

#endif
