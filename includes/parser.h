/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:47:02 by aait-mas          #+#    #+#             */
/*   Updated: 2022/11/25 22:18:44 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include "minishel.h"

#define ERROR 0

typedef struct file
{
	char *file;
	int type;
	struct file *next;
} t_file;

typedef struct cmd
{
	char **cmd;
	t_file *file;
	int	infile;
	int	outfile;
	struct cmd *next;
} t_cmd;

typedef struct parser
{
	char *value;
	int type;
	struct parser *next;
} t_parser;


int check_error_quote(t_token *token);
int check_error_flags(t_token *token);
int check_error_pipe(t_token *token);
t_file *file_init(char *f, int type);
t_cmd *cmd_init(char **c, t_file *f);
void file_add_back(t_file **file, char *f, int type);
void cmd_add_back(t_cmd **cmd, char **c, t_file *f);
t_file *file_init(char *f, int type);
t_cmd *cmd_init(char **c, t_file *f);
t_cmd *get_cmd_file(t_token *token, t_cmd *cmd);
int check_char(char *str, char c);
int test_cmp(char *str, char *str1);
int token_red_flag(t_token *token);
void close_cmd(t_token *token, t_cmd *cmd);
char *change_value_cmd(char *str);
char **change_value2(char **str);
t_cmd *get_cmd(t_token *tmp, t_cmd *cmd, char *str, t_file *file);
char *ft_change(t_token *tmp);
char *get_string(t_token *tmp, char *str);
char *delete(char *str);
int while_not_pipe(t_token *t_token, int y);
void free_cmd(t_cmd *cmd);

#endif
