/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 02:18:02 by mrobaii           #+#    #+#             */
/*   Updated: 2022/11/26 01:13:37 by mrobaii          ###   ########.fr       */
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

int	inisialize_builtins(t_exec *var, t_cmd *cmd, t_envp **env)
{
	var->status = -10;
	var->fd_save = -1;
	open_files(cmd);
	var->fd = malloc(sizeof(int) * 2);
	var->path = ft_split(ft_find_path(*env), ':');
	if (check_bultins(cmd->cmd[0]) && !cmd->next)
	{
		bultins(cmd, env);
		free (var->fd);
		ft_free(var->path);
		free (var);
		return (1);
	}
	return (0);
}

void	execute_commands(t_cmd *cmd, t_envp **env, t_exec *var)
{
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
}

void	execution(t_cmd *cmd, t_envp **env)
{
	t_exec	*var;
	int		res;

	res = 0;
	var = malloc(sizeof(t_exec));
	if (inisialize_builtins(var, cmd, env))
		return ;
	execute_commands(cmd, env, var);
	close(var->fd[0]);
	free(var->fd);
	ft_free(var->path);
	while (res != -1)
		res = waitpid(-1, &var->status, 0);
	if (var->status != -10)
	{
		if (WIFEXITED(var->status))
			get_var(1, WEXITSTATUS(var->status));
		if (WIFSIGNALED(var->status))
			get_var(1, WTERMSIG(var->status) + 128);
	}
	signal(SIGINT, signal_handler);
	free(var);
}
