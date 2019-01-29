/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   error_verbose.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/13 22:02:05 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/24 20:35:14 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static void	error_message(t_stock *stock, int id)
{
	int		a;

	a = -1;
	while (++a < 8)
	{
		if (stock->tokens[id].error & (1 << a))
		{
			ft_putstr("[ERROR: ");
			ft_putstr(get_error_message(stock->tokens[id].type, a + 1));
			ft_putstr("] (Line ");
			ft_putnbr(stock->tokens[id].pos[0]);
			ft_putstr(" ; Token ");
			ft_putnbr(stock->tokens[id].pos[1]);
			ft_putstr(") Type: ");
			ft_putstr(get_error_message(stock->tokens[id].type, 0));
			ft_putchar('\n');
		}
	}
}

static void	op_error_message(t_stock *stock, int token_id, int op_id)
{
	int		a;
	int		i;
	t_op	*op;

	op = &stock->operators[op_id];
	error_message(stock, token_id);
	if (op->token->error & E2)
	{
		i = -1;
		while (++i < op->pcount)
		{
			a = -1;
			while (++a < 8)
				if (op->params[i].error & (1 << a))
				{
					ft_putstr("\t[ERROR] Parameter ");
					ft_putnbr(i + 1);
					ft_putchar(' ');
					ft_putstr(get_error_message(4, a));
					ft_putchar('\n');
				}
		}
	}
}

static void	advanced_verbose(int *errors)
{
	t_stock	*stock;
	int		i;
	int		op_id;

	stock = get_stock();
	i = -1;
	op_id = -1;
	if (stock->header.name_exist < 1)
		ft_putstr("[ERROR] Missing name command.\n");
	if (stock->header.comment_exist < 1)
		ft_putstr("[ERROR] Missing comment command.\n");
	while (++i < stock->tokens_count)
	{
		if (stock->tokens[i].type == OP_TOKEN)
			op_id++;
		if (stock->tokens[i].error != 0)
		{
			if (stock->tokens[i].type == OP_TOKEN)
				op_error_message(stock, i, op_id);
			else
				error_message(stock, i);
			*errors += 1;
		}
	}
}

void		error_output(void)
{
	t_stock	*stock;
	int		errors;
	int		i;

	stock = get_stock();
	errors = 0;
	i = 0;
	errors += stock->header.name_exist < 1 ? 1 : 0;
	errors += stock->header.comment_exist < 1 ? 1 : 0;
	if (stock->run_options & ERROR_VERBOSE_OPTION)
		advanced_verbose(&errors);
	else
	{
		while (i < stock->tokens_count)
			if (stock->tokens[i++].error != 0)
				errors++;
		if (errors > 0)
		{
			ft_putnbr(errors);
			ft_putstr(" error(s) in the file.\n");
		}
	}
	if (errors != 0)
		exit_failure("Use -h for debug options.\n");
}
