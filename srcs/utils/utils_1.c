/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 21:36:03 by mrobaii           #+#    #+#             */
/*   Updated: 2022/11/25 22:11:15 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishel.h"

char	**my_split(char *str, char c)
{
	char	**split;
	int		i;

	i = 0;
	split = malloc(sizeof(char *) * 4);
	while (str[i] && str[i] != c)
		i++;
	split[0] = ft_substr(str, 0, i);
	split[1] = ft_substr(str, i, 1);
	if (ft_strlen(str + i))
		split[2] = ft_strdup(str + i + 1);
	else
		split[2] = ft_strdup("");
	split[3] = NULL;
	return (split);
}

int	ft_lstlen(t_envp *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**list_to_array(t_envp *env)
{
	int		i;
	char	**envp;
	char	*tmp;
	char	*jon;

	envp = malloc(sizeof(char *) * (ft_lstlen(env) + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		tmp = ft_strjoin(env->var, "=");
		jon = tmp;
		tmp = ft_strjoin(tmp, env->value);
		free(jon);
		envp[i++] = tmp;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

int	is_directory(char *filename)
{
	struct stat	path;

	if (!filename)
		return (0);
	lstat(filename, &path);
	return (S_ISDIR(path.st_mode));
}

void	ft_print_error(char *s, char *error)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(error, 2);
}
