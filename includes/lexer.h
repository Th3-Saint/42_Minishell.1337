/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:46:55 by aait-mas          #+#    #+#             */
/*   Updated: 2022/11/25 22:18:37 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H
#include "minishel.h"
#include "token.h"

typedef struct lexer
{
	char *line;
	int line_size;
	char c;
	int i;
	int j;
} t_lexer;

t_lexer *lexer_init(char *src);
void lexer_move(t_lexer *lexer);
void lexer_skip_white_space(t_lexer *lexer);
char *convert_char_to_str(char c);
char *get_word(t_lexer *lexer, char **env);
t_token *ft_get_tokens(t_lexer *lexer, char **env);
void lexer_move_with(t_lexer *lexer, t_token *token, int type, char *value);
void lexer_back(t_lexer *lexer);
int check_second_quote(t_lexer *lexer, char c);
void check_after_space(t_lexer *lexer, t_token *token);
void check_after_word(t_token *token, t_lexer *lexer);
char *develop(t_lexer *lexer, char **env);
void get_btw_single_quote(t_lexer *lexer, t_token *token);
void get_btw_double_quote(t_lexer *lexer, t_token *token, char **env);
char *develop2(t_lexer *lexer, char **env);
char *get_name_file(t_token *tmp);
void free_token(t_token **token);

#endif