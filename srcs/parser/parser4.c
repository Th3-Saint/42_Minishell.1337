/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mas <aait-mas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 03:37:28 by aait-mas          #+#    #+#             */
/*   Updated: 2022/11/25 22:33:20 by aait-mas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishel.h"

char	*ft_change(t_token *tmp)
{
	char	*str;
	char	*tmp2;
	char	*c;

	c = ft_strdup("@");
	str = ft_strjoin(c, tmp->value);
	tmp2 = str;
	str = ft_strjoin(str, c);
	free(tmp2);
	free(c);
	free(tmp->value);
	return (str);
}

char	*get_string(t_token *tmp, char *str)
{
	char	*tmp_token;

	tmp_token = str;
	str = ft_strjoin(str, tmp->value);
	free(tmp_token);
	return (str);
}

char	*change_value_cmd(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '@')
		{
			i++;
			while (str[i] && str[i] != '@')
			{
				if (str[i] == ' ')
					str[i] = 127;
				i++;
			}
		}
		if (str[i] != '\0')
			i++;
	}
	return (str);
}

char	**change_value2(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = delete(str[i]);
		i++;
	}
	return (str);
}

char	*delete(char *str)
{
	char	*join;
	char	*c;
	int		i;
	char	*tmp;

	i = 0;
	join = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '@')
			i++;
		else
		{
			c = convert_char_to_str(str[i]);
			tmp = join;
			join = ft_strjoin(join, c);
			free(tmp);
			free(c);
			i++;
		}
	}
	free(str);
	return (join);
}
