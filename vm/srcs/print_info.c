/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_info.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/18 20:08:57 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/23 15:26:13 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op_vm.h"

void	print_dump(t_vm *vm)
{
	int				i;

	i = 0;
	ft_printf("\n0x%0.4x : ", i);
	while (i < MEM_SIZE)
	{
		ft_printf("%.2x ", vm->mem[i] & 0xff);
		i++;
		if (i < MEM_SIZE && !(i % 64))
			ft_printf("\n%#0.4x : ", i);
	}
	ft_printf("\n");
}

void	print_result(t_vm *vm)
{
	int				i;
	t_champ			*start;
	t_champ			*winner;

	i = 0;
	winner = vm->champ;
	start = winner;
	while (i < vm->champ_nb && vm->champ)
	{
		if (vm->last_whisper == vm->champ->id)
			winner = vm->champ;
		vm->champ = vm->champ->next;
		i++;
	}
	if (vm->vis == 0)
		ft_printf("\nContestant %d, \"%s\", has won !\n", (winner->id * -1),
				winner->head->prog_name);
	else
		write_info_result(vm, winner);
	vm->champ = start;
}

int		print_man(t_vm *vm)
{
	ft_printf("Usage: ./corewar [-d N -b -v N -a] [-n N] <champion1.cor> ...");
	ft_printf("\n\t-b\t: Beautiful Visual Mode");
	ft_printf("\n\t-d N\t: Dumps memory after N cycles then exits");
	ft_printf("\n\t-v N\t: Verbosity levels, can be added together");
	ft_printf("\n\t\t 0 : Same as no -v");
	ft_printf("\n\t\t 1 : Show lives");
	ft_printf("\n\t\t 2 : Show cycles and cycle to die decrementation");
	ft_printf("\n\t\t 4 : Show operations");
	ft_printf("\n\t\t 8 : Show death of procs");
	ft_printf("\n\t\t 16 : Show PC movement (except for succesful jumps)");
	ft_printf("\n\t-n [1-%d] <champion1.cor> -n [1-%d] <champion2.cor> ...",
			MAX_PLAYERS, MAX_PLAYERS);
	ft_printf(" : manualy determine players IDs");
	ft_printf("\n\t-a\t: Prints output from \"aff\" operations\n");
	return (free_all(vm));
}

int		introduce_contestants(t_vm *vm)
{
	t_champ			*champ;
	int				i;

	i = -1;
	if (vm->vis)
		return (0);
	ft_printf("Introducing contestants...");
	while (-i <= vm->champ_nb && (champ = vm->champ))
	{
		while (champ)
		{
			if (i == champ->id)
			{
				ft_printf("\n* Player %d, weighing %d bytes, \"%s\" (\"%s\") !",
					(champ->id * -1), champ->head->prog_size,
					champ->head->prog_name, champ->head->comment);
				break ;
			}
			champ = champ->next;
		}
		i--;
	}
	return (0);
}
