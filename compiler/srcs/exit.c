/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exit.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/15 20:09:54 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/24 20:35:24 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

void	exit_failure(char *failure_message)
{
	ft_putstr(failure_message);
	gc_exit(-1);
}

void	exit_success(char *filename)
{
	ft_putstr("Writing output program to ");
	ft_putstr(filename);
	ft_putstr("\n");
	gc_exit(0);
}
