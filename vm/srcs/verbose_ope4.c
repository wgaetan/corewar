/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   verbose_ope1.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/22 14:26:03 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/22 17:15:15 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op_vm.h"

void	verb_lfork(int val1, int val2, t_proc *proc)
{
	proc->paramval[1] = 0;
	ft_printf("lfork %d (%d)", val1, val2);
}

void	verb_aff(int val1, int val2, t_proc *proc)
{
	val1 = proc->paramval[0] + 1;
	val2 = val2 + 0;
	ft_printf("aff r%d", proc->paramval[0] + 1);
}
