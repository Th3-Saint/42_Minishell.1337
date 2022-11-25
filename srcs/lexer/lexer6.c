/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mas <aait-mas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 03:16:13 by aait-mas          #+#    #+#             */
/*   Updated: 2022/11/25 22:32:55 by aait-mas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishel.h"

char	*develop2(t_lexer *lexer, char **env)
{
	int		i;
	char	*str;
	char	*real_value;

	i = 0;
	lexer_move(lexer);
	lexer->j = lexer->i;
	while (lexer->line[lexer->j] && (ft_isalnum(lexer->line[lexer->j])
			|| lexer->line[lexer->j] == '_') && lexer->line[lexer->j] != '$')
		lexer->j++;
	str = malloc(sizeof(char) * (lexer->j - lexer->i + 1));
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

char	*get_name_file(t_token *tmp)
{
	char	*str;
	char	*temp;

	tmp = tmp->next;
	str = tmp->value;
	while (tmp->next->e_tokn == TOKEN_SINGLE_QUOTE
		|| tmp->next->e_tokn == TOKEN_DOUBLE_QUOTES)
	{
		tmp = tmp->next;
		temp = str;
		str = ft_strjoin(str, tmp->value);
		free(temp);
	}
	return (str);
}

void	free_token(t_token **token)
{
	t_token	*tmp;

	while ((*token))
	{
		tmp = (*token);
		*token = (*token)->next;
		free(tmp->value);
		free(tmp);
	}
}

void	free_norm(char *tmp, char *c)
{
	free(tmp);
	free(c);
}
