/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:34:22 by mrobaii           #+#    #+#             */
/*   Updated: 2022/11/25 22:08:55 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishel.h"

void	multi_pipes(t_cmd *cmd, t_exec *var, t_envp **env)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(var->fd[0]);
	if (cmd->next)
		dup2(var->fd[1], STDOUT_FILENO);
	if (cmd->outfile != -1)
		dup2(cmd->outfile, STDOUT_FILENO);
	if (var->fd_save != -1)
		dup2(var->fd_save, 0);
	if (cmd->infile != -1)
		dup2(cmd->infile, STDIN_FILENO);
	if (check_bultins(cmd->cmd[0]))
		bultins(cmd, env);
	else if (execve(var->cmd_path, cmd->cmd, var->envp) == -1)
	{
		if (var->cmd_path)
			perror(var->cmd_path);
		else if (!var->path)
			ft_print_error(cmd->cmd[0], ": No such a file or directory\n");
		else if (!var->cmd_path)
			ft_print_error(cmd->cmd[0], ": command not found\n");
		exit(127);
	}
	exit(0);
}
