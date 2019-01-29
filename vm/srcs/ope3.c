/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ope3.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/19 15:54:12 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/23 15:17:08 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op_vm.h"

int		ft_sti(t_proc *proc, t_vm *vm)
{
	int			val1;
	int			val2;
	int			j;

	val1 = 0;
	val2 = 0;
	if (proc->paramtype[1] == T_DIR)
		val1 = proc->paramval[1];
	else if (proc->paramtype[1] == T_IND)
		val1 = manage_nega(T_DIR, REG_SIZE, read_mem(vm->mem, proc->pc
					+ (proc->paramval[1] % IDX_MOD + REG_SIZE - 1), REG_SIZE));
	else if (proc->paramtype[1] == T_REG)
		val1 = proc->regs[proc->paramval[1]];
	if (proc->paramtype[2] == T_DIR)
		val2 = proc->paramval[2];
	else if (proc->paramtype[2] == T_REG)
		val2 = proc->regs[proc->paramval[2]];
	j = val1 + val2;
	verbose_ope(val1, val2, proc, vm);
	write_mem(vm->mem, proc->pc + j % IDX_MOD + REG_SIZE - 1, REG_SIZE,
			proc->regs[proc->paramval[0]]);
	if (vm->vis)
		write_matrix2(vm->win->matrix, proc->pc + j % IDX_MOD + REG_SIZE - 1,
				proc->regs[proc->paramval[0]], proc->id);
	return (1);
}

int		ft_fork(t_proc *proc, t_vm *vm)
{
	t_proc		*son;
	int			pc;

	vm->procnb++;
	pc = proc->pc + proc->paramval[0] % IDX_MOD;
	if (!(son = init_proc()))
		return (0);
	if (!(update_proclist(son, vm->proclist)))
		return (0);
	verbose_ope(proc->paramval[0], pc, proc, vm);
	fill_son(son, proc, vm, pc);
	return (1);
}

int		ft_lld(t_proc *proc, t_vm *vm)
{
	int			val1;

	val1 = 0;
	if (proc->paramtype[0] == T_IND)
		val1 = manage_nega(T_DIR, 4, read_mem(vm->mem, proc->pc
					+ proc->paramval[0] + REG_SIZE - 1, REG_SIZE));
	else if (proc->paramtype[0] == T_DIR)
		val1 = proc->paramval[0];
	proc->regs[proc->paramval[1]] = val1;
	verbose_ope(val1, proc->paramval[1] + 1, proc, vm);
	proc->carry = !proc->regs[proc->paramval[1]] ? 1 : 0;
	return (0);
}

int		ft_lldi(t_proc *proc, t_vm *vm)
{
	int			val1;
	int			val2;

	val1 = 0;
	val2 = 0;
	if (proc->paramtype[0] == T_DIR)
		val1 = proc->paramval[0];
	else if (proc->paramtype[0] == T_IND)
		val1 = read_mem(vm->mem, proc->pc + proc->paramval[0] + REG_SIZE - 1,
				IND_SIZE);
	else if (proc->paramtype[0] == T_REG)
		val1 = proc->regs[proc->paramval[0]];
	if (proc->paramtype[1] == T_DIR)
		val2 = proc->paramval[1];
	else if (proc->paramtype[1] == T_REG)
		val2 = proc->regs[proc->paramval[1]];
	verbose_ope(val1, val2, proc, vm);
	proc->regs[proc->paramval[2]] = manage_nega(T_DIR, REG_SIZE,
			read_mem(vm->mem, proc->pc + val1 + val2 + REG_SIZE - 1, REG_SIZE));
	return (1);
}
