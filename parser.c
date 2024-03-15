/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afantini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:37:05 by afantini          #+#    #+#             */
/*   Updated: 2024/03/08 18:37:07 by afantini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_setargs(t_tok *token, t_c_list *node, int arg)
{
	int	i;

	i = 0;
	while (token->data[i])
		i++;
	node->args[arg] = malloc((i + 1) * sizeof(char));
	node->args[arg][i] = '\0';
	i = -1;
	while (token->data[++i])
		node->args[arg][i] = token->data[i];
}

int	ft_args_count(t_lexer *lexbuf)
{
	int		i;
	int		c;
	int		t;
	t_tok	*token;

	i = 0;
	t = 0;
	token = lexbuf->llisttok;
	while (i < lexbuf->pipe_count)
	{
		if (token->type == CHAR_PIPE)
			i++;
		token = token->next;
		t++;
	}
	c = 0;
	while (t < lexbuf->ntoks)
	{
		if (token->type != CHAR_PIPE)
		{
			if (token->type == CHAR_GENERAL)
				c++;
			token = token->next;
		}
		t++;
	}
	return (c);
}

int	ft_input_count(t_lexer *lexbuf)
{
	int		i;
	int		t;
	int		c;
	t_tok	*token;

	i = 0;
	t = 0;
	token = lexbuf->llisttok;
	while (i < lexbuf->pipe_count)
	{
		if (token->type == CHAR_PIPE)
			i++;
		token = token->next;
		t++;
	}
	c = 0;
	while (t < lexbuf->ntoks && token->type != CHAR_PIPE)
	{
		if (token->type == CHAR_LESSER || token->type == CHAR_D_LESSER)
			c++;
		t++;
		token = token->next;
	}
	return (c);
}

int	ft_output_count(t_lexer *lexbuf)
{
	int		i;
	int		t;
	int		c;
	t_tok	*token;

	i = 0;
	t = 0;
	token = lexbuf->llisttok;
	while (i < lexbuf->pipe_count)
	{
		if (token->type == CHAR_PIPE)
			i++;
		token = token->next;
		t++;
	}
	c = 0;
	while (t < lexbuf->ntoks && token->type != CHAR_PIPE)
	{
		if (token->type == CHAR_GREATER || token->type == CHAR_D_GREATER)
			c++;
		t++;
		token = token->next;
	}
	return (c);
}

t_c_list	ft_add_node(t_lexer *lexbuf)
{
	t_c_list	node;
	int			nargs;
	int			nin;
	int			nout;

	node.next = NULL;
	nargs = ft_args_count(lexbuf);
	node.args = malloc((nargs + 1) * sizeof(char *));
	node.args[nargs] = NULL;
	nin = ft_input_count(lexbuf);
	node.input = malloc((nin + 1) * sizeof(t_tok));
	node.input[nin].type = CHAR_GENERAL;
	nout = ft_output_count(lexbuf);
	node.output = malloc((nout + 1) * sizeof(t_tok));
	node.output[nout].type = CHAR_GENERAL;
	lexbuf->nnodes++;
	return (node);
}

t_tok	ft_tokenize(t_tok *token)
{
	char	*input;
	t_tok	new;

	new.type = CHAR_D_LESSER;
	while (input != token->data)
	{
		printf("\n");
		input = readline(">");
		if (input != token->data)
			new.data = ft_strjoin(new.data, input);
	}
	return (new);
}

void	parser(t_lexer *lexbuf, t_c_list *node)
{
	t_tok		*token;
	t_c_list		new;
	int			i;
	int			in;
	int			out;
	int			arg;

	token = lexbuf->llisttok;
	i = -1;
	in = 0;
	out = 0;
	arg = 0;
	while (++i < lexbuf->ntoks)
	{
		if (token->type == CHAR_PIPE)
		{
			(lexbuf->pipe_count)++;
			new = ft_add_node(lexbuf);
			node->next = &new;
			node = node->next;
		}
		else if (token->type == CHAR_GENERAL)
			ft_setargs(token, node, arg++);
		else if (token->type == CHAR_LESSER)
			node->input[in++] = *token;
		else if (token->type == CHAR_D_LESSER)
			node->input[in++] = ft_tokenize(token);
		else if (token->type == CHAR_GREATER || token->type == CHAR_D_GREATER)
			node->output[out++] = *token;
		token = token->next;
	}
}

void	parse(t_lexer *lexbuf)
{
	t_c_list	*node;

	node = lexbuf->command_list;
	parser(lexbuf, node);
	lexbuf->command_list = node;
}
