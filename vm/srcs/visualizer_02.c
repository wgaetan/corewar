/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   visualizer_02.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bodibon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/09 18:16:19 by bodibon      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/24 17:02:48 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op_vm.h"

char	nibble_to_char(unsigned char ch)
{
	return ((ch < 10) ? ch + '0' : ch - 10 + 'a');
}

void	write_matrix(WINDOW *matrix, int proc_id, unsigned int pos,
		unsigned char c)
{
	unsigned int	row;
	unsigned int	col;

	row = 1 + (pos / 64);
	col = 1 + (3 * (pos % 64));
	wattron(matrix, COLOR_PAIR(3 + (-proc_id - 1)));
	mvwaddch(matrix, row, col, nibble_to_char(c >> 4));
	mvwaddch(matrix, row, col + 1, nibble_to_char(c & 0x0f));
	wattroff(matrix, COLOR_PAIR(3 + (-proc_id - 1)));
	wrefresh(matrix);
}

void	write_matrix2(WINDOW *matrix, int start, int val, int proc_id)
{
	int				i;
	int				pos;
	unsigned char	c;

	i = 0;
	while (i < REG_SIZE)
	{
		while (start - i < 0)
			start += MEM_SIZE;
		pos = (start - i) % MEM_SIZE;
		c = (val >> (i * 8)) & 0xff;
		write_matrix(matrix, proc_id, pos, c);
		i++;
	}
}

void	set_cursor_color(WINDOW *matrix, unsigned int pos)
{
	unsigned int	row;
	unsigned int	col;
	short			color_pair;

	row = 1 + (pos / 64);
	col = 1 + (3 * (pos % 64));
	color_pair = PAIR_NUMBER(mvwinch(matrix, row, col) & A_COLOR);
	if (color_pair >= 3 && color_pair <= 6)
		mvwchgat(matrix, row, col, 2, A_COLOR, color_pair + 4, NULL);
	else if (color_pair == 2)
		mvwchgat(matrix, row, col, 2, A_COLOR, 11, NULL);
	wrefresh(matrix);
}

void	unset_cursor_color(WINDOW *matrix, unsigned int pos)
{
	unsigned int	row;
	unsigned int	col;
	short			color_pair;

	row = 1 + (pos / 64);
	col = 1 + (3 * (pos % 64));
	color_pair = PAIR_NUMBER(mvwinch(matrix, row, col) & A_COLOR);
	if (color_pair >= 7 && color_pair <= 10)
		mvwchgat(matrix, row, col, 2, A_COLOR, color_pair - 4, NULL);
	else if (color_pair == 11)
		mvwchgat(matrix, row, col, 2, A_COLOR, 2, NULL);
	wrefresh(matrix);
}
