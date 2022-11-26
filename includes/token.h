/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:47:09 by aait-mas          #+#    #+#             */
/*   Updated: 2022/11/25 23:06:50 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
# include "minishel.h"

typedef struct token
{
	enum
	{
		TOKEN_START,
		TOKEN_WORD,
		TOKEN_PIPE,
		TOKEN_REDIR_IN,
		TOKEN_REDIR_OUT,
		D_TOKEN_REDIR_IN,
		D_TOKEN_REDIR_OUT,
		TOKEN_DOLLAR,
		TOKEN_SPACE,
		TOKEN_FLAG,
		TKN_DQ,
		TKN_SQ,
		TOKEN_X,
	} e_tokn;
	char			*value;
	struct token	*next;
}	t_token;

#endif