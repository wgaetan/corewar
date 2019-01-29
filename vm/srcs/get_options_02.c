/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_options_02.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bodibon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/19 17:14:43 by bodibon      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/24 13:32:46 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op_vm.h"

void		ft_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}

int			get_args(int ac, char *av[], t_vm *vm)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!vm->champ_nb && !ft_strcmp("-d", av[i]) && i + 1 < ac)
			vm->dump = ft_atoi(av[++i]);
		else if (!vm->champ_nb && !ft_strcmp("-v", av[i]) && i + 1 < ac)
			vm->verbose = ft_atoi(av[++i]);
		else if (!vm->champ_nb && !ft_strcmp("-a", av[i]))
			vm->aff = 1;
		else if (!vm->champ_nb && !ft_strcmp("-b", av[i]))
			vm->vis = 1;
		else if (!ft_strcmp("-n", av[i]) && i + 1 < ac)
			get_player_id(vm, vm->champ_nb, ft_atoi(av[++i]));
		else if (ft_strcmp(av[i], "-d") && ft_strcmp(av[i], "-v"))
		{
			if (vm->champ_nb < MAX_PLAYERS)
				vm->players_file[vm->champ_nb++] = av[i];
			else
				ft_error("Too many champions\n");
		}
		i++;
	}
	return (check_players(vm));
}
