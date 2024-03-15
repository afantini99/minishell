/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afantini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:43:30 by afantini          #+#    #+#             */
/*   Updated: 2024/03/04 15:43:32 by afantini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

enum e_TokenType
{
	CHAR_GENERAL = -1,
	CHAR_PIPE = '|',
	CHAR_QUOTE = '\'',
	CHAR_DQUOTE = '\"',
	CHAR_WHITESPACE = ' ',
	CHAR_ESCAPESEQUENCE = '\\',
	CHAR_TAB = '\t',
	CHAR_NEWLINE = '\n',
	CHAR_GREATER = '>',
	CHAR_LESSER = '<',
	CHAR_D_GREATER = '>' * 2,
	CHAR_D_LESSER = '<' * 2,
	CHAR_NULL = 0,
	TOKEN	= -1,
};

enum
{
	STATE_IN_DQUOTE,
	STATE_IN_QUOTE,
	STATE_IN_ESCAPESEQ,
	STATE_GENERAL,
};

typedef struct tok
{
	char		*data;
	int			type;
	struct tok	*next;
}	t_tok;

typedef struct command_node
{
	char				**args;
	t_tok				*input;
	t_tok				*output;
	struct command_node	*next;
}	t_c_list;

typedef struct lexer
{
	t_tok		*llisttok;
	t_c_list	*command_list;
	int			nnodes;
	int			ntoks;
	int			pipe_count;
}	t_lexer;

void	parse(t_lexer *lexbuf);
int	execute(t_lexer *lexbuf);
t_c_list	ft_add_node(t_lexer *lexbuf);

#endif