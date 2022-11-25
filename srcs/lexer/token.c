/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:57:20 by aait-mas          #+#    #+#             */
/*   Updated: 2022/11/25 22:11:01 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishel.h"

t_token	*token_init(char *value, int type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->value = ft_strdup(value);
	token->type = type;
	token->next = NULL;
	return (token);
}

char	*get_word(t_lexer *lexer, char **env)
{
	char	*value;
	char	*c;
	char	*tmp;

	value = malloc(sizeof(char));
	value[0] = '\0';
	while (check_special_char(lexer->c) && lexer->c != '\0')
	{
		if (lexer->c == '$' && ft_isalnum(lexer->line[lexer->i + 1])
			&& lexer->line[lexer->i + 1] != '_')
			c = develop(lexer, env);
		else if (lexer->c == '$' && lexer->line[lexer->i + 1] == '?')
		{
			lexer_move(lexer);
			c = ft_itoa(get_var(0, 127));
		}
		else
			c = convert_char_to_str(lexer->c);
		tmp = value;
		value = ft_strjoin(value, c);
		free_norm(tmp, c);
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

void	get_btw_single_quote(t_lexer *lexer, t_token *token)
{
	char	*value;
	char	*c;
	char	*tmp;

	if (check_second_quote(lexer, '\'') == 1)
	{
		token_add_back(&token, "ERROR", TOKEN_FLAG);
		lexer_move(lexer);
		return ;
	}
	value = ft_strdup("");
	lexer_move(lexer);
	while (lexer->c != '\'')
	{
		c = convert_char_to_str(lexer->c);
		tmp = value;
		value = ft_strjoin(value, c);
		free(tmp);
		free(c);
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
	char	*c;

	if (check_second_quote(lexer, '"') == 1)
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
			c = get_exit_code(lexer, c);
		else if (help_gbdq(lexer))
			c = develop2(lexer, env);
		else
			c = convert_char_to_str(lexer->c);
		value = help_gbdq_1(lexer, c, value);
	}
	token_add_back(&token, value, TOKEN_DOUBLE_QUOTES);
	free(value);
	lexer_move(lexer);
	check_after_space(lexer, token);
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

int	check_special_char(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == '\''
		|| c == '"' || c == ' ' || c == '\0')
		return (0);
	else
		return (1);
}

int	ft_lstsize(t_token *token)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = token;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

char	*check_env(char *str, char **env)
{
	char	*tmp;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], str, test_cmp(str, env[i])) == 0)
		{
			tmp = str;
			str = ft_substr(env[i], ft_strlen(str) + 1, ft_strlen(env[i]));
			free(tmp);
			return (str);
		}
		i++;
	}
	tmp = str;
	str = ft_strdup("\0");
	free(tmp);
	return (str);
}

char	**return_cmd(char *str)
{
	int		i;
	int		j;
	char	**spl;

	i = 0;
	if (!str)
		return (NULL);
	str = change_value_cmd(str);
	spl = ft_split(str, ' ');
	spl = change_value2(spl);
	while (spl[i])
	{
		j = 0;
		while (spl[i][j])
		{
			if (spl[i][j] == 127)
				spl[i][j] = ' ';
			j++;
		}
		i++;
	}
	free(str);
	return (spl);
}
