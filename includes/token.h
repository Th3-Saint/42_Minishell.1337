/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:47:09 by aait-mas          #+#    #+#             */
/*   Updated: 2022/11/25 22:18:41 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
#define TOKEN_H
#include "minishel.h"

typedef struct token
{
	enum
	{
		TOKEN_START,
		TOKEN_WORD,
		TOKEN_PIPE,
		TOKEN_REDIR_IN,
		TOKEN_REDIR_OUT,
		D_TOKEN_REDIR_IN,
		D_TOKEN_REDIR_OUT,
		TOKEN_DOLLAR,
		TOKEN_SPACE,
		TOKEN_FLAG,
		TOKEN_DOUBLE_QUOTES,
		TOKEN_SINGLE_QUOTE,
		TOKEN_X,
	} type;
	char *value;
	struct token *next;
} t_token;

t_token *token_init(char *value, int type);
void token_add_back(t_token **token, char *value, int type);
int check_special_char(char c);
int ft_lstsize(t_token *token);
char *check_env(char *str, char **env);
void correction1(t_token *token);
char **return_cmd(char *str);
int heredoc(char *del, int *flag);
#endif