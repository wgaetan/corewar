/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   proc_tools.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/30 18:07:10 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/25 19:09:07 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op_vm.h"

t_proc			*init_proc(void)
{
	t_proc		*proc;

	if (!(proc = malloc(sizeof(t_proc))))
		return (NULL);
	ft_memset(proc->regs, 0, REG_NUMBER);
	proc->type = 0;
	proc->paramnb = 0;
	proc->ocp = 0;
	ft_memset(proc->paramtype, 0, 4);
	ft_memset(proc->paramval, 0, 4);
	proc->cycles_exec = 0;
	proc->pc = 0;
	proc->lives = 0;
	proc->carry = 1;
	proc->size = 0;
	proc->id = 0;
	proc->lastlive = 0;
	return (proc);
}

int				fill_proc(t_proc *proc, t_vm *vm, int id, int mempos)
{
	int			i;
	t_opmodvm	*optab;

	i = 0;
	optab = get_op_tab_vm();
	while (i < REG_NUMBER)
		proc->regs[i++] = 0;
	proc->regs[0] = id;
	proc->id = id;
	proc->pc = mempos;
	if (vm->vis)
		set_cursor_color(vm->win->matrix, mempos % MEM_SIZE);
	if ((proc->type = vm->mem[mempos]) < 1 || proc->type > 16)
	{
		proc->cycles_exec = vm->cycle + 1;
		proc->size = 1;
		return (0);
	}
	proc->ocp = optab[proc->type].ocp ? vm->mem[(proc->pc + 1) % MEM_SIZE] : 0;
	proc->cycles_exec = vm->cycle + optab[proc->type].cycles;
	proc->paramnb = optab[proc->type].paramnb;
	proc->size = calc_size(proc);
	proc->carry = 0;
	fill_paramval(proc, vm);
	return (1);
}

int				refill_proc(t_proc *proc, t_vm *vm)
{
	t_opmodvm	*optab;

	optab = get_op_tab_vm();
	proc->ocp = optab[proc->type].ocp ? vm->mem[(proc->pc + 1) % MEM_SIZE]
		: 0;
	proc->paramnb = optab[proc->type].paramnb;
	if (!proc->ocp)
	{
		proc->size = optab[proc->type].dirsize + 1;
		proc->paramtype[0] = T_DIR;
	}
	else
		proc->size = calc_size(proc);
	fill_paramval(proc, vm);
	return (1);
}

void			free_proc(t_proc **proc, t_vm *vm)
{
	if (vm->vis)
		unset_cursor_color(vm->win->matrix, (*proc)->pc % MEM_SIZE);
	free(*proc);
	*proc = NULL;
	vm->procnb--;
}

int				fill_paramval(t_proc *proc, t_vm *vm)
{
	int			i;
	int			j;
	int			k;
	static int	opc[4] = {0, 1, 0, IND_SIZE};
	t_opmodvm	*optab;

	i = 0;
	optab = get_op_tab_vm();
	j = proc->ocp ? 1 : 0;
	opc[2] = optab[proc->type].dirsize;
	while (i < proc->paramnb)
	{
		proc->paramval[i] = 0;
		if (proc->paramtype[i] == T_REG)
			proc->paramval[i] = read_mem(vm->mem, proc->pc + j + 1, 1) - 1;
		else if (proc->paramtype[i] == T_DIR || proc->paramtype[i] == T_IND)
		{
			k = proc->paramtype[i] == T_DIR ? 2 : 3;
			proc->paramval[i] = manage_nega(proc->paramtype[i], opc[k],
					read_mem(vm->mem, proc->pc + j + opc[k], opc[k]));
		}
		j += opc[(proc->ocp >> (6 - i * 2)) & 0x3];
		i++;
	}
	return (0);
}
