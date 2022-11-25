/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 18:13:52 by mrobaii           #+#    #+#             */
/*   Updated: 2022/11/25 22:07:21 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishel.h"

void	ft_cd(char *cmd, t_envp *env)
{
	char	oldpwd[1024];
	char	pwd[1024];

	if (!getcwd(oldpwd, 1024))
		perror(NULL);
	if (!cmd)
		cmd = expand_env(env, "HOME");
	if (chdir (cmd) != 0)
	{
		if (!cmd)
		{
			ft_putstr_fd("HOME is not set\n", 2);
			get_var(1, 1);
			return ;
		}
		perror(NULL);
	}
	if (!getcwd(pwd, 1024))
		perror(NULL);
	updatt_pwd(env, pwd, "PWD");
	updatt_pwd(env, oldpwd, "OLDPWD");
	get_var(1, 0);
}
