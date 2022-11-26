/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 16:02:44 by mrobaii           #+#    #+#             */
/*   Updated: 2022/11/26 02:07:10 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishel.h"

#define RESET   "\033[0m"
#define BLUE   "\033[32m"      /* Green */
int	check_all_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (1);
			i++;
	}
	return (0);
}

void	lets_go(t_mini *mini, char *line, t_cmd **cmd, char **envp)
{
	t_cmd	*shell;

	mini->lexer = lexer_init(line);
	mini->token = ft_get_tokens(mini->lexer, envp);
	shell = get_cmd_file(mini->token, *cmd);
	*cmd = shell;
	free_token(&mini->token);
	mini->token = NULL;
	cmd = NULL;
	free(line);
}

void	cmd_free(t_var *var)
{
	t_cmd	*tmp;
	t_file	*temp;

	while (var->cmd)
	{
		tmp = var->cmd;
		var->cmd = var->cmd->next;
		while (tmp->file)
		{
			temp = tmp->file;
			tmp->file = tmp->file->next;
			free(temp->file);
			free(temp);
		}
		ft_free(tmp->cmd);
		free(tmp);
	}
	free(var->envp);
}

void	inisialize_main(t_var **var, char **ev)
{
	*var = malloc(sizeof(t_var));
	(*var)->line = NULL;
	(*var)->mini = malloc(sizeof(t_mini));
	(*var)->env = inisialize_env(ev);
	get_var(1, 0);
	(*var)->cmd = NULL;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int ac, char **av, char **ev)
{
	t_var	*var;

	(void) ac;
	(void) av;
	inisialize_main(&var, ev);
	while (1)
	{
		var->envp = list_to_array(var->env);
		var->line = readline(BLUE "minishell-13.37$  " RESET);
		if (var->line == NULL)
		{
			printf("exit\n");
			exit(get_var(0, 0));
		}
		if (check_all_space(var->line))
		{
			add_history(var->line);
			lets_go(var->mini, var->line, &var->cmd, var->envp);
		}
		else
			free(var->line);
		if (var->cmd)
			execution(var->cmd, &var->env);
		cmd_free(var);
	}
}
