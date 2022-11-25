/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mas <aait-mas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:50:16 by aait-mas          #+#    #+#             */
/*   Updated: 2022/11/25 22:32:34 by aait-mas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishel.h"

t_lexer	*lexer_init(char *line)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	lexer->line = ft_strdup(line);
	lexer->line_size = ft_strlen(line);
	lexer->i = 0;
	lexer->j = 0;
	lexer->c = lexer->line[lexer->i];
	return (lexer);
}

t_token	*ft_get_tokens(t_lexer *lexer, char **env)
{
	t_token	*token;

	token = token_init("TOKEN_START", TOKEN_START);
	while (lexer->i < (int)ft_strlen(lexer->line) && lexer->c != '\0')
	{
		lexer_skip_white_space(lexer);
		get_tokens(lexer, token, env);
	}
	free(lexer->line);
	free(lexer);
	return (token);
}

void	lexer_skip_white_space(t_lexer *lexer)
{
	while (lexer->line[lexer->i] == 32 || lexer->line[lexer->i] == 9
		|| lexer->line[lexer->i] == 10 || lexer->line[lexer->i] == 13)
		lexer_move(lexer);
}

void	lexer_move(t_lexer *lexer)
{
	if (lexer->i < lexer->line_size && lexer->c != '\0')
	{
		lexer->i++;
		lexer->c = lexer->line[lexer->i];
	}
}

void	lexer_move_with(t_lexer *lexer, t_token *token, int type, char *value)
{
	if (lexer->line[lexer->i] != '\0')
		lexer_move(lexer);
	token_add_back(&token, value, type);
	free(value);
}
