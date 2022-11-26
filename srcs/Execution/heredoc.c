/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 22:16:09 by mrobaii           #+#    #+#             */
/*   Updated: 2022/11/26 03:29:20 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishel.h"

int	get_var(int op, int value)
{
	static int		exit_status = 0;

	if (op == 0)
		return (exit_status);
	if (op == 1)
		exit_status = value;
	return (0);
}

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		get_var(1, 1);
	}
}

void	child(int fd, char *del)
{
	char	*str;

	while (1)
	{
		signal(SIGINT, SIG_DFL);
		str = readline(">");
		if (!str)
			exit(0);
		if (!ft_strncmp(del, str, ft_strlen(del) + 1))
			exit(0);
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
	}
}

int	heredoc(char *del, int *flag)
{
	int		fd[2];
	char	*str;
	int		pid;
	int		status;

	str = NULL;
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{	
		close (fd[0]);
		child(fd[1], del);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		get_var(1, WEXITSTATUS(status));
	else
	{
		*flag = 1;
		get_var(1, 1);
	}
	free(str);
	close(fd[1]);
	return (fd[0]);
}
