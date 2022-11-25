/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mas <aait-mas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:57:20 by aait-mas          #+#    #+#             */
/*   Updated: 2022/11/25 22:32:52 by aait-mas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishel.h"

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

int	test_cmp(char *str, char *str1)
{
	if (ft_strlen(str) <= (size_t)check_char(str1, '='))
		return (check_char(str1, '='));
	else
		return (ft_strlen(str));
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
