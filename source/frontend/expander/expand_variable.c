/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:18:15 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/28 02:12:54 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "utils.h"

bool	expand_variable(char **str, size_t *i, size_t offset, t_list *env_list)
{
	size_t	replace_len;
	char	*replacement;
	char	*var;
	size_t	var_len;

	var_len = count_var_len(&(*str)[*i]);
	var = ft_substr(*str, *i + offset, var_len);
	if (!var)
		return (false);
	replace_len = count_replace_len(&(*str)[*i]);
	replacement = get_value_from_env_list(env_list, var);
	if (!replacement)
		replacement = "";
	free(var);
	if (!ft_rplc_part_of_str(str, replacement, *i, replace_len))
		return (false);
	*i += ft_strlen(replacement);
	return (true);
}

size_t	count_var_len(char *str)
{
	size_t	len;

	if (*str == '$')
	{
		str++;
		if (*str == OPENING_BRACE)
			str++;
	}
	len = 0;
	while (is_valid_varname_char(*str))
	{
		len++;
		str++;
	}
	return (len);
}
