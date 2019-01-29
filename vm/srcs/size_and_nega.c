/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   manage_nega.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/25 21:31:52 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/24 16:57:54 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op_vm.h"

int		manage_nega(t_arg_type type, int dirsize, int val)
{
	int			ret;

	ret = val;
	if (val & 0x8000)
	{
		if (type == T_IND || (type == T_DIR && dirsize == 2))
			ret = -((val ^ 0xFFFF) + 1);
		else if (type == T_DIR && dirsize == 4)
			ret = -((val ^ 0xFFFFFFFF) + 1);
	}
	return (ret);
}

size_t	calc_size(t_proc *proc)
{
	int			size;
	int			i;
	static int	opc[4] = {0, 1, 0, 2};
	static int	opt[4] = {0, T_REG, T_DIR, T_IND};
	t_opmodvm	*optab;

	i = 0;
	optab = get_op_tab_vm();
	opc[2] = optab[proc->type].dirsize;
	if (optab[proc->type].ocp == 0)
	{
		proc->ocp = 0;
		proc->paramtype[0] = T_DIR;
		return (1 + opc[2]);
	}
	opc[2] = optab[proc->type].dirsize;
	proc->ocp = proc->ocp & (0xFC << (6 - optab[proc->type].paramnb * 2));
	size = (opc[(proc->ocp & 0xC0) >> 6] + opc[(proc->ocp & 0x30) >> 4]
		+ opc[(proc->ocp & 0xC) >> 2] + 2);
	while (i < proc->paramnb)
	{
		proc->paramtype[i] = opt[(proc->ocp >> (6 - (2 * i))) & 3];
		i++;
	}
	return (size);
}
