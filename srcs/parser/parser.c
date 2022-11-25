/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:00:07 by aait-mas          #+#    #+#             */
/*   Updated: 2022/11/25 22:20:21 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishel.h"

t_file	*file_init(char *f, int type)
{
	t_file	*file;

	file = malloc(sizeof(t_file));
	file->file = ft_strdup(f);
	file->type = type;
	file->next = NULL;
	return (file);
}

t_cmd	*cmd_init(char **str, t_file *file)
{
	t_cmd	*cmd;
	t_file	*tmp_file;
	t_file	*new_file;

	new_file = NULL;
	tmp_file = file;
	cmd = malloc(sizeof(t_cmd));
	cmd->cmd = str;
	while (tmp_file)
	{
		file_add_back(&new_file, tmp_file->file, tmp_file->type);
		tmp_file = tmp_file->next;
	}
	cmd->file = new_file;
	cmd->next = NULL;
	while (file)
	{
		tmp_file = file;
		file = file->next;
		free(tmp_file->file);
		free(tmp_file);
	}
	return (cmd);
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

int	check_error_quote(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == TOKEN_FLAG)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	check_error_flags(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == TOKEN_REDIR_IN || tmp->type == TOKEN_REDIR_OUT
			|| tmp->type == D_TOKEN_REDIR_IN || tmp->type == D_TOKEN_REDIR_OUT)
		{
			if (tmp->next == NULL)
				return (0);
			if (!(tmp->next->type == TOKEN_DOLLAR
					|| tmp->next->type == TOKEN_SINGLE_QUOTE
					|| tmp->next->type == TOKEN_DOUBLE_QUOTES
					|| tmp->next->type == TOKEN_WORD))
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	check_error_pipe(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (tmp->next && tmp->next->type == TOKEN_PIPE)
		return (0);
	while (tmp)
	{
		if (tmp->type == TOKEN_PIPE)
		{
			if (!(tmp->next) || tmp->next->type == TOKEN_PIPE)
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

void	file_add_back(t_file **file, char *f, int type)
{
	t_file	*last;
	t_file	*tmp;

	if (!*file)
	{
		*file = file_init(f, type);
		return ;
	}
	last = file_init(f, type);
	tmp = (*file);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = last;
}

void	cmd_add_back(t_cmd **cmd, char **str, t_file *f)
{
	t_cmd	*last;
	t_cmd	*tmp;

	if (!*cmd)
	{
		*cmd = cmd_init(str, f);
		return ;
	}
	last = cmd_init(str, f);
	tmp = (*cmd);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = last;
}

t_cmd	*get_cmd_file(t_token *token, t_cmd *cmd)
{
	t_token	*tmp;
	t_file	*file;
	char	*str;

	tmp = token;
	file = NULL;
	str = ft_strdup("");
	if (token_red_flag(token) == 1)
	{
		free(str);
		return (NULL);
	}
	cmd = get_cmd(tmp, cmd, str, file);
	// close_cmd(token, cmd);
	return (cmd);
}

int	check_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c)
		i++;
	return (i);
}

int	test_cmp(char *str, char *str1)
{
	if (ft_strlen(str) <= (size_t)check_char(str1, '='))
		return (check_char(str1, '='));
	else
		return (ft_strlen(str));
}

int	token_red_flag(t_token *token)
{
	if (check_error_quote(token) == 0)
	{
		printf("Error quote\n");
		get_var(1, 127);
		return (1);
	}
	else if (check_error_flags(token) == 0)
	{
		printf("Syntax Error\n");
		get_var(1, 258);
		return (1);
	}
	else if (check_error_pipe(token) == 0)
	{
		printf("Syntax Error pipe\n");
		get_var(1, 258);
		return (1);
	}
	else
		return (0);
}

void	close_cmd(t_token *token, t_cmd *cmd)
{
	t_token	*t_token;
	t_cmd	*t_cmd;
	int		i;
	int		j;

	t_token = token;
	t_cmd = cmd;
	while (t_cmd)
	{
		j = 0;
		j = while_not_pipe(t_token, j);
		if (j == 0)
		{
			i = 0;
			while (t_cmd->cmd[i])
			{
				free(t_cmd->cmd[i]);
				t_cmd->cmd[i] = NULL;
				i++;
			}
		}
		if (t_token && t_token->type == TOKEN_PIPE)
			t_token = t_token->next;
		t_cmd = t_cmd->next;
	}
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

int	while_not_pipe(t_token *t_token, int x)
{
	while (t_token && t_token->type != TOKEN_PIPE)
	{
		if (t_token->type == TOKEN_WORD || t_token->type == TOKEN_DOUBLE_QUOTES
			|| t_token->type == TOKEN_SINGLE_QUOTE)
			x++;
		t_token = t_token->next;
	}
	return (x);
}

void	help_get_cmd(t_cmd **cmd, t_file **file, char **str)
{
	cmd_add_back(cmd, return_cmd(*str), *file);
	*file = NULL;
	*str = ft_strdup("");
}

t_cmd	*get_cmd(t_token *tmp, t_cmd *cmd, char *str, t_file *file)
{
	while (tmp)
	{
		if (tmp->type == D_TOKEN_REDIR_IN || tmp->type == D_TOKEN_REDIR_OUT
			|| tmp->type == TOKEN_REDIR_IN || tmp->type == TOKEN_REDIR_OUT)
		{
			file_add_back(&file, tmp->next->value, tmp->type);
			tmp = tmp->next;
		}
		else if (tmp->type == TOKEN_DOUBLE_QUOTES
			|| tmp->type == TOKEN_SINGLE_QUOTE
			|| tmp->type == TOKEN_WORD || tmp->type == TOKEN_SPACE)
		{
			if (tmp->type == TOKEN_DOUBLE_QUOTES
				|| tmp->type == TOKEN_SINGLE_QUOTE)
				tmp->value = ft_change(tmp);
			str = get_string(tmp, str);
		}
		else if (tmp->type == TOKEN_PIPE)
		{
			help_get_cmd(&cmd, &file, &str);
		}
		tmp = tmp->next;
	}
	if (file || str)
		cmd_add_back(&cmd, return_cmd(str), file);
	return (cmd);
}
