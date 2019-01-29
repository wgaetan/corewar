/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   launch_champ.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/20 17:56:35 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/23 16:49:13 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op_vm.h"

t_proctab		*init_proctab(t_proctab *prev)
{
	t_proctab	*proctab;
	int			i;

	i = 0;
	if (!(proctab = malloc(sizeof(t_proctab))))
		return (NULL);
	while (i < PROC_NB)
		proctab->proc[i++] = NULL;
	proctab->proclen = 0;
	proctab->i = 0;
	proctab->next = NULL;
	proctab->prev = prev;
	return (proctab);
}

void			reinit_champlives(t_vm *vm)
{
	t_champ		*champ;

	champ = vm->champ;
	while (champ)
	{
		champ->lives = 0;
		champ = champ->next;
	}
	vm->check = 0;
	vm->ctd -= CYCLE_DELTA;
	verb_cycle(vm, 2);
}

static int		regular_cycle(t_vm *vm, int j)
{
	if (vm->cycle >= (vm->ctd + j))
	{
		j = vm->cycle;
		if (!(check_proc_lives(vm)) || vm->check == MAX_CHECKS - 1)
			reinit_champlives(vm);
		else
			vm->check++;
		if (vm->procnb == 0)
			return (vm->cycle);
		vm->lives = 0;
	}
	return (j);
}

static void		first_cycle(t_vm *vm, int i, int j)
{
	t_champ		*champs;

	if (!vm->champ_nb || !(vm->proclist = init_proctab(NULL)))
		return ;
	vm->last_whisper = -vm->champ_nb;
	while (-j <= vm->champ_nb)
	{
		champs = vm->champ;
		while (champs)
		{
			if (champs->id == j)
			{
				if (!(vm->proclist->proc[i] = init_proc()))
					return ;
				vm->proclist->proclen++;
				vm->procnb++;
				fill_proc(vm->proclist->proc[i++], vm, champs->id,
						champs->mempos);
				break ;
			}
			champs = champs->next;
		}
		j--;
	}
}

int				launch_vm(t_vm *vm)
{
	int			j;
	char		ch;

	j = 0;
	first_cycle(vm, 0, -1);
	start_visualizer(vm);
	vm->cycle++;
	if (!vm->dump)
		return (0);
	while (vm->procnb > 0 && (ch = getch()))
	{
		if (vm->vis != 0)
			update_visu(vm, ch);
		verb_cycle(vm, 1);
		check_proc_to_exec(vm);
		j = regular_cycle(vm, j);
		if (vm->cycle == vm->dump)
			return (vm->cycle);
		vm->cycle++;
	}
	return (vm->cycle);
}
