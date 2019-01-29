/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   operateurs.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/06 20:48:06 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/24 17:00:34 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op_vm.h"

int		invalid_ocp(t_proc *proc, t_opmodvm *optab, int *opc)
{
	proc->ocp = (proc->ocp >> (8 -
				(2 * optab[proc->type].paramnb))) <<
		(8 - (2 * optab[proc->type].paramnb));
	proc->size = opc[(proc->ocp & 0xC0) >> 6]
		+ opc[(proc->ocp & 0x30) >> 4]
		+ opc[(proc->ocp & 0xC) >> 2] + 2;
	return (-1);
}

int		check_regnum(t_proc *proc, t_opmodvm *optab, int *opc)
{
	int			i;

	i = 0;
	while (i < proc->paramnb)
	{
		if (proc->paramtype[i] == T_REG && (proc->paramval[i] < 0
					|| proc->paramval[i] > REG_NUMBER - 1))
		{
			proc->ocp = (proc->ocp >> (8 - (2 *
							optab[proc->type].paramnb))) << (8
						- (2 * optab[proc->type].paramnb));
			proc->size = (opc[(proc->ocp & 0xC0) >> 6]
					+ opc[(proc->ocp & 0x30) >> 4]
				+ opc[(proc->ocp & 0xC) >> 2] + 2);
			return (0);
		}
		i++;
	}
	return (1);
}

int		launch_proc(t_proc *proc, t_vm *vm, int procnb)
{
	static int	(*f[17])(t_proc *proc, t_vm *vm) = {0,
		ft_live, ft_ld, ft_st, ft_add, ft_sub, ft_and, ft_or, ft_xor, ft_zjmp,
		ft_ldi, ft_sti, ft_fork, ft_lld, ft_lldi, ft_lfork, ft_aff};
	static int	opc[4] = {0, 1, 0, 2};
	t_opmodvm	*optab;

	optab = get_op_tab_vm();
	opc[2] = optab[proc->type].dirsize;
	if (proc->size == 1)
		return (-1);
	if (optab[proc->type].ocp && (proc->ocp < 64 || proc->ocp > 255
				|| !check_ocp(proc)))
		return (invalid_ocp(proc, optab, opc));
	else if (!proc->size)
		proc->size = calc_size(proc);
	if (!check_regnum(proc, optab, opc))
		return (-1);
	if (proc->type != 16)
		verb_procnb(vm, procnb, proc->size);
	return (f[proc->type](proc, vm));
}
