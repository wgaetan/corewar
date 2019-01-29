/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_tokens.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/07 21:28:16 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/24 20:36:59 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

void		put_str_color(unsigned char tc, unsigned char bc, char *str)
{
	if (tc == UNKNOWN_TOKEN)
		ft_putstr(WHITE);
	else if (tc == COMMAND_TOKEN)
		ft_putstr(YELLOW);
	else if (tc == LABEL_TOKEN)
		ft_putstr(BLUE);
	else if (tc == OP_TOKEN)
		ft_putstr(MAGENTA);
	else if (tc == COMMENT_TOKEN)
		ft_putstr(CYAN);
	else if (tc == NEWLINE_TOKEN || tc == WHITESPACE_TOKEN)
		ft_putstr(BLACK);
	if (bc == 0)
		ft_putstr(G_BACK);
	else if (bc > 0)
		ft_putstr(R_BACK);
	if (tc == NEWLINE_TOKEN)
		ft_putstr("\U000021B2 \e[0m\n");
	else if (tc == WHITESPACE_TOKEN)
		ft_putstr(" \U00002423 ");
	else
		ft_putstr(str);
	ft_putstr(RESET);
}

void		print_tokens(void)
{
	t_stock	*stock;
	int		i;

	stock = get_stock();
	i = 0;
	while (i < stock->tokens_count)
	{
		put_str_color(stock->tokens[i].type, stock->tokens[i].error,
				stock->tokens[i].content);
		i++;
	}
}
