/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 03:36:24 by aait-mas          #+#    #+#             */
/*   Updated: 2022/11/25 23:07:08 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishel.h"

t_cmd	*get_cmd_file(t_token *token, t_cmd *cmd)
{
	t_token	*tmp;
	t_file	*file;
	char	*str;

	tmp = token;
	file = NULL;
	str = ft_strdup("");
	if (token_red_flag(token) == 1)
	{
		free(str);
		return (NULL);
	}
	cmd = get_cmd(tmp, cmd, str, file);
	return (cmd);
}

t_cmd	*get_cmd(t_token *tmp, t_cmd *cmd, char *str, t_file *file)
{
	while (tmp)
	{
		if (tmp->e_tokn == D_TOKEN_REDIR_IN || tmp->e_tokn == D_TOKEN_REDIR_OUT
			|| tmp->e_tokn == TOKEN_REDIR_IN || tmp->e_tokn == TOKEN_REDIR_OUT)
		{
			file_add_back(&file, tmp->next->value, tmp->e_tokn);
			tmp = tmp->next;
		}
		else if (tmp->e_tokn == TKN_DQ || tmp->e_tokn == TKN_SQ \
		|| tmp->e_tokn == TOKEN_WORD || tmp->e_tokn == TOKEN_SPACE)
		{
			if (tmp->e_tokn == TKN_DQ
				|| tmp->e_tokn == TKN_SQ)
				tmp->value = ft_change(tmp);
			str = get_string(tmp, str);
		}
		else if (tmp->e_tokn == TOKEN_PIPE)
		{
			help_get_cmd(&cmd, &file, &str);
		}
		tmp = tmp->next;
	}
	if (file || str)
		cmd_add_back(&cmd, return_cmd(str), file);
	return (cmd);
}

void	help_get_cmd(t_cmd **cmd, t_file **file, char **str)
{
	cmd_add_back(cmd, return_cmd(*str), *file);
	*file = NULL;
	*str = ft_strdup("");
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
