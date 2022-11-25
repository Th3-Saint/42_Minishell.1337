/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mas <aait-mas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 03:36:40 by aait-mas          #+#    #+#             */
/*   Updated: 2022/11/25 22:33:16 by aait-mas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishel.h"

int	token_red_flag(t_token *token)
{
	if (check_error_quote(token) == 0)
	{
		printf("Error quote\n");
		get_var(1, 127);
		return (1);
	}
	else if (check_error_flags(token) == 0)
	{
		printf("Syntax Error\n");
		get_var(1, 258);
		return (1);
	}
	else if (check_error_pipe(token) == 0)
	{
		printf("Syntax Error pipe\n");
		get_var(1, 258);
		return (1);
	}
	else
		return (0);
}

int	check_error_quote(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->e_tokn == TOKEN_FLAG)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	check_error_flags(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->e_tokn == TOKEN_REDIR_IN || tmp->e_tokn == TOKEN_REDIR_OUT
			|| tmp->e_tokn == D_TOKEN_REDIR_IN
			|| tmp->e_tokn == D_TOKEN_REDIR_OUT)
		{
			if (tmp->next == NULL)
				return (0);
			if (!(tmp->next->e_tokn == TOKEN_DOLLAR
					|| tmp->next->e_tokn == TOKEN_SINGLE_QUOTE
					|| tmp->next->e_tokn == TOKEN_DOUBLE_QUOTES
					|| tmp->next->e_tokn == TOKEN_WORD))
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	check_error_pipe(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (tmp->next && tmp->next->e_tokn == TOKEN_PIPE)
		return (0);
	while (tmp)
	{
		if (tmp->e_tokn == TOKEN_PIPE)
		{
			if (!(tmp->next) || tmp->next->e_tokn == TOKEN_PIPE)
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	check_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c)
		i++;
	return (i);
}
