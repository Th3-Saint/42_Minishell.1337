/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 02:18:02 by mrobaii           #+#    #+#             */
/*   Updated: 2022/11/25 22:09:51 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishel.h"
#include "../../libft/libft.h"

char	*path_finder(char **str, char *cmd)
{
	int		i;
	char	*path;
	char	*tmp;

	if (!cmd || !cmd[0])
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		path = ft_strjoin(str[i], "/");
		tmp = path;
		path = ft_strjoin(path, cmd);
		free(tmp);
		if (access(path, X_OK) != -1)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

void	open_files(t_cmd *cmd)
{
	t_file	*tmp;
	int		save;
	int		flag;

	save = -1;
	flag = 0;
	while (cmd)
	{
		cmd->infile = -1;
		cmd->outfile = -1;
		tmp = cmd->file;
		while (tmp)
		{
			if (tmp->type == TOKEN_REDIR_IN)
				cmd->infile = open(tmp->file, O_RDONLY);
			else if (tmp->type == TOKEN_REDIR_OUT)
				cmd->outfile = open(tmp->file, O_WRONLY | O_CREAT
						| O_TRUNC, 0644);
			else if (tmp->type == D_TOKEN_REDIR_OUT)
				cmd->outfile = open(tmp->file, O_WRONLY | O_CREAT
						| O_APPEND, 0644);
			else if (tmp->type == D_TOKEN_REDIR_IN && flag == 0)
			{
				save = dup(STDIN_FILENO);
				signal(SIGINT, SIG_IGN);
				cmd->infile = heredoc(tmp->file, &flag);
				signal(SIGINT, signal_handler);
			}
			if (save != -1)
				dup2(save, 0);
		tmp = tmp->next;
		}
	cmd = cmd->next;
	}
}

char	*ft_find_path(t_envp *env)
{
	while (env)
	{
		if (!ft_strncmp(env->var, "PATH", 5))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	execution(t_cmd *cmd, t_envp **env)
{
	t_exec	*var;
	int		res;

	res = 0;
	var = malloc(sizeof(t_exec));
	var->status = -10;
	var->fd_save = -1;
	open_files(cmd);
	var->fd = malloc(sizeof(int) * 2);
	var->path = ft_split(ft_find_path(*env), ':');
	if (check_bultins(cmd->cmd[0]) && !cmd->next)
	{
		bultins(cmd, env);
		free (var->fd);
		free (var);
		ft_free(var->path);
		return ;
	}
	while (cmd)
	{
		var->cmd_path = path_finder(var->path, cmd->cmd[0]);
		var->envp = list_to_array(*env);
		pipe(var->fd);
		signal(SIGINT, SIG_IGN);
		if (cmd->cmd[0])
			var->pid = fork();
		if (var->pid == 0 && cmd->cmd[0])
			multi_pipes(cmd, var, env);
		ft_free(var->envp);
		free(var->cmd_path);
		close(cmd->infile);
		close(cmd->outfile);
		if (var->fd_save != -1)
			close(var->fd_save);
		var->fd_save = var->fd[0];
		close(var->fd[1]);
		cmd = cmd->next;
	}
	close(var->fd[0]);
	free(var->fd);
	ft_free(var->path);
	while (res != -1)
		res = waitpid(-1, &var->status, 0);
	if (var->status != - 10)
	{
		if (WIFEXITED(var->status))
			get_var(1, WEXITSTATUS(var->status));
		if (WIFSIGNALED(var->status))
			get_var(1, WTERMSIG(var->status) + 128);
	}
	signal(SIGINT, signal_handler);
	free(var);
}
