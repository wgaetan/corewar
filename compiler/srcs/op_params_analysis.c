/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   op_params_analysis.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/14 17:32:44 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/24 20:36:30 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static void		op_param_int_check(t_op_param *param)
{
	int			i;
	int			a;

	a = 0;
	param->is_negative = 0;
	if ((param->type & T_DIR || param->type & T_REG) && param->len < 2)
		param->error |= E1;
	else if (param->type & T_DIR || param->type & T_REG)
		a = 1;
	i = a - 1;
	if (param->str[a] == '-' || param->str[a] == '+')
	{
		param->is_negative = param->str[a] == '-' ? 1 : 0;
		i++;
	}
	while (++i < param->len && param->error == 0)
		if (!(ft_isdigit(param->str[i])))
			param->error |= E3;
	if (param->error ^ E3 && ft_atou(&param->str[a], &param->value) == 0)
		param->error |= E1;
	if ((param->error ^ E3 && param->type & T_REG && param->value > REG_NUMBER)
			|| (param->type & T_REG && param->is_negative == 1))
		param->error |= E5;
}

static void		op_param_lbl_check(t_op_param *param)
{
	t_stock		*stock;
	int			found;
	int			i;

	stock = get_stock();
	i = param->str[0] == DIRECT_CHAR ? 2 : 1;
	found = -1;
	param->is_negative = 0;
	if (param->len < i + 1)
		param->error |= E1;
	if (!(param->error & E1) && wrong_label_char(&param->str[i]))
		param->error |= E3;
	i = -1;
	while (++i < stock->labels_count && found == -1 && param->error == 0)
		if (ft_strcmp(&param->str[ft_charpos(param->str, LABEL_CHAR) + 1],
					stock->labels[i]) == 0)
			found = i;
	if (found == -1 && param->error == 0)
		param->error |= E4;
	else
		param->value = found;
}

void			get_param_str(t_op *op)
{
	char		*new;
	int			i;
	int			a;
	int			b;

	new = NULL;
	i = 0;
	a = 0;
	while (i < op->token->len && ft_isalpha(op->token->content[i]))
		i++;
	while (i < op->token->len && (op->token->content[i] == ' ' ||
				op->token->content[i] == '\t'))
		i++;
	a = op->token->len - i;
	if (a > 0)
	{
		new = gc_alloc(sizeof(char) * (a + 1), 0);
		b = 0;
		while (b < a)
			new[b++] = op->token->content[i++];
		split_params(op, new);
		gc_free(new, 0);
	}
	else
		op->token->error = E1;
}

void			split_params(t_op *op, char *str)
{
	t_op_model	op_model;
	int			i;
	int			a;
	int			c;

	op->pcount = ft_countchar(str, SEPARATOR_CHAR) + 1;
	i = 0;
	a = 0;
	op_model = get_op_model(op->type);
	op->token->error |= (op->pcount != op_model.pcount) ? E1 : 0;
	if (op->token->error == 0)
	{
		op->params = gc_alloc(sizeof(t_op_param) * op->pcount, 0);
		if (op->pcount == 1)
			op->params[0].str = ft_strdup(str);
		else
		{
			while (i < op->pcount)
			{
				op->params[i++].str = ft_strtrim(ft_strndup(&str[a],
						c = ft_charpos(&str[a], SEPARATOR_CHAR)));
				a += c + 1;
			}
		}
	}
}

void			analyze_op_param(t_op_param *param)
{
	param->len = ft_strlen(param->str);
	if (param->str == NULL)
		param->error |= E1;
	else
	{
		param->type = 0;
		if (param->str[0] == 'r' && param->len >= 2)
			param->type |= T_REG;
		else if (param->str[0] == DIRECT_CHAR && param->len >= 2)
			param->type |= T_DIR + ((param->str[1] == LABEL_CHAR) ? T_LAB : 0);
		else if (ft_isdigit(param->str[0]) || param->str[0] == '-' ||
				param->str[0] == '+')
			param->type |= T_IND;
		else if (param->str[0] == LABEL_CHAR && param->len >= 2)
			param->type |= (T_IND + T_LAB);
		else
			param->error |= E3;
		if (!(param->error & (E1 + E3)))
		{
			if (param->type & T_LAB)
				op_param_lbl_check(param);
			else
				op_param_int_check(param);
		}
	}
}
