/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:56:26 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/17 13:41:01 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "ft_printf.h"

# define PROGRAM_NAME		"minishell"
# define EXIT_SUCCESS		0
# define EXIT_FAILED	    -1

# define PT_COL_SIZE        5

// # define RED				"\033[0;31m"
// # define GREEN				"\033[0;32m"
// # define YELLOW				"\033[0;33m"
// # define BLUE				"\033[0;34m"
// # define MAGENTA			"\033[0;35m"
// # define CYAN				"\033[0;36m"
// # define WHITE				"\033[0;37m"
// # define BOLD_RED			"\033[1;31m"
// # define RESET				"\033[0m"

# define PROMPT				"\033[1;32mminishell$ \033[0m"
// # define PROMPT				"\001\033[1;32m\002minishell$ \001\033[0m\002"
// # define PROMPT				"minishell$ "

extern const int	g_parsing_table[][PT_COL_SIZE];

typedef enum e_pt_col
{
	PT_COL_STATE = 0,
	PT_COL_TOKEN_TYPE,
	PT_COL_ACTION,
	PT_COL_NEXT_STATE,
	PT_COL_NUM_REDUCED
}	t_pt_col;

typedef enum e_action_type
{
	A_REJECT = -2,
	A_ACCEPT = 0,
	A_SHIFT,
	A_REDUCE,
	A_GOTO
}	t_action_type;

typedef enum e_rules
{
	R_AND_OR = 100,
	R_PIPE_SEQ,
	R_CMD,
	R_SUBSHELL,
	R_SIMPLE_CMD,
	R_CMD_NAME,
	R_CMD_WORD,
	R_CMD_PREFIX,
	R_CMD_SUFFIX,
	R_RED_LIST,
	R_IO_RED,
	R_IO_FILE,
	R_FILENAME,
	R_IO_HERE,
	R_HERE_END
}	t_rules;

typedef enum e_token_type
{
	T_END = -2,
	T_WORD = 0,
	T_ASSIGNMENT_WORD,
	T_RED_IN,
	T_RED_OUT,
	T_PIPE,
	T_HERE_DOC,
	T_APPEND,
	T_OR,
	T_AND,
	T_L_BRACKET,
	T_R_BRACKET
}	t_token_type;

typedef struct s_env
{
	char			*key;
	char			*value;
}	t_env;

typedef struct s_token
{
	int				type;
	char			*data;
}	t_token;

typedef struct s_ast
{
	int				type;
	char			*data;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct s_pt_node
{
	int				state;
	int				token_type;
	int				action;
	int				next_state;
	int				num_reduced;
}	t_pt_node;

typedef struct s_io_redirect
{
	char			*redir_in;
	char			*redir_out;
}	t_io_redirect;

typedef struct s_cmd_table
{
	char			*cmd_name;
	char			*cmd_args;
	t_io_redirect	*io_redirect;
}	t_cmd_table;

typedef struct s_shell
{
	int				exit_code;
	t_list			*env_list;
	t_list			*token_list;
	t_list			*final_cmd_table;
	t_ast			*ast;
	char			*input_line;
}	t_shell;

#endif	