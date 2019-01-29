/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   labels_value.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/14 17:11:05 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/24 20:35:54 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

void		get_labels_and_op_pos(void)
{
	t_stock	*stock;
	int		i;
	int		j;
	int		k;
	int		pos;

	stock = get_stock();
	i = 0;
	j = 0;
	k = 0;
	pos = 0;
	while (i < stock->tokens_count)
	{
		if (stock->tokens[i].type == LABEL_TOKEN)
			stock->labels_pos[j++] = pos;
		else if (stock->tokens[i].type == OP_TOKEN)
		{
			stock->operators[k].index = pos;
			pos += stock->operators[k++].size;
		}
		i++;
	}
}

void		calc_label_params(void)
{
	t_stock	*stock;
	int		i;
	int		j;
	int		value;

	stock = get_stock();
	i = 0;
	while (i < stock->op_count)
	{
		j = 0;
		while (j < stock->operators[i].pcount)
		{
			if (stock->operators[i].params[j].type & T_LAB)
			{
				value = stock->labels_pos[stock->operators[i].params[j].value]
					- stock->operators[i].index;
				stock->operators[i].params[j].is_negative = value < 0 ? 1 : 0;
				value *= value < 0 ? -1 : 1;
				stock->operators[i].params[j].value = value;
			}
			j++;
		}
		i++;
	}
}
