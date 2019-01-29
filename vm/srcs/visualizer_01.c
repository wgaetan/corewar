/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   visualizer_01.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bodibon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/09 11:41:31 by bodibon      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/23 16:49:06 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op_vm.h"

t_win	*init_windows(void)
{
	t_win	*windows;

	if (!(windows = ft_memalloc(sizeof(t_win))))
		return (NULL);
	windows->cycles_per_sec = 50;
	if (!(windows->wrap = newwin(WRAP_H, WRAP_W, WRAP_SY, WRAP_SX)))
		return (NULL);
	wbkgd(windows->wrap, COLOR_PAIR(1));
	wrefresh(windows->wrap);
	if (!(windows->matrix = newwin(MATRIX_H, MATRIX_W, MATRIX_SY, MATRIX_SX)))
		return (NULL);
	wbkgd(windows->matrix, COLOR_PAIR(2));
	wrefresh(windows->matrix);
	if (!(windows->info = newwin(INFO_H, INFO_W, INFO_SY, INFO_SX)))
		return (NULL);
	wbkgd(windows->info, COLOR_PAIR(2));
	wrefresh(windows->info);
	return (windows);
}

void	init_colors(void)
{
	init_color(COLOR_CYAN, 242, 242, 242);
	init_pair(1, COLOR_BLACK, COLOR_CYAN);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_RED, COLOR_BLACK);
	init_pair(6, COLOR_YELLOW, COLOR_BLACK);
	init_pair(7, COLOR_BLACK, COLOR_GREEN);
	init_pair(8, COLOR_BLACK, COLOR_BLUE);
	init_pair(9, COLOR_BLACK, COLOR_RED);
	init_pair(10, COLOR_BLACK, COLOR_YELLOW);
	init_pair(11, COLOR_CYAN, COLOR_CYAN);
	init_pair(12, COLOR_WHITE, COLOR_GREEN);
	init_pair(13, COLOR_WHITE, COLOR_BLUE);
	init_pair(14, COLOR_WHITE, COLOR_RED);
	init_pair(15, COLOR_WHITE, COLOR_YELLOW);
	init_pair(16, COLOR_WHITE, COLOR_BLACK);
}

void	init_matrix(t_vm *vm)
{
	unsigned char	*mem;
	int				i;
	int				row;
	int				col;

	mem = vm->mem;
	i = 0;
	row = 1;
	col = 1;
	while (i < MEM_SIZE)
	{
		mvwaddch(vm->win->matrix, row, col++, nibble_to_char(mem[i] >> 4));
		mvwaddch(vm->win->matrix, row, col++, nibble_to_char(mem[i] & 0x0f));
		col++;
		i++;
		if (i % 64 == 0)
		{
			col = 1;
			row++;
		}
	}
	wrefresh(vm->win->matrix);
}

void	init_visualizer(t_vm *vm)
{
	if (vm->vis == 0)
		return ;
	initscr();
	noecho();
	cbreak();
	curs_set(0);
	if (has_colors() == FALSE)
	{
		endwin();
		exit(EXIT_FAILURE);
	}
	start_color();
	init_colors();
	refresh();
	if (!(vm->win = init_windows()))
	{
		endwin();
		exit(EXIT_FAILURE);
	}
	init_matrix(vm);
}

void	start_visualizer(t_vm *vm)
{
	char ch;

	if (vm->vis == 0)
		return ;
	write_info_par(vm);
	while ((ch = getch()) != ' ')
	{
		if (ft_strchr("qQwWeErR", ch))
		{
			change_speed(vm, ch);
			write_info_speed(vm);
		}
	}
	nodelay(stdscr, TRUE);
}
