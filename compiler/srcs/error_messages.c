/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   op_model.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <wgaetan@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/30 20:24:18 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/24 20:35:02 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

const char				*command_errors(int error)
{
	if (error == 0)
		return ("COMMAND");
	if (error == 1)
		return ("Unknown command");
	if (error == 2)
		return ("Text too long");
	if (error == 3)
		return ("Unwanted char before oppening bracket");
	if (error == 4)
		return ("Missing closing bracket");
	if (error == 5)
		return ("Command not well placed");
	if (error == 6)
		return ("Command already existing");
	return (NULL);
}

const char				*label_errors(int error)
{
	if (error == 0)
		return ("LABEL");
	if (error == 1)
		return ("Invalid char in label");
	if (error == 2)
		return ("Label already existing");
	if (error == 3)
		return ("Void label");
	return (NULL);
}

const char				*operator_errors(int error)
{
	if (error == 0)
		return ("OPERATOR");
	if (error == 1)
		return ("Bad parameter(s) count");
	if (error == 2)
		return ("Wrong parameter(s)");
	if (error == 3)
		return ("Unknown token");
	return (NULL);
}

const char				*param_errors(int error)
{
	if (error == 0)
		return ("Void parameter");
	if (error == 1)
		return ("Wrong type");
	if (error == 2)
		return ("Invalid char");
	if (error == 3)
		return ("Unknown label");
	if (error == 4)
		return ("Invalid register value");
	return (NULL);
}

const char				*get_error_message(int token_type, int error)
{
	if (token_type == 0 && error == 0)
		return ("UNKNOWN");
	else if (token_type == 0 && error == 1)
		return ("Could not identify token type");
	else if (token_type == 1)
		return (command_errors(error));
	else if (token_type == 2)
		return (label_errors(error));
	else if (token_type == 3)
		return (operator_errors(error));
	else if (token_type == 4)
		return (param_errors(error));
	return (NULL);
}
