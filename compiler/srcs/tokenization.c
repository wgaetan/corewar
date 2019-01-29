/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tokenization.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <wgaetan@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/07 15:02:39 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/24 20:37:18 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static void		get_token_type(t_token *token)
{
	char		first_char;
	char		last_char;

	token->type = 0;
	first_char = token->content[0];
	last_char = token->content[token->len - 1];
	if (first_char == COMMENT_CHAR)
		token->type = COMMENT_TOKEN;
	else if (first_char == COMMAND_CHAR)
		token->type = COMMAND_TOKEN;
	else if (first_char == ' ' || first_char == '\t')
		token->type = WHITESPACE_TOKEN;
	else if (last_char == LABEL_CHAR)
		token->type = LABEL_TOKEN;
	else if (first_char == '\n')
		token->type = NEWLINE_TOKEN;
	else if (ft_isalpha(first_char))
		token->type = OP_TOKEN;
	else
	{
		token->type = UNKNOWN_TOKEN;
		token->error |= E1;
	}
}

static void		fill_first_token(void)
{
	t_stock		*stock;

	stock = get_stock();
	stock->tokens[0].len = stock->tokens_limits[0] + 1;
	stock->tokens[0].content =
		gc_alloc(sizeof(char) * (stock->tokens[0].len + 1), 0);
	stock->tokens[0].content[stock->tokens[0].len] = '\0';
	ft_strncpy(stock->tokens[0].content,
			&stock->dot_s.content[0], stock->tokens[0].len);
	get_token_type(&stock->tokens[0]);
	if (stock->tokens[0].type != UNKNOWN_TOKEN)
		stock->tokens[0].error = 0;
}

static void		limits_to_token(void)
{
	t_stock		*stock;
	int			i;

	stock = get_stock();
	i = 1;
	stock->tokens = gc_alloc(sizeof(t_token) * stock->tokens_count, 0);
	fill_first_token();
	while (i < stock->tokens_count)
	{
		stock->tokens[i].len =
			stock->tokens_limits[i] - stock->tokens_limits[i - 1];
		stock->tokens[i].content =
			gc_alloc(sizeof(char) * (stock->tokens[i].len + 1), 0);
		stock->tokens[i].content[stock->tokens[i].len] = '\0';
		ft_strncpy(stock->tokens[i].content,
				&stock->dot_s.content[stock->tokens_limits[i - 1] + 1],
				stock->tokens[i].len);
		get_token_type(&stock->tokens[i]);
		if (stock->tokens[i].type != UNKNOWN_TOKEN)
			stock->tokens[i].error = 0;
		i++;
	}
}

static	void	fill_tokens_pos(void)
{
	t_stock		*stock;
	int			i;
	int			a;
	int			b;

	stock = get_stock();
	i = 0;
	a = 1;
	b = 0;
	while (i < stock->tokens_count)
	{
		stock->tokens[i].pos[0] = a;
		stock->tokens[i].pos[1] = b;
		if (stock->tokens[i].type == NEWLINE_TOKEN)
		{
			a++;
			b = -1;
		}
		i++;
		b++;
	}
}

void			tokenize(void)
{
	get_tokens_limits();
	limits_to_token();
	check_labels();
	fill_tokens_pos();
}
