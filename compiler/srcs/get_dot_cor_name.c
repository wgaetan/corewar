/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_dot_cor_name.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/15 15:57:39 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/24 20:35:31 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static void	build_dot_cor_name(int len, int pos)
{
	t_stock	*stock;
	int		i;

	stock = get_stock();
	stock->dot_cor.name = gc_alloc(len + 1, 0);
	stock->dot_cor.name[len] = '\0';
	i = 0;
	while (i < pos)
	{
		stock->dot_cor.name[i] = stock->dot_s.name[i];
		i++;
	}
	stock->dot_cor.name[i] = '.';
	stock->dot_cor.name[i + 1] = 'c';
	stock->dot_cor.name[i + 2] = 'o';
	stock->dot_cor.name[i + 3] = 'r';
}

void		get_dot_cor_name(void)
{
	t_stock	*stock;
	int		len;
	int		last_dot;
	int		i;

	stock = get_stock();
	len = ft_strlen(stock->dot_s.name);
	if (len >= 2 && stock->dot_s.name[len - 1] == 's' &&
			stock->dot_s.name[len - 2] == '.')
		build_dot_cor_name(len + 2, len - 2);
	else
	{
		last_dot = 0;
		i = -1;
		while (++i < len)
			last_dot = stock->dot_s.name[i] == '.' ? i : last_dot;
		if (last_dot == 0 && stock->dot_s.name[0] == '.')
			build_dot_cor_name(4, 0);
		else if (last_dot == 0)
			build_dot_cor_name(len + 4, len);
		else
			build_dot_cor_name(last_dot + 4, last_dot);
	}
}
