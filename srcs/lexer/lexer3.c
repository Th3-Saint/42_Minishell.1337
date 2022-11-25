/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mas <aait-mas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 03:04:45 by aait-mas          #+#    #+#             */
/*   Updated: 2022/11/25 22:32:42 by aait-mas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishel.h"

void	get_btw_single_quote(t_lexer *lexer, t_token *token)
{
	char	*value;
	char	*str;
	char	*tmp;

	if (check_second_s_quote(lexer) == 1)
	{
		token_add_back(&token, "ERROR", TOKEN_FLAG);
		lexer_move(lexer);
		return ;
	}
	value = ft_strdup("");
	lexer_move(lexer);
	while (lexer->c != '\'')
	{
		str = convert_char_to_str(lexer->c);
		tmp = value;
		value = ft_strjoin(value, str);
		free(tmp);
		free(str);
		lexer_move(lexer);
	}
	lexer_move(lexer);
	token_add_back(&token, value, TOKEN_SINGLE_QUOTE);
	free(value);
	check_after_space(lexer, token);
}

void	get_btw_double_quote(t_lexer *lexer, t_token *token, char **env)
{
	char	*value;
	char	*str;

	if (check_second_d_quote(lexer) == 1)
	{
		token_add_back(&token, "ERROR", TOKEN_FLAG);
		lexer_move(lexer);
		return ;
	}
	value = ft_strdup("");
	lexer_move(lexer);
	while (lexer->c != '"')
	{
		if (lexer->c == '$' && lexer->line[lexer->i + 1] == '?')
			str = get_exit_code(lexer, str);
		else if (help_gbdq(lexer))
			str = develop2(lexer, env);
		else
			str = convert_char_to_str(lexer->c);
		value = help_gbdq_1(lexer, str, value);
	}
	token_add_back(&token, value, TOKEN_DOUBLE_QUOTES);
	free(value);
	lexer_move(lexer);
	check_after_space(lexer, token);
}

char	*develop(t_lexer *lexer, char **env)
{
	int		i;
	char	*str;
	char	*real_value;

	i = 0;
	lexer_move(lexer);
	lexer->j = lexer->i;
	while (lexer->line[lexer->j] && (ft_isalnum(lexer->line[lexer->j])
			|| lexer->line[lexer->j] == '_'))
		lexer->j++;
	str = malloc(sizeof(char) * (lexer->j - lexer->i) + 1);
	while (lexer->i < lexer->j)
	{
		str[i] = lexer->c;
		lexer_move(lexer);
		i++;
	}
	str[i] = '\0';
	real_value = check_env(str, env);
	lexer_back(lexer);
	return (real_value);
}

void	token_add_back(t_token **token, char *value, int type)
{
	t_token	*last;
	t_token	*tmp;

	if (!*token)
	{
		*token = token_init(value, type);
		return ;
	}
	last = token_init(value, type);
	tmp = (*token);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = last;
}

void	check_after_space(t_lexer *lexer, t_token *token)
{
	if (lexer->c <= 32)
	{
		lexer->j = lexer->i;
		while (lexer->line[lexer->j] <= 32 && lexer->line[lexer->j])
			lexer->j++;
		if (lexer->line[lexer->j] == '\'' || lexer->line[lexer->j] == '"'
			|| lexer->c != '\0')
			token_add_back(&token, " ", TOKEN_SPACE);
		lexer->j = 0;
	}
}
