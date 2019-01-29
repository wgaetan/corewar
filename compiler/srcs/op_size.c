/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   op_size.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/14 17:11:21 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/24 20:36:51 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

void	calc_op_size(t_op *op)
{
	t_op_model	op_model;
	int			i;

	i = 0;
	op_model = get_op_model(op->type);
	op->size = 1 + op_model.ocp;
	while (i < op->pcount)
	{
		if (op->params[i].type & T_REG)
			op->size += (op->params[i].size = 1);
		else if (op->params[i].type & T_IND)
			op->size += (op->params[i].size = IND_SIZE);
		else if (op->params[i].type & T_DIR)
			op->size += (op->params[i].size = op_model.dir_size);
		i++;
	}
}
