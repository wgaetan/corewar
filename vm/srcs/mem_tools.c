/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mem_tools.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/30 16:47:30 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/23 18:26:05 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op_vm.h"

int		read_mem(unsigned char *mem, int start, size_t bytes)
{
	size_t	i;
	int		ret;
	int		pos;

	i = 0;
	ret = 0;
	while (i < bytes)
	{
		while (start - (int)i < 0)
			start += MEM_SIZE;
		pos = (start - i) % MEM_SIZE;
		ret += (mem[pos] & 0xFF) << (i * 8);
		i++;
	}
	return (ret);
}

void	write_mem(unsigned char *mem, int start, size_t bytes, int val)
{
	size_t	i;
	int		pos;

	i = 0;
	pos = 0;
	while (i < bytes)
	{
		while (start - (int)i < 0)
			start += MEM_SIZE;
		pos = (start - i) % MEM_SIZE;
		mem[pos] = (val >> (i * 8)) & 0xFF;
		i++;
	}
}
