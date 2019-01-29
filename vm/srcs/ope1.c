/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ope1.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/25 11:42:00 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/23 15:16:58 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op_vm.h"

int		ft_live(t_proc *proc, t_vm *vm)
{
	t_champ		*tmp;

	tmp = vm->champ;
	verbose_ope(0, 0, proc, vm);
	proc->lastlive = vm->cycle;
	vm->lives++;
	while (tmp)
	{
		if (tmp->id == proc->paramval[0])
		{
			tmp->lastlive = vm->cycle;
			tmp->lives++;
			vm->last_whisper = tmp->id;
			if ((vm->verbose & 1) == 1 && tmp->head)
				ft_printf("\nPlayer %d (%s) is said to be alive", tmp->id * -1,
					tmp->head->prog_name);
		}
		tmp = tmp->next;
	}
	return (1);
}

int		ft_ld(t_proc *proc, t_vm *vm)
{
	int		val1;

	val1 = 0;
	if (proc->paramtype[0] == T_IND)
		val1 = manage_nega(T_DIR, 4, read_mem(vm->mem, proc->pc +
					(proc->paramval[0] + REG_SIZE - 1) % IDX_MOD, REG_SIZE));
	else if (proc->paramtype[0] == T_DIR)
		val1 = proc->paramval[0];
	proc->regs[proc->paramval[1]] = val1;
	verbose_ope(val1, 0, proc, vm);
	proc->carry = !proc->regs[proc->paramval[1]] ? 1 : 0;
	return (0);
}

int		ft_st(t_proc *proc, t_vm *vm)
{
	if (proc->paramtype[1] == T_REG)
		proc->regs[proc->paramval[1]] = proc->regs[proc->paramval[0]];
	else if (proc->paramtype[1] == T_IND)
	{
		write_mem(vm->mem, proc->pc + (proc->paramval[1] % IDX_MOD) + REG_SIZE
				- 1, REG_SIZE, proc->regs[proc->paramval[0]]);
		if (vm->vis)
			write_matrix2(vm->win->matrix,
					proc->pc + (proc->paramval[1] % IDX_MOD) + REG_SIZE - 1,
					proc->regs[proc->paramval[0]], proc->id);
	}
	verbose_ope(0, 0, proc, vm);
	return (1);
}

int		ft_add(t_proc *proc, t_vm *vm)
{
	verbose_ope(proc->paramval[0] + 1, proc->paramval[1] + 1, proc, vm);
	proc->regs[proc->paramval[2]] = proc->regs[proc->paramval[0]]
		+ proc->regs[proc->paramval[1]];
	proc->carry = !proc->regs[proc->paramval[2]] ? 1 : 0;
	return (0);
}

int		ft_sub(t_proc *proc, t_vm *vm)
{
	verbose_ope(proc->paramval[0] + 1, proc->paramval[1] + 1, proc, vm);
	proc->regs[proc->paramval[2]] = proc->regs[proc->paramval[0]]
		- proc->regs[proc->paramval[1]];
	proc->carry = !proc->regs[proc->paramval[2]] ? 1 : 0;
	return (0);
}
