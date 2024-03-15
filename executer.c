/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afantini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:59:16 by afantini          #+#    #+#             */
/*   Updated: 2024/03/04 14:59:17 by afantini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(t_lexer *lexbuf)
{
	int			ret;
	int			i;
	int			j;
	int			tmpin;
	int			tmpout;
	int			fdin;
	int			fdout;
	int			fdpipe[2];
	t_tok		*input;
	t_tok		*output;
	t_c_list	*node;

	tmpin = dup(0);
	tmpout = dup(1);
	printf("a = %d\n", lexbuf->command_list->next->input[0].type);
	node = lexbuf->command_list;
	fdin = dup(tmpin);
	i = -1;
	printf("a = %d\n", lexbuf->command_list->next->input[0].type);
	printf("a = %d\n", node->next->input[0].type);
	while (++i < lexbuf->nnodes)//se si commenta tutto il while node->next->input[0].type = -1, senno' no
	{
		input = node->input;
		printf("b = %d\n", node->input[0].type);
		dup2(fdin, 0);
		j = 0;
		if (input[j].type != CHAR_GENERAL)
		{
			while (input[j + 1].type != CHAR_GENERAL)
				j++;
			fdin = open(input[j].data, O_RDONLY);
		}
		close(fdin);
		output = node->output;
		j = 0;
		if (output[j].type != CHAR_GENERAL)
		{
			while (output[j + 1].type != CHAR_GENERAL)
			{
				if (output[j].type == CHAR_GREATER)
					fdout = open(output[j].data, O_WRONLY | O_TRUNC);
				j++;
			}
			if (output[j].type == CHAR_GREATER)
				fdout = open(output[j].data, O_WRONLY);
			else if (output[j].type == CHAR_D_GREATER)
				fdout = open(output[j].data, O_APPEND);
		}
		if (i == lexbuf->nnodes - 1 && output[j].type == CHAR_GENERAL)
			fdout = dup(tmpout);
		else if (i != lexbuf->nnodes - 1)
		{
			pipe(fdpipe);
			fdout = fdpipe[1];
			fdin = fdpipe[0];
		}
		dup2(fdout, 1);
		close(fdout);
		ret = fork();
		if (ret == 0)
		{
			execvp(node->args[0], node->args);
			perror("execvp");
			_exit(1);
		}
		else if (ret < 0)
		{
			perror("fork");
			return (1);
		}
		printf("c = %d", node->next->input[0].type);
		node = node->next;
	}
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
	return (0);
}
