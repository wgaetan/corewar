/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   errors2.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bodibon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/24 15:10:53 by bodibon      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/24 15:15:00 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op_vm.h"

static void		write_message_champ_too_big(char *file, char *size,
		char *maxsize)
{
	write(2, "Error: file ", 12);
	write(2, file, ft_strlen(file));
	write(2, " has too large a code (", 23);
	write(2, size, ft_strlen(size));
	write(2, " bytes > ", 9);
	write(2, maxsize, ft_strlen(maxsize));
	write(2, " bytes)\n", 8);
}

int				champ_toobig(t_vm *vm, char *file, int fd)
{
	char	buf[800];
	int		ret;
	int		bytes;
	char	*size;
	char	*maxsize;

	close(fd);
	bytes = 0;
	fd = open(file, O_RDONLY);
	while ((ret = read(fd, buf, 800)))
		bytes += ret;
	size = ft_itoa(bytes - 16 - COMMENT_LENGTH - PROG_NAME_LENGTH);
	maxsize = ft_itoa(CHAMP_MAX_SIZE);
	if (vm->vis)
	{
		endwin();
		free(vm->win);
	}
	write_message_champ_too_big(file, size, maxsize);
	ft_strdel(&size);
	ft_strdel(&maxsize);
	close(fd);
	exit(EXIT_FAILURE);
	return (1);
}
