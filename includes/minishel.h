/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishel.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:43:24 by aait-mas          #+#    #+#             */
/*   Updated: 2022/11/25 22:18:23 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
#define MINISHELL_H

#include "../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/wait.h>
#include <limits.h>
#include <errno.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../includes/lexer.h"
#include "../includes/token.h"
#include "../includes/parser.h"

typedef struct minishel
{
	t_token *token;
	t_lexer *lexer;
	char **env;
} t_mini;

typedef struct t_env
{
	int ret_val;
	struct t_env *next;
} t_env;
t_env *g_env;

typedef struct  t_envp
{
	char	*var;
	char	*key;
	char	*value;
	struct t_envp *next;
}	t_envp;

typedef struct variables{
	t_mini	*mini;
	char	*line;
	t_cmd	*cmd;
	t_cmd	*tmp;
	char	**envp;
	t_envp	*env;
}	t_var;

typedef struct exec_var
{
	char	**path;
	char	*cmd_path;
	int		pid;
	int		status;
	int		*fd;
	int		fd_save;
	char	**envp;
}	t_exec;

int		get_var(int op, int value);
void	lets_go(t_mini *mini,char *line, t_cmd **cmd, char **envp);
void	correction2(t_token *token);
void	free_norm(char *tmp, char *c);
int		help_gbdq(t_lexer *lexer);
char	*help_gbdq_1(t_lexer *lexer, char *c, char *value);
char	*get_exit_code(t_lexer *lexer, char *c);
void	execution(t_cmd *cmd, t_envp **env);
void	ft_echo(t_cmd *cmd);
void	ft_pwd(t_cmd *cmd);
t_envp	*inisialize_env(char **envp);
void	ft_print_export(t_envp *export);
t_envp	*ft_lstnew(char *value, char *var, char *key);
void	ft_export(char **args, t_envp **envp);
void	ft_add_back(t_envp **lst, t_envp *new);
char	**my_split(char *str, char c);
void	ft_print_env(t_envp *env);
void	ft_free(char **ptr);
void	ft_unset(char **args, t_envp **env);
char	**list_to_array(t_envp *env);
void	bultins(t_cmd *cmd, t_envp **env);
int		check_bultins(char *cmd);
void	open_files(t_cmd *cmd);
void	ft_cd(char *cmd, t_envp *env);
int		is_directory(char *filename);
void	signal_handler(int signal);
void	multi_pipes(t_cmd *cmd, t_exec *var, t_envp **env);
void	cmd_free(t_var *var);
void	ft_exit(char **str);
void	ft_print_error(char *s, char *error);
void	del_node(t_envp **env, char *str);
int		check_exist(t_envp *env, t_envp *new);
void	ft_skip(char **cmd, int *flag, int *i);
void	free_export_node(t_envp *env);
int		check_error_export(char *str);
char	*expand_env(t_envp *env, char *var);
void	updatt_pwd(t_envp *env, char *value, char *var);
#endif