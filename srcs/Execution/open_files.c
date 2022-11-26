/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 01:12:42 by mrobaii           #+#    #+#             */
/*   Updated: 2022/11/26 03:37:15 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishel.h"

void	check_redections(t_cmd *cmd, t_file *tmp, int *flag)
{
	int		save;

	save = -1;
	while (tmp)
	{
		if (tmp->type == TOKEN_REDIR_IN)
		{
			cmd->infile = open(tmp->file, O_RDONLY);
			if (cmd->infile == -1)
				perror(NULL);
		}
		else if (tmp->type == TOKEN_REDIR_OUT)
			cmd->outfile = open(tmp->file, O_WRONLY | O_CREAT
					| O_TRUNC, 0644);
		else if (tmp->type == D_TOKEN_REDIR_OUT)
			cmd->outfile = open(tmp->file, O_WRONLY | O_CREAT
					| O_APPEND, 0644);
		else if (tmp->type == D_TOKEN_REDIR_IN && *flag == 0)
		{
			save = dup(STDIN_FILENO);
			signal(SIGINT, SIG_IGN);
			cmd->infile = heredoc(tmp->file, flag);
			signal(SIGINT, signal_handler);
		}
		if (save != -1)
			dup2(save, 0);
		tmp = tmp->next;
	}
}

void	open_files(t_cmd *cmd)
{
	t_file	*tmp;
	int		flag;

	flag = 0;
	while (cmd)
	{
		cmd->infile = -1;
		cmd->outfile = -1;
		tmp = cmd->file;
		check_redections(cmd, tmp, &flag);
	cmd = cmd->next;
	}
}
