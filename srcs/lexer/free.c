/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 04:02:29 by aait-mas          #+#    #+#             */
/*   Updated: 2022/11/25 22:10:37 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishel.h"

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

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmpcmd;
	t_file	*tmpfile;
	int		i;

	while (cmd)
	{
		tmpcmd = cmd;
		while (tmpcmd->file)
		{
			tmpfile = tmpcmd->file;
			tmpcmd->file = tmpcmd->file->next;
			free(tmpfile->file);
			free(tmpfile);
		}
		i = 0;
		if (tmpcmd->cmd)
		{
			while (tmpcmd->cmd[i])
			{
				free(tmpcmd->cmd[i]);
				i++;
			}
			free(tmpcmd->cmd);
		}
		cmd = cmd->next;
		free(tmpcmd);
	}
}

void	free_norm(char *tmp, char *c)
{
	free(tmp);
	free(c);
}
