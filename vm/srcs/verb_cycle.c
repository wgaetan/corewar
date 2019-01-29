/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   verb_cycle.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/22 17:25:13 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/22 17:26:02 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op_vm.h"

static void	nothin(int cycle, int ctd)
{
	return ((void)(cycle + ctd));
}

static void	it_is_cycle(int cycle, int ctd)
{
	ctd = ctd + 0;
	ft_printf("\nIt is now cycle %d", cycle);
}

static void	ctd_is_now(int cycle, int ctd)
{
	cycle = cycle + 0;
	ft_printf("\nCycle to die is now %d", ctd);
}

void		verb_cycle(t_vm *vm, int mode)
{
	static void	(*f[3])(int cycle, int ctd) = {nothin, it_is_cycle, ctd_is_now};

	f[mode * ((vm->verbose & 2) / 2)](vm->cycle, vm->ctd);
}
