/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:27:22 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/17 13:57:37 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// | State | Token Type | Action | Next State | Number of Reduced Tokens |
const int	g_parsing_table[][PT_COL_SIZE] = {\
	{0, 0, 1, 1, -1}, \
	{0, 1, 1, 2, -1}, \
	{0, 2, 1, 3, -1}, \
	{0, 3, 1, 4, -1}, \
	{0, 5, 1, 5, -1}, \
	{0, 6, 1, 6, -1}, \
	{0, 9, 1, 7, -1}, \
	{0, 100, 3, 8, -1}, \
	{0, 101, 3, 9, -1}, \
	{0, 102, 3, 10, -1}, \
	{0, 103, 3, 11, -1}, \
	{0, 104, 3, 12, -1}, \
	{0, 105, 3, 13, -1}, \
	{0, 107, 3, 14, -1}, \
	{0, 110, 3, 15, -1}, \
	{0, 111, 3, 16, -1}, \
	{0, 113, 3, 17, -1}, \
	{1, -1, 2, 105, 1}, \
	{2, -1, 2, 107, 1}, \
	{3, 0, 1, 18, -1}, \
	{3, 112, 3, 19, -1}, \
	{4, 0, 1, 18, -1}, \
	{4, 112, 3, 20, -1}, \
	{5, 0, 1, 21, -1}, \
	{5, 114, 3, 22, -1}, \
	{6, 0, 1, 18, -1}, \
	{6, 112, 3, 23, -1}, \
	{7, 0, 1, 1, -1}, \
	{7, 1, 1, 2, -1}, \
	{7, 2, 1, 3, -1}, \
	{7, 3, 1, 4, -1}, \
	{7, 5, 1, 5, -1}, \
	{7, 6, 1, 6, -1}, \
	{7, 9, 1, 7, -1}, \
	{7, 100, 3, 24, -1}, \
	{7, 101, 3, 9, -1}, \
	{7, 102, 3, 10, -1}, \
	{7, 103, 3, 11, -1}, \
	{7, 104, 3, 12, -1}, \
	{7, 105, 3, 13, -1}, \
	{7, 107, 3, 14, -1}, \
	{7, 110, 3, 15, -1}, \
	{7, 111, 3, 16, -1}, \
	{7, 113, 3, 17, -1}, \
	{8, 8, 1, 26, -1}, \
	{8, 7, 1, 27, -1}, \
	{9, 4, 1, 28, -1}, \
	{9, -1, 2, 100, 1}, \
	{10, -1, 2, 101, 1}, \
	{11, 2, 1, 3, -1}, \
	{11, 3, 1, 4, -1}, \
	{11, 5, 1, 5, -1}, \
	{11, 6, 1, 6, -1}, \
	{11, -1, 2, 102, 1}, \
	{11, 109, 3, 29, -1}, \
	{11, 110, 3, 30, -1}, \
	{11, 111, 3, 16, -1}, \
	{11, 113, 3, 17, -1}, \
	{12, -1, 2, 102, 1}, \
	{13, 0, 1, 31, -1}, \
	{13, 2, 1, 3, -1}, \
	{13, 3, 1, 4, -1}, \
	{13, 5, 1, 5, -1}, \
	{13, 6, 1, 6, -1}, \
	{13, -1, 2, 104, 1}, \
	{13, 108, 3, 32, -1}, \
	{13, 110, 3, 33, -1}, \
	{13, 111, 3, 16, -1}, \
	{13, 113, 3, 17, -1}, \
	{14, 0, 1, 34, -1}, \
	{14, 1, 1, 35, -1}, \
	{14, 2, 1, 3, -1}, \
	{14, 3, 1, 4, -1}, \
	{14, 5, 1, 5, -1}, \
	{14, 6, 1, 6, -1}, \
	{14, -1, 2, 104, 1}, \
	{14, 106, 3, 36, -1}, \
	{14, 110, 3, 37, -1}, \
	{14, 111, 3, 16, -1}, \
	{14, 113, 3, 17, -1}, \
	{15, -1, 2, 107, 1}, \
	{16, -1, 2, 110, 1}, \
	{17, -1, 2, 110, 1}, \
	{18, -1, 2, 112, 1}, \
	{19, -1, 2, 111, 2}, \
	{20, -1, 2, 111, 2}, \
	{21, -1, 2, 114, 1}, \
	{22, -1, 2, 113, 2}, \
	{23, -1, 2, 111, 2}, \
	{24, 8, 1, 26, -1}, \
	{24, 7, 1, 27, -1}, \
	{24, 10, 1, 38, -1}, \
	{25, -1, 0, -1, -1}, \
	{26, 0, 1, 1, -1}, \
	{26, 1, 1, 2, -1}, \
	{26, 2, 1, 3, -1}, \
	{26, 3, 1, 4, -1}, \
	{26, 5, 1, 5, -1}, \
	{26, 6, 1, 6, -1}, \
	{26, 9, 1, 7, -1}, \
	{26, 101, 3, 39, -1}, \
	{26, 102, 3, 10, -1}, \
	{26, 103, 3, 11, -1}, \
	{26, 104, 3, 12, -1}, \
	{26, 105, 3, 13, -1}, \
	{26, 107, 3, 14, -1}, \
	{26, 110, 3, 15, -1}, \
	{26, 111, 3, 16, -1}, \
	{26, 113, 3, 17, -1}, \
	{27, 0, 1, 1, -1}, \
	{27, 1, 1, 2, -1}, \
	{27, 2, 1, 3, -1}, \
	{27, 3, 1, 4, -1}, \
	{27, 5, 1, 5, -1}, \
	{27, 6, 1, 6, -1}, \
	{27, 9, 1, 7, -1}, \
	{27, 101, 3, 40, -1}, \
	{27, 102, 3, 10, -1}, \
	{27, 103, 3, 11, -1}, \
	{27, 104, 3, 12, -1}, \
	{27, 105, 3, 13, -1}, \
	{27, 107, 3, 14, -1}, \
	{27, 110, 3, 15, -1}, \
	{27, 111, 3, 16, -1}, \
	{27, 113, 3, 17, -1}, \
	{28, 0, 1, 1, -1}, \
	{28, 1, 1, 2, -1}, \
	{28, 2, 1, 3, -1}, \
	{28, 3, 1, 4, -1}, \
	{28, 5, 1, 5, -1}, \
	{28, 6, 1, 6, -1}, \
	{28, 9, 1, 7, -1}, \
	{28, 102, 3, 41, -1}, \
	{28, 103, 3, 11, -1}, \
	{28, 104, 3, 12, -1}, \
	{28, 105, 3, 13, -1}, \
	{28, 107, 3, 14, -1}, \
	{28, 110, 3, 15, -1}, \
	{28, 111, 3, 16, -1}, \
	{28, 113, 3, 17, -1}, \
	{29, 2, 1, 3, -1}, \
	{29, 3, 1, 4, -1}, \
	{29, 5, 1, 5, -1}, \
	{29, 6, 1, 6, -1}, \
	{29, -1, 2, 102, 2}, \
	{29, 110, 3, 42, -1}, \
	{29, 111, 3, 16, -1}, \
	{29, 113, 3, 17, -1}, \
	{30, -1, 2, 109, 1}, \
	{31, -1, 2, 108, 1}, \
	{32, 0, 1, 43, -1}, \
	{32, 2, 1, 3, -1}, \
	{32, 3, 1, 4, -1}, \
	{32, 5, 1, 5, -1}, \
	{32, 6, 1, 6, -1}, \
	{32, -1, 2, 104, 2}, \
	{32, 110, 3, 44, -1}, \
	{32, 111, 3, 16, -1}, \
	{32, 113, 3, 17, -1}, \
	{33, -1, 2, 108, 1}, \
	{34, -1, 2, 106, 1}, \
	{35, -1, 2, 107, 2}, \
	{36, 0, 1, 31, -1}, \
	{36, 2, 1, 3, -1}, \
	{36, 3, 1, 4, -1}, \
	{36, 5, 1, 5, -1}, \
	{36, 6, 1, 6, -1}, \
	{36, -1, 2, 104, 2}, \
	{36, 108, 3, 45, -1}, \
	{36, 110, 3, 33, -1}, \
	{36, 111, 3, 16, -1}, \
	{36, 113, 3, 17, -1}, \
	{37, -1, 2, 107, 2}, \
	{38, -1, 2, 103, 3}, \
	{39, 4, 1, 28, -1}, \
	{39, -1, 2, 100, 3}, \
	{40, 4, 1, 28, -1}, \
	{40, -1, 2, 100, 3}, \
	{41, -1, 2, 101, 3}, \
	{42, -1, 2, 109, 2}, \
	{43, -1, 2, 108, 2}, \
	{44, -1, 2, 108, 2}, \
	{45, 0, 1, 43, -1}, \
	{45, 2, 1, 3, -1}, \
	{45, 3, 1, 4, -1}, \
	{45, 5, 1, 5, -1}, \
	{45, 6, 1, 6, -1}, \
	{45, -1, 2, 104, 3}, \
	{45, 110, 3, 44, -1}, \
	{45, 111, 3, 16, -1}, \
	{45, 113, 3, 17, -1}, \
	{}
};


