/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   op_model.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <wgaetan@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/30 20:24:18 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/24 20:36:13 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

t_op_model				get_op_model(int i)
{
	static const t_op_model	op_model_tab[OP_COUNT] = {
		{0, 0, {0}, 0, 0},
		{"live", 1, {T_DIR}, 0, 4},
		{"ld", 2, {T_DIR | T_IND, T_REG}, 1, 4},
		{"st", 2, {T_REG, T_IND | T_REG}, 1, 0},
		{"add", 3, {T_REG, T_REG, T_REG}, 1, 0},
		{"sub", 3, {T_REG, T_REG, T_REG}, 1, 0},
		{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 1, 4},
		{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 1, 4},
		{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 1, 4},
		{"zjmp", 1, {T_DIR}, 0, 2},
		{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 1, 2},
		{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 1, 2},
		{"fork", 1, {T_DIR}, 0, 2},
		{"lld", 2, {T_DIR | T_IND, T_REG}, 1, 4},
		{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 1, 2},
		{"lfork", 1, {T_DIR}, 0, 2},
		{"aff", 1, {T_REG}, 1, 0},
	};

	return (op_model_tab[i]);
}
