/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:02:14 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/04 11:09:35 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The ft_min function returns the minimum of two integers.
 *
 * @param a    The first integer to compare.
 * @param b    The second integer to compare.
 *
 * @return     Returns the smaller of the two integers.
 */
int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}
