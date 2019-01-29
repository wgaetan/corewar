/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   visualizer_04.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bodibon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/15 13:59:40 by bodibon      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/24 14:31:27 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op_vm.h"

typedef WINDOW	t_window;

void	write_info_result(t_vm *vm, t_champ *winner)
{
	t_window	*info;
	int			player_id;

	info = vm->win->info;
	player_id = winner->id;
	wattron(info, COLOR_PAIR(16));
	mvwprintw(info, 29, 2, "The winner is : ");
	wattroff(info, COLOR_PAIR(16));
	wattron(info, COLOR_PAIR(3 + (-player_id - 1)));
	mvwprintw(info, 29, 18, "%s", winner->head->prog_name);
	wattroff(info, COLOR_PAIR(3 + (-player_id - 1)));
	wattron(info, COLOR_PAIR(16));
	mvwprintw(info, 31, 2, "Press <SPACE> KEY to exit");
	wattroff(info, COLOR_PAIR(16));
	wrefresh(info);
}

void	change_speed(t_vm *vm, char ch)
{
	short	cps;

	cps = vm->win->cycles_per_sec;
	if (ch == 'q' || ch == 'Q')
		cps = (cps > 10) ? cps - 10 : 1;
	else if (ch == 'w' || ch == 'W')
		cps = (cps > 1) ? cps - 1 : 1;
	else if (ch == 'e' || ch == 'E')
		cps = (cps < 1000) ? cps + 1 : 1000;
	else if (ch == 'r' || ch == 'R')
		cps = (cps <= 990) ? cps + 10 : 1000;
	vm->win->cycles_per_sec = cps;
}

void	update_visu(t_vm *vm, char ch)
{
	if (ft_strchr("qQwWeErR", ch))
		change_speed(vm, ch);
	write_info_cycle(vm);
	if (ch == ' ')
	{
		write_info_par(vm);
		while ((ch = getch()) != ' ')
		{
			if (ft_strchr("qQwWeErR", ch))
			{
				change_speed(vm, ch);
				write_info_speed(vm);
			}
		}
		write_info_par(vm);
	}
	usleep(1000000 / vm->win->cycles_per_sec);
}

void	end_ncurses_mod(t_vm *vm)
{
	if (vm->vis == 0 || vm->champ_nb == 0)
		return ;
	nodelay(stdscr, FALSE);
	while ((getch()) != ' ')
		;
	endwin();
	free(vm->win);
}
