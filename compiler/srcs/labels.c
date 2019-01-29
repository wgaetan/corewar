/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   labels.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/08 18:31:36 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/24 20:35:47 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

int			wrong_label_char(char *content)
{
	int		error;
	int		i;
	int		len;

	i = 0;
	error = 0;
	len = ft_strlen(content);
	while (i < len)
	{
		if (ft_strchr(LABEL_CHARS, content[i]) == NULL)
		{
			if (!(content[i] == LABEL_CHAR && i == len - 1))
				error = E1;
		}
		i++;
	}
	return (error);
}

void		check_labels(void)
{
	t_stock	*stock;
	int		i;
	int		j;

	stock = get_stock();
	i = -1;
	while (++i < stock->tokens_count)
	{
		if (stock->tokens[i].type == LABEL_TOKEN)
		{
			if (ft_strlen(stock->tokens[i].content) <= 1)
				stock->tokens[i].error |= E3;
			stock->tokens[i].error |=
				wrong_label_char(stock->tokens[i].content);
			j = -1;
			while (++j < stock->tokens_count && stock->tokens[i].error == 0)
			{
				if (i != j && stock->tokens[j].type == LABEL_TOKEN)
					stock->tokens[i].error |= ft_strcmp(stock->tokens[j].content
							, stock->tokens[i].content) == 0 ? E2 : 0;
			}
		}
	}
}

void		create_label_array(void)
{
	t_stock	*stock;
	int		i;
	int		y;

	stock = get_stock();
	stock->labels_count = 0;
	i = -1;
	while (++i < stock->tokens_count)
	{
		if (stock->tokens[i].type == LABEL_TOKEN && stock->tokens[i].error == 0)
			stock->labels_count++;
	}
	stock->labels = gc_alloc(sizeof(char *) * stock->labels_count, 0);
	stock->labels_pos = gc_alloc(sizeof(int) * stock->labels_count, 0);
	i = -1;
	y = 0;
	while (++i < stock->tokens_count)
	{
		if (stock->tokens[i].type == LABEL_TOKEN && stock->tokens[i].error == 0)
		{
			stock->labels[y] = ft_strndup(stock->tokens[i].content,
					ft_strlen(stock->tokens[i].content) - 1);
			stock->labels_pos[y++] = 0;
		}
	}
}
