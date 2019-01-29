/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   verbose_ope1.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/22 15:26:11 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/18 20:55:48 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op_vm.h"

void	verb_live(int val1, int val2, t_proc *proc)
{
	val1 = proc->paramval[0];
	val2 = val2 + 0;
	ft_printf("live %d", val1);
}

void	verb_ld(int val1, int val2, t_proc *proc)
{
	val2 = proc->paramval[1] + 1;
	ft_printf("ld %d r%d", val1, val2);
}

/*
** The verbose for ld is incorect because it mimes zaz's verbose: if the second
** parameter is a register it prints the number of the register (without the r)
** instead of what it contains
*/

void	verb_st(int val1, int val2, t_proc *proc)
{
	val1 = proc->paramval[0] + 1;
	val2 = proc->paramtype[1] == T_REG ? proc->paramval[1] + 1
		: proc->paramval[1];
	ft_printf("st r%d %d", val1, val2);
}

void	verb_add(int val1, int val2, t_proc *proc)
{
	ft_printf("add r%d r%d r%d", val1, val2, proc->paramval[2] + 1);
}

void	verb_sub(int val1, int val2, t_proc *proc)
{
	ft_printf("sub r%d r%d r%d", val1, val2, proc->paramval[2] + 1);
}
