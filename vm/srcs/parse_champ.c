/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_champ.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/15 12:58:42 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/25 12:29:39 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op_vm.h"

t_header	*init_head(void)
{
	t_header	*head;

	if (!(head = malloc(sizeof(t_header))))
		return (NULL);
	ft_memset(head->prog_name, '\0', PROG_NAME_LENGTH + 1);
	ft_memset(head->comment, '\0', COMMENT_LENGTH + 1);
	head->magic = 0;
	head->prog_size = 0;
	return (head);
}

static t_vm	*init_vm(void)
{
	t_vm		*vm;

	if (!(vm = ft_memalloc(sizeof(t_vm))))
		return (NULL);
	vm->available_id = 0x0f;
	vm->ctd = CYCLE_TO_DIE;
	vm->dump = -1;
	return (vm);
}

int			free_all(t_vm *vm)
{
	t_proctab	*tmp;
	t_champ		*tmpchamp;

	while (vm->proclist)
	{
		tmp = vm->proclist->next;
		free(vm->proclist);
		vm->proclist = tmp;
	}
	while (vm->champ)
	{
		if (vm->champ->head)
			free(vm->champ->head);
		tmpchamp = vm->champ->next;
		free(vm->champ);
		vm->champ = tmpchamp;
	}
	end_ncurses_mod(vm);
	free(vm);
	return (1);
}

int			main(int ac, char **av)
{
	t_vm		*vm;

	vm = init_vm();
	if (ac == 1)
		return (print_man(vm));
	if (get_args(ac, av, vm))
		return (free_all(vm));
	if (vm->vis)
		init_visualizer(vm);
	if (get_champs(vm))
		return (free_all(vm));
	if (introduce_contestants(vm))
		return (free_all(vm));
	if (launch_vm(vm) == vm->dump && vm->vis == 0 && vm->dump >= 0)
		print_dump(vm);
	else
		print_result(vm);
	free_all(vm);
	return (0);
}
