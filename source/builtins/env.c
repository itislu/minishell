/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 20:07:52 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/05 19:10:10 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_env(t_shell *shell)
{
	t_list	*cur;
	t_env	*env;

	cur = shell->env_list;
	while (cur)
	{
		env = (t_env *)cur->content;
		ft_printf("%s=%s\n", env->key, env->value);
		cur = cur->next;
	}
}
