/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   verbose.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/18 20:38:00 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/23 15:43:10 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op_vm.h"

void	verb_procnb(t_vm *vm, int procnb, size_t procsize)
{
	if (procsize != 1 && (vm->verbose & 4) == 4)
		ft_printf("\nP%*d | ", ft_bdigitlen(10, procnb) < 5 ? 5
				: ft_bdigitlen(10, procnb) + 1, procnb);
}

void	nothing(int val1, int val2, t_proc *proc)
{
	return ((void)(proc->type + val1 + val2));
}

void	verb_proc_lives(t_vm *vm, t_proctab *start, int i)
{
	if ((vm->verbose & 8) == 8)
		ft_printf("\nProcess %d hasn't lived for %d cycles (CTD %d)",
			i + start->i * PROC_NB + 1, vm->cycle - start->proc[i]->lastlive,
			vm->ctd);
}

void	verbose_ope(int val1, int val2, t_proc *proc, t_vm *vm)
{
	static void	(*f[17])(int val1, int val2, t_proc *proc) = {nothing,
		verb_live, verb_ld, verb_st, verb_add, verb_sub, verb_and, verb_or,
		verb_xor, verb_zjmp, verb_ldi, verb_sti, verb_fork, verb_lld,
		verb_lldi, verb_lfork, verb_aff};

	f[proc->type * ((vm->verbose & 4) >> 2)](val1, val2, proc);
}
