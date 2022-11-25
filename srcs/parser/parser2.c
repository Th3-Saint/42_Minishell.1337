/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mas <aait-mas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:00:07 by aait-mas          #+#    #+#             */
/*   Updated: 2022/11/25 22:33:08 by aait-mas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishel.h"

t_file	*file_init(char *f, int type)
{
	t_file	*file;

	file = malloc(sizeof(t_file));
	file->file = ft_strdup(f);
	file->type = type;
	file->next = NULL;
	return (file);
}

t_cmd	*cmd_init(char **str, t_file *file)
{
	t_cmd	*cmd;
	t_file	*tmp_file;
	t_file	*new_file;

	new_file = NULL;
	tmp_file = file;
	cmd = malloc(sizeof(t_cmd));
	cmd->cmd = str;
	while (tmp_file)
	{
		file_add_back(&new_file, tmp_file->file, tmp_file->type);
		tmp_file = tmp_file->next;
	}
	cmd->file = new_file;
	cmd->next = NULL;
	while (file)
	{
		tmp_file = file;
		file = file->next;
		free(tmp_file->file);
		free(tmp_file);
	}
	return (cmd);
}

void	file_add_back(t_file **file, char *f, int type)
{
	t_file	*last;
	t_file	*tmp;

	if (!*file)
	{
		*file = file_init(f, type);
		return ;
	}
	last = file_init(f, type);
	tmp = (*file);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = last;
}

void	cmd_add_back(t_cmd **cmd, char **str, t_file *f)
{
	t_cmd	*last;
	t_cmd	*tmp;

	if (!*cmd)
	{
		*cmd = cmd_init(str, f);
		return ;
	}
	last = cmd_init(str, f);
	tmp = (*cmd);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = last;
}
