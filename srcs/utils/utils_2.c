/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 21:37:36 by mrobaii           #+#    #+#             */
/*   Updated: 2022/11/25 22:11:19 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishel.h"

void	ft_add_back(t_envp **lst, t_envp *new)
{
	t_envp	*tmp;

	tmp = NULL;
	if (lst)
	{
		if (*lst)
		{
			tmp = *lst;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
		else
			*lst = new;
	}
	new->next = NULL;
}

int	check_error_export(char *str)
{
	int	i;

	i = 0;
	if (str[0] < 'A' || (str[0] > 'Z' && str[0] < 'a')
		|| str[0] > 'z')
	{		
		printf("export: `%s': not a valid identifier\n", str);
		get_var(1, 1);
		return (1);
	}
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && !ft_isalpha(str[i]))
		{
			printf("test: `%s': not a valid identifier\n", str);
			get_var(1, 1);
			return (1);
		}
			i++;
	}
	return (0);
}

void	free_export_node(t_envp *env)
{
	free(env->key);
	free(env->value);
	free(env->var);
	free(env);
}

void	updatt_pwd(t_envp *env, char *value, char *var)
{
	while (env)
	{
		if (!ft_strncmp(env->var, var, ft_strlen(var) + 1))
		{
			free(env->value);
			env->value = ft_strdup(value);
			return ;
		}
		env = env->next;
	}
}

char	*expand_env(t_envp *env, char *var)
{
	while (env)
	{
		if (!ft_strncmp(env->var, var, ft_strlen(var) + 1))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
