/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 18:10:22 by mrobaii           #+#    #+#             */
/*   Updated: 2022/11/25 22:07:33 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishel.h"

int	check_bultins(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp("export", cmd, ft_strlen("export") + 1))
		return (1);
	else if (!ft_strncmp("unset", cmd, ft_strlen("unset") + 1))
		return (1);
	else if (!ft_strncmp("echo", cmd, ft_strlen("echo") + 1))
		return (1);
	else if (!ft_strncmp("pwd", cmd, ft_strlen("pwd") + 1))
		return (1);
	else if (!ft_strncmp("exit", cmd, ft_strlen("exit") + 1))
		return (1);
	else if (!ft_strncmp("env", cmd, ft_strlen("env") + 1))
		return (1);
	else if (!ft_strncmp("cd", cmd, ft_strlen("cd") + 1))
		return (1);
	return (0);
}

void	ft_skip(char **cmd, int *flag, int *i)
{
	int	j;

	*flag = 1;
	while (cmd[*i] && cmd[*i][0] == '-')
	{
		j = 1;
		while (cmd[*i][j] == 'n')
			j++;
		if (ft_strlen(cmd[*i] + j) || !cmd[*i][1])
			return ;
		else
			*flag = 0;
		(*i)++;
	}
}

int	check_exist(t_envp *env, t_envp *new)
{
	while (env)
	{
		if (!ft_strncmp(env->var, new->var, ft_strlen(env->var) + 1))
		{
			if (ft_strlen(new->key))
			{
				free(env->key);
				free(env->value);
				env->key = ft_strdup("=");
				env->value = ft_strdup(new->value);
				free_export_node(new);
			}
			else
				free_export_node(new);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

void	del_node(t_envp **env, char *str)
{
	t_envp	*previous;
	t_envp	*head;
	int		i;

	i = 1;
	head = *env;
	while (head)
	{
		if (!ft_strncmp(str, head->var, ft_strlen(str) + 1))
		{
			if (i == 1)
			{
				*env = head->next;
				free_export_node(head);
			}
			else
			{
				previous->next = head->next;
				free_export_node(head);
			}
		}
		previous = head;
		head = head->next;
		i++;
	}
}

void	bultins(t_cmd *cmd, t_envp **env)
{
	if (!ft_strncmp("export", cmd->cmd[0], ft_strlen("export") + 1))
		ft_export(cmd->cmd, env);
	else if (!ft_strncmp("unset", cmd->cmd[0], ft_strlen("unset") + 1))
		ft_unset(cmd->cmd, env);
	else if (!ft_strncmp("echo", cmd->cmd[0], ft_strlen("echo") + 1))
		ft_echo(cmd);
	else if (!ft_strncmp("pwd", cmd->cmd[0], ft_strlen("pwd") + 1))
		ft_pwd(cmd);
	else if (!ft_strncmp("exit", cmd->cmd[0], ft_strlen("exit") + 1))
		ft_exit(cmd->cmd);
	else if (!ft_strncmp("env", cmd->cmd[0], ft_strlen("env") + 1))
		ft_print_env(*env);
	else if (!ft_strncmp("cd", cmd->cmd[0], ft_strlen("cd") + 1))
		ft_cd(cmd->cmd[1], *env);
}
