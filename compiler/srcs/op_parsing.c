/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   op_parsing.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/08 13:36:30 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/24 20:36:40 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static void		init_operator(t_op *op, t_token *token)
{
	op->token = token;
	op->type = 0;
	op->index = 0;
	op->size = 0;
	op->ocp = 0;
	op->pcount = 0;
	get_op_type(op);
}

void			create_op_array(void)
{
	t_stock		*stock;
	int			i;
	int			y;

	stock = get_stock();
	i = 0;
	stock->op_count = 0;
	while (i < stock->tokens_count)
	{
		if (stock->tokens[i].type == OP_TOKEN)
			stock->op_count++;
		i++;
	}
	stock->operators = gc_alloc(sizeof(t_op) * stock->op_count, 0);
	i = 0;
	y = 0;
	while (i < stock->tokens_count)
	{
		if (stock->tokens[i].type == OP_TOKEN)
			init_operator(&stock->operators[y++], &stock->tokens[i]);
		i++;
	}
}

void			get_op_type(t_op *op)
{
	t_op_model	op_model;
	int			i;
	int			tag_end;

	i = ft_charpos(op->token->content, '\t');
	tag_end = ft_charpos(op->token->content, ' ');
	if ((i < tag_end && i >= 0) || tag_end < 0)
		tag_end = i;
	i = 1;
	op->instruction = ft_strndup(op->token->content, tag_end);
	while (i < OP_COUNT && op->type == 0)
	{
		op_model = get_op_model(i);
		if (ft_strcmp(op->instruction, op_model.tag) == 0)
			op->type = i;
		i++;
	}
	if (op->type == 0)
		op->token->error |= E3;
}

static void		parse_op(t_op *op)
{
	t_stock		*stock;
	t_op_model	op_model;
	int			i;

	stock = get_stock();
	get_param_str(op);
	i = 0;
	if (op->token->error == 0)
	{
		op_model = get_op_model(op->type);
		while (i < op->pcount)
		{
			analyze_op_param(&op->params[i]);
			if (op->params[i].error == 0 &&
					!(op->params[i].type & op_model.pcheck[i]))
				op->params[i].error |= E2;
			if (op->params[i].error != 0)
				op->token->error |= E2;
			i++;
		}
		calc_op_size(op);
	}
}

void			op_parsing(void)
{
	t_stock		*stock;
	int			i;

	stock = get_stock();
	i = 0;
	while (i < stock->op_count)
	{
		if (stock->operators[i].token->error ^ E3)
			parse_op(&stock->operators[i]);
		i++;
	}
}
