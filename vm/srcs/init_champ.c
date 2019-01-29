/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_champ.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/15 16:21:44 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/15 16:22:16 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op_vm.h"

t_champ			*init_champ(void)
{
	t_champ			*champ;

	if (!(champ = malloc(sizeof(t_champ))))
		return (NULL);
	champ->id = 0;
	champ->mempos = 0;
	champ->head = init_head();
	champ->next = NULL;
	champ->lastlive = 0;
	champ->lives = 0;
	return (champ);
}
