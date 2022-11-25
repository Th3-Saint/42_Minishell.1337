/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 22:16:09 by mrobaii           #+#    #+#             */
/*   Updated: 2022/11/25 22:08:59 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishel.h"

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
