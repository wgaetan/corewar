/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   visualizer_03.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bodibon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/14 13:46:14 by bodibon      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/23 16:49:05 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op_vm.h"

int		write_info_players(t_vm *vm)
{
	WINDOW		*info;
	t_champ		*champ;
	int			row;

	info = vm->win->info;
	champ = vm->champ;
	row = 9;
	while (champ)
	{
		mvwprintw(info, row, 2, "Player %d : ", champ->id);
		wattroff(info, COLOR_PAIR(16));
		wattron(info, COLOR_PAIR(3 + (-champ->id - 1)));
		mvwprintw(info, row, 15, "%s", champ->head->prog_name);
		wattroff(info, COLOR_PAIR(3 + (-champ->id - 1)));
		wattron(info, COLOR_PAIR(16));
		mvwprintw(info, ++row, 2, "Last live : % 22d", champ->lastlive);
		mvwprintw(info, ++row, 2, "Lives in current period : % 8d",
				champ->lives);
		champ = champ->next;
		row = row + 2;
	}
	return (row);
}

void	write_info_status(WINDOW *info)
{
	if ((mvwinch(info, 1, 5) & A_CHARTEXT) != 'P')
	{
		mvwdelch(info, 1, 14);
		mvwprintw(info, 1, 2, "** PAUSED **");
	}
	else
		mvwprintw(info, 1, 2, "** RUNNING **");
}

void	write_info_speed(t_vm *vm)
{
	WINDOW	*info;

	info = vm->win->info;
	wattron(info, COLOR_PAIR(16));
	mvwprintw(info, 3, 2, "Cycles/second limit : %-4d",
			vm->win->cycles_per_sec);
	wattroff(info, COLOR_PAIR(16));
	wrefresh(info);
}

void	write_info_par(t_vm *vm)
{
	WINDOW	*info;
	int		row;

	info = vm->win->info;
	wattron(info, COLOR_PAIR(16));
	write_info_status(info);
	mvwprintw(info, 3, 2, "Cycles/second limit : %-4d",
			vm->win->cycles_per_sec);
	mvwprintw(info, 5, 2, "Cycle : %d", vm->cycle);
	mvwprintw(info, 7, 2, "Processes : %-6d", vm->procnb);
	row = write_info_players(vm);
	mvwprintw(info, row, 2, "CYCLE_TO_DIE : %-4d", vm->ctd);
	row = row + 2;
	mvwprintw(info, row, 2, "CYCLE_DELTA : %d", CYCLE_DELTA);
	row = row + 2;
	mvwprintw(info, row, 2, "NBR_LIVE : %d", NBR_LIVE);
	row = row + 2;
	mvwprintw(info, row, 2, "MAX_CHECKS : %d", MAX_CHECKS);
	wattroff(info, COLOR_PAIR(16));
	wrefresh(info);
}

void	write_info_cycle(t_vm *vm)
{
	WINDOW	*info;
	int		row;

	info = vm->win->info;
	wattron(info, COLOR_PAIR(16));
	mvwprintw(info, 3, 2, "Cycles/second limit : %-4d",
			vm->win->cycles_per_sec);
	mvwprintw(info, 5, 2, "Cycle : %d", vm->cycle);
	mvwprintw(info, 7, 2, "Processes : %-6d", vm->procnb);
	row = write_info_players(vm);
	mvwprintw(info, row, 2, "CYCLE_TO_DIE : %-4-4-4-4d", vm->ctd);
	row = row + 2;
	mvwprintw(info, row, 2, "CYCLE_DELTA : %d", CYCLE_DELTA);
	row = row + 2;
	mvwprintw(info, row, 2, "NBR_LIVE : %d", NBR_LIVE);
	row = row + 2;
	mvwprintw(info, row, 2, "MAX_CHECKS : %d", MAX_CHECKS);
	wattroff(info, COLOR_PAIR(16));
	wrefresh(info);
}
