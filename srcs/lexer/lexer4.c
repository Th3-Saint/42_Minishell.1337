/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mas <aait-mas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 03:05:47 by aait-mas          #+#    #+#             */
/*   Updated: 2022/11/25 22:32:46 by aait-mas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishel.h"

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

int	check_second_s_quote(t_lexer *lexer)
{
	lexer->j = lexer->i;
	lexer->j += 1;
	while (lexer->line[lexer->j] != '\0')
	{
		if (lexer->line[lexer->j] == '\'')
			return (0);
		lexer->j++;
	}
	return (1);
}

int	check_second_d_quote(t_lexer *lexer)
{
	lexer->j = lexer->i;
	lexer->j += 1;
	while (lexer->line[lexer->j] != '\0')
	{
		if (lexer->line[lexer->j] == '"')
			return (0);
		lexer->j++;
	}
	return (1);
}
