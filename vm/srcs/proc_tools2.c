/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   proc_tools2.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/19 18:57:47 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/25 12:29:36 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op_vm.h"

int				exec_proc(t_proc *proc, t_vm *vm, int procnb)
{
	size_t		i;

	i = 0;
	if (!proc->size)
		refill_proc(proc, vm);
	launch_proc(proc, vm, procnb);
	if ((vm->verbose & 16) == 16 && (proc->type != 9 || !proc->carry)
			&& proc->size != 1)
	{
		ft_printf("\nADV %d (0x%.4x -> 0x%.4x) ", proc->size, proc->pc,
				proc->pc + proc->size);
		while (i < proc->size)
		{
			ft_printf("%.2x ", vm->mem[(proc->pc + i) % MEM_SIZE]);
			i++;
		}
	}
	return (1);
}

int				find_next_exec_cycle(t_proc *proc, t_vm *vm)
{
	t_opmodvm	*optab;

	optab = get_op_tab_vm();
	if (vm->vis)
		unset_cursor_color(vm->win->matrix, proc->pc % MEM_SIZE);
	if (proc->size < 1000)
		proc->pc = (proc->pc + proc->size) % MEM_SIZE;
	if (vm->vis)
		set_cursor_color(vm->win->matrix, proc->pc);
	proc->type = vm->mem[proc->pc];
	if (proc->type < 1 || proc->type > 16)
	{
		proc->cycles_exec = vm->cycle;
		proc->size = 1;
		return (0);
	}
	proc->size = 0;
	proc->cycles_exec = vm->cycle + optab[proc->type].cycles - 1;
	return (1);
}

static int		ctd_vs_lives(t_proc *proc, t_vm *vm)
{
	return (vm->cycle - proc->lastlive >= vm->ctd);
}

int				check_proc_lives(t_vm *vm)
{
	t_proctab	*start;
	int			i;
	int			ret;

	ret = 1;
	start = vm->proclist;
	while (start->next)
		start = start->next;
	while (start)
	{
		i = start->proclen;
		while (--i >= 0)
		{
			if (start->proc[i] && ctd_vs_lives(start->proc[i], vm))
			{
				verb_proc_lives(vm, start, i);
				free_proc(&start->proc[i], vm);
			}
		}
		start = start->prev;
	}
	if (vm->lives >= NBR_LIVE)
		ret = 0;
	return (ret);
}

int				check_proc_to_exec(t_vm *vm)
{
	int			i;
	int			ret;
	t_proctab	*cycles;

	ret = 0;
	cycles = vm->proclist;
	while (cycles->next)
		cycles = cycles->next;
	while (cycles && (i = cycles->proclen - 1) >= 0)
	{
		while (i >= 0)
		{
			if (cycles->proc[i] && cycles->proc[i]->cycles_exec
					== vm->cycle - 1)
				find_next_exec_cycle(cycles->proc[i], vm);
			if (cycles->proc[i] && cycles->proc[i]->cycles_exec == vm->cycle)
			{
				exec_proc(cycles->proc[i], vm, cycles->i * PROC_NB + i + 1);
				ret = 1;
			}
			i--;
		}
		cycles = cycles->prev;
	}
	return (ret);
}
