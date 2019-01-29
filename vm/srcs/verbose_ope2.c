/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   verbose_ope1.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/22 15:26:11 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/22 17:16:55 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op_vm.h"

void	verb_and(int val1, int val2, t_proc *proc)
{
	ft_printf("and %d %d r%d", val1, val2, proc->paramval[2] + 1);
}

void	verb_or(int val1, int val2, t_proc *proc)
{
	ft_printf("or %d %d r%d", val1, val2, proc->paramval[2] + 1);
}

void	verb_xor(int val1, int val2, t_proc *proc)
{
	ft_printf("xor %d %d r%d", val1, val2, proc->paramval[2] + 1);
}

void	verb_zjmp(int val1, int val2, t_proc *proc)
{
	if (val2)
		ft_printf("zjmp %d OK", proc->paramval[0]);
	else
		ft_printf("zjmp %d FAILED", val1);
}

void	verb_ldi(int val1, int val2, t_proc *proc)
{
	ft_printf("ldi %d %d r%d", val1, val2, proc->paramval[2] + 1);
	ft_printf("\n       | -> load from %d + %d = %d (with pc and mod %d)",
			val1, val2, val1 + val2, proc->pc + (val1 + val2) % IDX_MOD);
}
