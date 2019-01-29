/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   op.c                                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/19 19:53:36 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/17 13:40:54 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op_vm.h"

t_opmodvm	*get_op_tab_vm(void)
{
	static t_opmodvm	op_tab_vm[17] = {
		{0, {0}, 0, 0, 0, 0},
		{1, {T_DIR}, 10, 0, 0, 4},
		{2, {T_DIR | T_IND, T_REG, 0}, 5, 1, 0, 4},
		{2, {T_REG, T_IND | T_REG, 0}, 5, 1, 0, 4},
		{3, {T_REG, T_REG, T_REG}, 10, 1, 0, 4},
		{3, {T_REG, T_REG, T_REG}, 10, 1, 0, 4},
		{3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 1, 0, 4},
		{3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 6, 1, 0, 4},
		{3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 6, 1, 0, 4},
		{1, {T_DIR}, 20, 0, 1, 2},
		{3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 25, 1, 1, 2},
		{3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 25, 1, 1, 2},
		{1, {T_DIR}, 800, 0, 1, 2},
		{2, {T_DIR | T_IND, T_REG, 0}, 10, 1, 0, 4},
		{3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 50, 1, 1, 2},
		{1, {T_DIR}, 1000, 0, 1, 2},
		{1, {T_REG, 0, 0}, 2, 1, 0, 2},
	};

	return (op_tab_vm);
}
