/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mas <aait-mas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 16:02:44 by mrobaii           #+#    #+#             */
/*   Updated: 2022/11/25 22:51:53 by aait-mas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishel.h"

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

int	get_var(int op, int value)
{
	static int		exit_status = 0;

	if (op == 0)
		return (exit_status);
	if (op == 1)
		exit_status = value;
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

void	signal_handler(int signal)
{
	if(signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		//rl_replace_line("", 0); 
		rl_redisplay();
	}
}

void	cmd_free(t_var *var)
{
	t_cmd	*tmp;
	t_file  *temp;

	while(var->cmd)
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
}

int	main(int ac, char **av, char **ev)
{
	t_var	*var;
	
	(void) ac;
	(void) av;
	var = malloc(sizeof(t_var));
	var->line = NULL;
	var->mini = malloc(sizeof(t_mini));
	var->env = inisialize_env(ev);
	get_var(1, 0);
	var->cmd = NULL;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		var->envp = list_to_array(var->env);
		var->line = readline("minishell-13.37$ ");
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

		ft_free(var->envp);
		if (var->cmd)
			execution(var->cmd, &var->env);
		cmd_free(var);
	}
}
