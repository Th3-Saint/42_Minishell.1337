/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mas <aait-mas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 02:50:17 by aait-mas          #+#    #+#             */
/*   Updated: 2022/11/25 22:32:39 by aait-mas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishel.h"

t_token	*token_init(char *value, int type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->value = ft_strdup(value);
	token->e_tokn = type;
	token->next = NULL;
	return (token);
}

void	get_tokens(t_lexer *lexer, t_token *token, char **env)
{
	if (check_special_char(lexer->c) == 1)
	{
		lexer_move_with(lexer, token, TOKEN_WORD, get_word(lexer, env));
		check_after_word(token, lexer);
	}
	if (lexer->c == '|')
		lexer_move_with(lexer, token, TOKEN_PIPE, ft_strdup("|"));
	if (lexer->c == '>' && lexer->line[lexer->i + 1] != '>')
		lexer_move_with(lexer, token, TOKEN_REDIR_OUT, ft_strdup(">"));
	if (lexer->c == '<' && lexer->line[lexer->i + 1] != '<')
		lexer_move_with(lexer, token, TOKEN_REDIR_IN, ft_strdup("<"));
	if (lexer->c == '>' && lexer->line[lexer->i + 1] == '>')
	{
		lexer_move(lexer);
		lexer_move_with(lexer, token, D_TOKEN_REDIR_OUT, ft_strdup(">>"));
	}
	if (lexer->c == '<' && lexer->line[lexer->i + 1] == '<')
	{
		lexer_move(lexer);
		lexer_move_with(lexer, token, D_TOKEN_REDIR_IN, ft_strdup("<<"));
	}
	if (lexer->c == '\'')
		get_btw_single_quote(lexer, token);
	if (lexer->c == '"')
		get_btw_double_quote(lexer, token, env);
}

int	check_special_char(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == '\''
		|| c == '"' || c == ' ' || c == '\0')
		return (0);
	else
		return (1);
}

char	*get_word(t_lexer *lexer, char **env)
{
	char	*value;
	char	*str;
	char	*tmp;

	value = malloc(sizeof(char));
	value[0] = '\0';
	while (check_special_char(lexer->c) && lexer->c != '\0')
	{
		if (lexer->c == '$' && ft_isalnum(lexer->line[lexer->i + 1])
			&& lexer->line[lexer->i + 1] != '_')
			str = develop(lexer, env);
		else if (lexer->c == '$' && lexer->line[lexer->i + 1] == '?')
		{
			lexer_move(lexer);
			str = ft_itoa(get_var(0, 127));
		}
		else
			str = convert_char_to_str(lexer->c);
		tmp = value;
		value = ft_strjoin(value, str);
		free_norm(tmp, str);
		lexer_move(lexer);
	}
	lexer_back(lexer);
	return (value);
}

void	check_after_word(t_token *token, t_lexer *lexer)
{
	if (lexer->c == 32)
	{
		lexer->j = lexer->i;
		while (lexer->line[lexer->j] && lexer->line[lexer->j] <= 32)
			lexer->j++;
		if (check_special_char(lexer->line[lexer->j]) == 1)
			token_add_back(&token, " ", TOKEN_SPACE);
		else if (lexer->line[lexer->j] == '"' || lexer->line[lexer->j] == '\'')
			token_add_back(&token, " ", TOKEN_SPACE);
		lexer->j = 0;
	}
}
