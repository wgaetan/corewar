/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   verbose_ope1.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/22 14:26:03 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/20 19:46:05 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op_vm.h"

void	verb_sti(int val1, int val2, t_proc *proc)
{
	int		j;

	j = val1 + val2;
	ft_printf("sti r%d %d %d", proc->paramval[0] + 1, val1, val2);
	ft_printf("\n       | -> store to %d + %d = %d (with pc and mod %d)",
			val1, val2, j, proc->pc + j % IDX_MOD);
}

void	verb_fork(int val1, int val2, t_proc *proc)
{
	proc->paramval[1] = 0;
	ft_printf("fork %d (%d)", val1, val2);
}

void	verb_lld(int val1, int val2, t_proc *proc)
{
	val2 = proc->paramval[1] + 1;
	ft_printf("lld %d r%d", val1, val2);
}

void	verb_lldi(int val1, int val2, t_proc *proc)
{
	ft_printf("ldi %d %d r%d", val1, val2, proc->paramval[2] + 1);
	ft_printf("\n       | -> load from %d + %d = %d (with pc and mod %d)",
			val1, val2, val1 + val2, proc->pc + (val1 + val2));
}
