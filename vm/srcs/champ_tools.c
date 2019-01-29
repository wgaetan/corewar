/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   champ_tools.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/18 19:59:21 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/24 15:10:12 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op_vm.h"

static t_champ	*read_champ(unsigned char *bf, t_champ *champ, t_vm *vm)
{
	unsigned int	i;
	int				j;

	j = 0;
	if ((champ->head->magic = read_mem(bf, 3, 4)) != MAGIC)
		return (NULL);
	champ->head->prog_size = read_mem(bf, PROG_NAME_LENGTH + 11, 4);
	ft_memcpy(champ->head->prog_name, bf + 4, PROG_NAME_LENGTH);
	champ->head->prog_name[PROG_NAME_LENGTH] = '\0';
	ft_memcpy(champ->head->comment, bf + 12 + PROG_NAME_LENGTH,
			COMMENT_LENGTH);
	champ->head->comment[COMMENT_LENGTH] = '\0';
	i = PROG_NAME_LENGTH + COMMENT_LENGTH + 16;
	while (i < PROG_NAME_LENGTH + COMMENT_LENGTH + 16 + champ->head->prog_size)
	{
		vm->mem[j++ + champ->mempos] = bf[i++];
		if (vm->vis)
			write_matrix(vm->win->matrix, champ->id,
					j - 1 + champ->mempos, bf[i - 1]);
	}
	return (champ);
}

/*
** 16 = taille du magic + taille de la size du prog + deux fois 4
** octets vide, un entre le nom et la size, et un entre le comment et le prog
*/

static t_champ	*fill_champ(char *bf, t_champ *champs, t_vm *vm, int i)
{
	champs->mempos = (MEM_SIZE / vm->champ_nb) * (-champs->id - 1);
	if (!(champs = read_champ((unsigned char*)bf, champs, vm)))
		return (NULL);
	if (i < vm->champ_nb)
	{
		if (!(champs->next = init_champ()))
			ft_error("init_champ() failed");
		champs = champs->next;
	}
	return (champs);
}

static int		check_champ_size(t_vm *vm, int fd, int ret, char *file)
{
	if (fd <= 0)
	{
		file_error(vm, file);
		return (0);
	}
	if (ret < PROG_NAME_LENGTH + COMMENT_LENGTH + 16)
	{
		champ_toosmall(vm, file, fd);
		return (0);
	}
	else if (ret == CHAMP_MAX_SIZE + 17 + COMMENT_LENGTH + PROG_NAME_LENGTH)
	{
		champ_toobig(vm, file, fd);
		return (0);
	}
	return (1);
}

int				get_champs(t_vm *vm)
{
	int				i;
	int				fd;
	t_champ			*champs;
	unsigned char	bf[CHAMP_MAX_SIZE + 17 + COMMENT_LENGTH + PROG_NAME_LENGTH];

	if (!(vm->champ = init_champ()))
		ft_error("init_champ() failed");
	i = 0;
	champs = vm->champ;
	while (i < MAX_PLAYERS && vm->players_file[i])
	{
		if ((fd = open(vm->players_file[i], O_RDONLY)) < 0)
			return (file_error(vm, vm->players_file[i]));
		champs->id = -(vm->players_id[i]);
		if (!check_champ_size(vm, fd, read(fd, bf, sizeof(bf)),
					vm->players_file[i]))
			return (1);
		if (!(champs = fill_champ((char*)bf, champs, vm, ++i)))
			return (champ_error(vm, vm->players_file[i - 1], fd));
		close(fd);
	}
	if (vm->vis)
		write_info_par(vm);
	return (0);
}
