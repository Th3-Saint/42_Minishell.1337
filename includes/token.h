/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mas <aait-mas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:47:09 by aait-mas          #+#    #+#             */
/*   Updated: 2022/11/25 22:37:18 by aait-mas         ###   ########.fr       */
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
		TOKEN_DOUBLE_QUOTES,
		TOKEN_SINGLE_QUOTE,
		TOKEN_X,
	} e_tokn;
	char			*value;
	struct token	*next;
}	t_token;

#endif