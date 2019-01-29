/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_options_01.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bodibon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/19 17:16:50 by bodibon      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/24 15:10:10 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op_vm.h"

int			check_player_id(int id, int *players_id)
{
	int		i;

	if (id > MAX_PLAYERS || id < 1)
		return (0);
	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (id == players_id[i])
			return (0);
		i++;
	}
	return (1);
}

void		get_player_id(t_vm *vm, int i, int id)
{
	char	c;
	int		j;

	c = MAX_PLAYERS + '0';
	vm->n = 1;
	j = 1;
	if (!check_player_id(id, vm->players_id))
	{
		write(2, "Champion id must be between 1 and ", 34);
		write(2, &c, 1);
		write(2, " (no duplicates)\n", 17);
		exit(EXIT_FAILURE);
	}
	else
		vm->players_id[i] = id;
	while (j <= MAX_PLAYERS)
	{
		if (id == j)
			vm->available_id ^= (1 << (j - 1));
		j++;
	}
}

void		fill_players_id(int *players_id, char available_id, int champ_nb)
{
	int		i;
	int		id;

	i = 0;
	while (i < champ_nb)
	{
		id = 1;
		while (id <= champ_nb)
		{
			if (players_id[i])
				break ;
			else if (available_id & (1 << (id - 1)))
			{
				players_id[i] = id;
				available_id ^= 1 << (id - 1);
			}
			id++;
		}
		i++;
	}
}

void		sort_players(int *players_id, char **players_file)
{
	int		i;
	int		j;
	char	*tmp;
	int		tmp2;

	i = 0;
	while (i < MAX_PLAYERS - 1)
	{
		j = 0;
		while (j < MAX_PLAYERS - (i + 1))
		{
			if ((players_file[j + 1] && players_id[j] > players_id[j + 1])
					|| players_file[j] == NULL)
			{
				tmp = players_file[j];
				players_file[j] = players_file[j + 1];
				players_file[j + 1] = tmp;
				tmp2 = players_id[j];
				players_id[j] = players_id[j + 1];
				players_id[j + 1] = tmp2;
			}
			j++;
		}
		i++;
	}
}

int			check_players(t_vm *vm)
{
	int		i;

	i = 0;
	if (!vm->champ_nb)
	{
		print_man(vm);
		ft_error("");
	}
	while (i < vm->champ_nb)
	{
		if (vm->players_id[i] > vm->champ_nb)
		{
			n_error(vm->champ_nb);
			ft_error("");
		}
		i++;
	}
	fill_players_id(vm->players_id, vm->available_id, vm->champ_nb);
	if (vm->n == 0)
		return (0);
	sort_players(vm->players_id, vm->players_file);
	return (0);
}
