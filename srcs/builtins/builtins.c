/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 02:53:06 by mrobaii           #+#    #+#             */
/*   Updated: 2022/11/25 22:07:41 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishel.h"
#include <limits.h>

void	ft_echo(t_cmd *cmd)
{
	int	i;
	int	flag;
	int	file;

	file = 1;
	i = 1;
	if (cmd->outfile != -1)
		file = cmd->outfile;
	ft_skip(cmd->cmd, &flag, &i);
	while (cmd->cmd[i])
	{
		ft_putstr_fd(cmd->cmd[i++], file);
		if (cmd->cmd[i])
			write(file, " ", 1);
	}
	if (flag == 1)
		write(file, "\n", 1);
	get_var(1, 0);
}

void	ft_pwd(t_cmd *cmd)
{
	char	pwd[1024];

	getcwd(pwd, sizeof(pwd));
	if (cmd->outfile != -1)
	{
		write(cmd->outfile, pwd, ft_strlen(pwd));
		write(cmd->outfile, "\n", 1);
	}
	else
	{
		ft_putstr_fd(pwd, 1);
		write(1, "\n", 1);
	}
	get_var(1, 0);
}

void	ft_export(char **args, t_envp **envp)
{
	int		i;
	char	**split;
	t_envp	*new;

	i = 1;
	if (!args[i])
	{
		ft_print_export(*envp);
		return ;
	}
	while (args[i])
	{
		split = my_split(args[i], '=');
		if (check_error_export(split[0]))
			ft_free(split);
		else
		{
			get_var(1, 0);
			new = ft_lstnew(split[2], split[0], split[1]);
			if (!check_exist(*envp, new))
				ft_add_back(envp, new);
			free(split);
		}
		i++;
	}
}

void	ft_unset(char **args, t_envp **env)
{
	int	i;

	i = 1;
	while (args[i])
	{
		del_node(env, args[i]);
		i++;
	}
	get_var(1, 0);
}

void	ft_exit(char **str)
{
	int	status;

	if (!str[1])
		exit(0);
	status = ft_atoi(str[1]);
	if (status == -2)
	{
		ft_print_error("", "numeric argument required\n");
		exit(255);
	}
	else if (str[2])
	{
		ft_print_error("", "exit: too many arguments\n");
		get_var(1, 1);
	}
	else
	{
		ft_putstr_fd("exit\n", 2);
		exit(status);
	}
}
