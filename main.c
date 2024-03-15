#include "minishell.h"

void    clear_toks(t_tok *token)
{
    _Bool   c;

    c = 1;
    if (c && token)
    {
        free(token->data);
        if (token->next != NULL)
            token = token->next;
        else
            c = !c;
    }
}

void    clear_nodes(t_c_list *node)
{
    _Bool   c;
    int     i;

    c = 1;
    if (c)
    {
        i = -1;
        while (node->args[++i] != NULL)
            free(node->args[i]);
        free(node->input);
        free(node->output);
        if (node->next != NULL)
            node = node->next;
        else
            c = !c;
    }
    free(node->args);
}

void clear_all(t_lexer *lexbuf)
{
    //clear_toks(lexbuf->llisttok);
    clear_nodes(lexbuf->command_list);
}


int main()
{
    t_tok   token;
    t_tok   token2;
    t_tok   token3;
    t_tok   token4;
    t_tok   token5;
    t_lexer lexbuf;
    t_c_list node;

    token.data = "echo";
    token.type = CHAR_GENERAL;
    token.next = &token2;
    token2.data = "ciao";
    token2.type = CHAR_GENERAL;
    token2.next = &token3;
    token3.data = "|";
    token3.type = CHAR_PIPE;
    token3.next = &token4;
    token4.data = "cat";
    token4.type = CHAR_GENERAL;
    token4.next = &token5;
    token5.data = "c";
    token5.type = CHAR_GREATER;
    token5.next = NULL;
    lexbuf.ntoks = 5;
    lexbuf.nnodes = 0;
	lexbuf.pipe_count = 0;
    lexbuf.llisttok = &token;
    node = ft_add_node(&lexbuf);
    lexbuf.command_list = &node;
    parse(&lexbuf);
	printf("a = %d\n", lexbuf.command_list->next->input[0].type);
    execute(&lexbuf);
    //clear_all(&lexbuf);
    return(0);
}