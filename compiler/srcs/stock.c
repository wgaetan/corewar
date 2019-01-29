/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   stock.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <wgaetan@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/30 20:24:18 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/24 20:37:05 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

/*
** A way to access stock without having to pass it as parameter
** But with easier access control than a global var.
*/

t_stock		*get_stock(void)
{
	static t_stock	*stock = NULL;

	if (stock == NULL)
	{
		stock = gc_alloc(sizeof(t_stock), 0);
		stock->tokens = NULL;
		stock->tokens_limits = NULL;
		stock->operators = NULL;
		stock->labels = NULL;
		stock->labels_pos = NULL;
		stock->labels_count = 0;
		stock->tokens_count = 0;
	}
	return (stock);
}
