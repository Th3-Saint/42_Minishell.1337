/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mas <aait-mas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:46:55 by aait-mas          #+#    #+#             */
/*   Updated: 2022/11/25 22:39:09 by aait-mas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "minishel.h"
# include "token.h"

typedef struct lexer
{
	char	*line;
	int		line_size;
	char	c;
	int		i;
	int		j;
}	t_lexer;

/* |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| */
t_lexer	*lexer_init(char *line);

/* |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| */
t_token	*ft_get_tokens(t_lexer *lexer, char **env);
void	lexer_skip_white_space(t_lexer *lexer);
void	token_add_back(t_token **token, char *value, int type);
t_token	*token_init(char *value, int type);

/* |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| */
void	get_tokens(t_lexer *lexer, t_token *token, char **env);
int		check_special_char(char c);
void	lexer_move(t_lexer *lexer);
void	lexer_move_with(t_lexer *lexer, t_token *token, int type, char *value);
char	*get_word(t_lexer *lexer, char **env);
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
char	*develop(t_lexer *lexer, char **env);
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
char	*check_env(char *str, char **env);
int		test_cmp(char *str, char *str1);
int		check_char(char *str, char c);

/* -------------------------------------------------------------------------- */
char	*convert_char_to_str(char c);
void	free_norm(char *tmp, char *c);
void	lexer_back(t_lexer *lexer);
/* -------------------------------------------------------------------------- */
void	check_after_word(t_token *token, t_lexer *lexer);
void	get_btw_single_quote(t_lexer *lexer, t_token *token);
int		check_second_s_quote(t_lexer *lexer);
void	get_btw_double_quote(t_lexer *lexer, t_token *token, char **env);
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
int		check_second_d_quote(t_lexer *lexer);
char	*get_exit_code(t_lexer *lexer, char *c);
int		help_gbdq(t_lexer *lexer);
char	*develop2(t_lexer *lexer, char **env);
char	*convert_char_to_str(char c);
void	check_after_space(t_lexer *lexer, t_token *token);
/* -------------------------------------------------------------------------- */
/* |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| */
void	free_token(t_token **token);
int		heredoc(char *del, int *flag);
char	**return_cmd(char *str);

#endif