/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tokens_limits.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <wgaetan@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/07 18:04:20 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/24 20:37:32 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

void		expand_tokens_limits_table(void)
{
	t_stock	*stock;
	int		*new;
	int		i;

	i = 0;
	stock = get_stock();
	new = gc_alloc(sizeof(int) * (stock->tokens_count + TOKENS_LIMIT_INC), 0);
	while (i < stock->tokens_count)
	{
		new[i] = stock->tokens_limits[i];
		i++;
	}
	i = 0;
	while (i < TOKENS_LIMIT_INC)
	{
		new[i + stock->tokens_count] = 0;
		i++;
	}
	gc_free(stock->tokens_limits, 0);
	stock->tokens_limits = new;
}

void		push_token_limit(int limit)
{
	t_stock	*stock;
	int		i;

	stock = get_stock();
	i = stock->tokens_count;
	if (stock->tokens_count % TOKENS_LIMIT_INC == 0)
		expand_tokens_limits_table();
	stock->tokens_limits[stock->tokens_count] = limit;
	stock->tokens_count++;
}

void		get_tokens_limits(void)
{
	t_stock	*stock;
	char	c;
	int		i;

	stock = get_stock();
	i = 0;
	while (i < (int)stock->dot_s.size)
	{
		c = stock->dot_s.content[i];
		if (c == COMMAND_CHAR)
			i += end_of_cmd_token(&stock->dot_s.content[i]);
		else if (c == COMMENT_CHAR)
			i += end_of_cmt_token(&stock->dot_s.content[i]);
		else if (c == ' ' || c == '\t')
			i += end_of_wsp_token(&stock->dot_s.content[i]);
		else if (ft_strchr(LABEL_CHARS, c) != NULL)
			i += end_of_lbl_or_op_token(&stock->dot_s.content[i]);
		else if (c != '\n')
			i += end_of_unknown_token(&stock->dot_s.content[i]);
		push_token_limit(i);
		i++;
	}
}
