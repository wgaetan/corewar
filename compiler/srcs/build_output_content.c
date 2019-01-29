/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   build_output_content.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/14 20:46:36 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/24 20:34:46 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static void			calc_ocp(t_op *op)
{
	t_op_model		op_model;
	int				i;

	op_model = get_op_model(op->type);
	i = 0;
	op->ocp = 0;
	while (i < op->pcount && op_model.ocp == 1)
	{
		if (op->params[i].type & T_REG)
			op->ocp += 0b01;
		else if (op->params[i].type & T_IND)
			op->ocp += 0b11;
		else if (op->params[i].type & T_DIR)
			op->ocp += 0b10;
		op->ocp = op->ocp << 2;
		i++;
	}
	op->ocp = op->ocp << (2 * (3 - op->pcount));
}

static int			write_unsigned_number(char *str, unsigned long number,
		int sign, int len)
{
	unsigned long	i;

	i = 0;
	if (len == 8)
		number &= LONG_MASK;
	else if (len == 4)
		number &= INT_MASK;
	else if (len == 2)
		number &= SHORT_MASK;
	if (sign == 1 && number > 0)
		number = ~(number - 1);
	while ((int)i < len)
	{
		str[len - (i + 1)] = ((number & 0xFF << (8 * i)) >> (8 * i));
		i++;
	}
	return (len);
}

static void			write_header(int head_size)
{
	t_stock			*stock;
	int				i;
	int				j;

	stock = get_stock();
	stock->header.magic = COREWAR_EXEC_MAGIC;
	if (stock->op_count > 0)
		stock->header.prog_size = stock->operators[stock->op_count - 1].index +
			stock->operators[stock->op_count - 1].size;
	else
		stock->header.prog_size = 0;
	stock->dot_cor.size = stock->header.prog_size + head_size;
	stock->dot_cor.content = gc_alloc(sizeof(char) * stock->dot_cor.size, 0);
	write_unsigned_number(stock->dot_cor.content, stock->header.magic, 0, 4);
	i = 4;
	j = 0;
	while (j < PROG_NAME_LENGTH)
		stock->dot_cor.content[i++] = stock->header.prog_name[j++];
	i += write_unsigned_number(&stock->dot_cor.content[i], 0, 0, 4);
	i += write_unsigned_number(&stock->dot_cor.content[i],
			stock->header.prog_size, 0, 4);
	j = 0;
	while (j < COMMENT_LENGTH)
		stock->dot_cor.content[i++] = stock->header.comment[j++];
	i += write_unsigned_number(&stock->dot_cor.content[i], 0, 0, 4);
}

static void			write_in_file(void)
{
	t_stock			*stock;

	stock = get_stock();
	get_dot_cor_name();
	stock->dot_cor.fd = open(stock->dot_cor.name, O_WRONLY | O_TRUNC | O_CREAT,
			0666);
	if (stock->dot_cor.fd >= 0)
		write(stock->dot_cor.fd, stock->dot_cor.content, stock->dot_cor.size);
	else
		exit_failure("Failed to create/rewrite .cor file.\n");
	exit_success(stock->dot_cor.name);
}

void				build_output_content(void)
{
	t_stock			*stock;
	int				i;
	int				j;
	int				k;

	stock = get_stock();
	i = 4 + PROG_NAME_LENGTH + COMMENT_LENGTH + 4 + 8;
	write_header(i);
	j = 0;
	while (j < stock->op_count)
	{
		k = -1;
		calc_ocp(&stock->operators[j]);
		stock->dot_cor.content[i++] = stock->operators[j].type;
		if (stock->operators[j].ocp != 0)
			stock->dot_cor.content[i++] = stock->operators[j].ocp;
		while (++k < stock->operators[j].pcount)
			i += write_unsigned_number(&stock->dot_cor.content[i],
					stock->operators[j].params[k].value,
					stock->operators[j].params[k].is_negative,
					stock->operators[j].params[k].size);
		j++;
	}
	write_in_file();
}
