/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   errors.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/14 16:51:54 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/24 15:11:15 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op_vm.h"

int		n_error(int nb)
{
	char	c;

	c = nb + 48;
	write(2, "Invalid player number or usage of -n\n", 37);
	if (nb == 1)
		write(2, "\tUsage: ./corewar -n 1 file.cor\n", 33);
	else
	{
		write(2, "\tUsage: ./corewar -n [1-", 24);
		write(2, &c, 1);
		write(2, "] file.cor (for each contestant)\n", 33);
	}
	return (1);
}

int		file_error(t_vm *vm, char *file)
{
	if (vm->vis)
	{
		endwin();
		free(vm->win);
	}
	write(2, "Can't read source file ", 23);
	write(2, file, ft_strlen(file));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
	return (1);
}

int		champ_error(t_vm *vm, char *file, int fd)
{
	if (vm->vis)
	{
		endwin();
		free(vm->win);
	}
	write(2, "Error: file ", 12);
	write(2, file, ft_strlen(file));
	write(2, " has an invalid header\n", 23);
	if (fd)
		close(fd);
	exit(EXIT_FAILURE);
	return (1);
}

int		champ_toosmall(t_vm *vm, char *file, int fd)
{
	if (vm->vis)
	{
		endwin();
		free(vm->win);
	}
	write(2, "Error: file ", 12);
	write(2, file, ft_strlen(file));
	write(2, " is too small to be a champion\n", 31);
	close(fd);
	exit(EXIT_FAILURE);
	return (1);
}
