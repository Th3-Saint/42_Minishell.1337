/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:50:16 by aait-mas          #+#    #+#             */
/*   Updated: 2022/11/25 22:10:47 by mrobaii          ###   ########.fr       */
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

char	*get_exit_code(t_lexer *lexer, char *c)
{
	int	t;

	lexer_move(lexer);
	t = get_var(0, 33);
	c = ft_itoa(t);
	return (c);
}

char	*convert_char_to_str(char c)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

void	lexer_back(t_lexer *lexer)
{
	lexer->i--;
	lexer->c = lexer->line[lexer->i];
}

int	check_second_quote(t_lexer *lexer, char c)
{
	lexer->j = lexer->i;
	lexer->j += 1;
	while (lexer->line[lexer->j] != '\0')
	{
		if (lexer->line[lexer->j] == c)
			return (0);
		lexer->j++;
	}
	return (1);
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

char	*help_gbdq_1(t_lexer *lexer, char *c, char *value)
{
	char	*tmp;

	tmp = value;
	value = ft_strjoin(value, c);
	free(tmp);
	free(c);
	lexer_move(lexer);
	return (value);
}

int	help_gbdq(t_lexer *lexer)
{
	if (lexer->c == '$' && ft_isalnum(lexer->line[lexer->i + 1])
		&& lexer->line[lexer->i + 1] != '_' && lexer->line[lexer->i + 1] != '"')
		return (1);
	return (0);
}

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
	while (tmp->next->type == TOKEN_SINGLE_QUOTE
		|| tmp->next->type == TOKEN_DOUBLE_QUOTES)
	{
		tmp = tmp->next;
		temp = str;
		str = ft_strjoin(str, tmp->value);
		free(temp);
	}
	return (str);
}