t_pt_node	*init_pt_node(const int pt_row[])
{
	t_pt_node	*pt_node;

	pt_node = malloc(sizeof(t_pt_node));
	if (!pt_node)
		return (NULL);
	pt_node->state = pt_row[PT_COL_STATE];
	pt_node->token_type = pt_row[PT_COL_TOKEN_TYPE];
	pt_node->action = pt_row[PT_COL_ACTION];
	pt_node->next_state = pt_row[PT_COL_NEXT_STATE];
	pt_node->num_reduced = pt_row[PT_COL_NUM_REDUCED];
	return (pt_node);
}

// | State | Token Type | Action | Next State | Number of Reduced Tokens |
t_pt_node	*get_pt_entry(
	const int parsing_table[][5], int state, int token_type)
{
	int			i;
	t_pt_node	*pt_entry;

	i = 0;
	while (parsing_table[i])
	{
		if (parsing_table[i][PT_COL_STATE] == state && \
			parsing_table[i][PT_COL_TOKEN_TYPE] == token_type)
			break ;
	}
	if (!parsing_table[i])
		return (NULL);
	pt_entry = init_pt_node(parsing_table[i]);
	return (pt_entry);
}

t_pt_node	*find_pt_entry(int state, int token_type)
{
	return (get_pt_entry(g_parsing_table, state, token_type));
}

bool	update_pt_entry(t_pt_node **pt_entry, int state, int token_type)
{
	t_pt_node	*new_pt_entry;

	new_pt_entry = find_pt_entry(state, token_type);
	if (!new_pt_entry)
		return (false);
	free(*pt_entry);
	*pt_entry = new_pt_entry;
	return (true);
}
