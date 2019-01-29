/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ope4.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/21 14:39:43 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/24 17:04:52 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op_vm.h"

int		check_ocp(t_proc *proc)
{
	int			i;
	t_opmodvm	*optab;

	i = 0;
	optab = get_op_tab_vm();
	if (proc->ocp < 64)
		return (0);
	while (i < proc->paramnb)
	{
		if (proc->paramtype[i] == 0 || (proc->paramtype[i]
				& optab[(int)proc->type].paramtype[i]) != proc->paramtype[i])
			return (0);
		i++;
	}
	return (1);
}

void	fill_son(t_proc *son, t_proc *proc, t_vm *vm, int pc)
{
	t_opmodvm	*optab;
	int			i;

	i = 0;
	optab = get_op_tab_vm();
	while (i < REG_NUMBER)
	{
		son->regs[i] = proc->regs[i];
		i++;
	}
	while (pc < 0)
		pc += MEM_SIZE;
	son->pc = pc % MEM_SIZE;
	son->id = proc->id;
	if (vm->vis)
		set_cursor_color(vm->win->matrix, son->pc);
	son->carry = proc->carry;
	son->lastlive = proc->lastlive;
	son->cycles_exec = vm->cycle;
}

int		update_proclist(t_proc *proc, t_proctab *proclist)
{
	while (proclist->next)
		proclist = proclist->next;
	if (proclist->proclen == PROC_NB)
	{
		if (!(proclist->next = init_proctab(proclist)))
			return (0);
		proclist = proclist->next;
		proclist->i = proclist->prev->i + 1;
	}
	proclist->proc[proclist->proclen] = proc;
	proclist->proclen++;
	return (1);
}

int		ft_lfork(t_proc *proc, t_vm *vm)
{
	t_proc		*son;
	int			i;
	int			pc;

	vm->procnb++;
	i = 0;
	if (!(son = init_proc()))
		return (0);
	if (!(update_proclist(son, vm->proclist)))
		return (0);
	pc = proc->pc + proc->paramval[0];
	verbose_ope(proc->paramval[0], pc, proc, vm);
	fill_son(son, proc, vm, pc);
	return (1);
}

int		ft_aff(t_proc *proc, t_vm *vm)
{
	char	c;

	if (vm->aff)
	{
		c = proc->regs[proc->paramval[0]] % 256;
		if (!check_ocp(proc))
			return (0);
		write(1, "\nAff: ", 6);
		write(1, &c, 1);
	}
	return (1);
}
