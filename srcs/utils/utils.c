/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 00:54:15 by mrobaii           #+#    #+#             */
/*   Updated: 2022/11/26 02:09:28 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishel.h"

t_envp	*ft_lstnew(char *value, char *var, char *key)
{
	t_envp	*node;

	node = malloc(sizeof(t_envp));
	node->var = var;
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

void	ft_free(char **ptr)
{
	int	i;

	if (!ptr)
		return ;
	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}

t_envp	*inisialize_env(char **envp)
{
	t_envp	*env;
	t_envp	*head;
	int		i;
	char	**split;

	if (!envp[0])
		return (NULL);
	split = ft_split(envp[0], '=');
	env = ft_lstnew(split[1], split[0], ft_strdup("="));
	free(split);
	head = env;
	i = 1;
	while (envp[i])
	{
		split = ft_split(envp[i], '=');
		env->next = ft_lstnew(split[1], split[0], ft_strdup("="));
		free(split);
		env = env->next;
		i++;
	}
	return (head);
}

void	ft_print_export(t_envp *export)
{
	while (export)
	{
		printf("declare -x %s%s", export->var, export->key);
		if (export->key[0])
			printf("\"%s\"", export->value);
		printf("\n");
		export = export->next;
	}
	get_var(1, 0);
}

void	ft_print_env(t_envp *env)
{
	while (env)
	{
		if (ft_strlen(env->key))
		{
			printf("%s%s%s\n", env->var, env->key, env->value);
		}
		env = env->next;
	}
}
