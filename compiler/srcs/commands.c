/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   commands.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <wgaetan@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/10 21:13:04 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/24 20:34:55 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

void		get_command_text(t_token *token, int cmd_type, int milestone)
{
	t_stock	*stock;
	int		i;
	int		len;

	stock = get_stock();
	i = milestone;
	while (i < token->len && token->content[i] != '"')
	{
		if (token->content[i] != ' ' && token->content[i] != '\t')
			token->error |= E3;
		i++;
	}
	if (token->content[i] != '\0' && i < token->len)
	{
		if (token->content[token->len - 1] != '"')
			token->error |= E4;
		len = token->len - i - (token->error & E4 ? 1 : 2);
		if ((cmd_type == 0 && len > PROG_NAME_LENGTH) ||
				(cmd_type == 1 && len > COMMENT_LENGTH))
			token->error |= E2;
		if (token->error == 0 && cmd_type == 0)
			ft_strncpy(stock->header.prog_name, &token->content[i + 1], len);
		else if (token->error == 0 && cmd_type == 1)
			ft_strncpy(stock->header.comment, &token->content[i + 1], len);
	}
}

static void	check_command_placement(t_token *token, int pos)
{
	t_stock	*stock;
	int		i;
	int		same_line;

	stock = get_stock();
	i = pos - 1;
	same_line = 1;
	while (i >= 0 && token->error ^ E5)
	{
		if (stock->tokens[i].type == NEWLINE_TOKEN)
			same_line = 0;
		else if (stock->tokens[i].type == COMMAND_TOKEN)
		{
			if (same_line == 1)
				token->error |= E5;
		}
		else if (stock->tokens[i].type == LABEL_TOKEN ||
				stock->tokens[i].type == OP_TOKEN)
			token->error |= E5;
		i--;
	}
}

static void	verify_command(t_token *token)
{
	t_stock	*stock;
	int		i;

	stock = get_stock();
	i = 1;
	while (i < token->len && ft_isalpha(token->content[i]))
		i++;
	if (ft_strncmp(NAME_CMD_STRING, token->content, i) == 0)
	{
		stock->header.name_exist += 1;
		if (stock->header.name_exist == 1)
			get_command_text(token, 0, i);
		else
			token->error |= E6;
	}
	else if (ft_strncmp(COMMENT_CMD_STRING, token->content, i) == 0)
	{
		stock->header.comment_exist += 1;
		if (stock->header.comment_exist == 1)
			get_command_text(token, 1, i);
		else
			token->error |= E6;
	}
	else
		token->error |= E1;
}

void		check_commands(void)
{
	t_stock	*stock;
	int		i;

	stock = get_stock();
	i = 0;
	while (i < stock->tokens_count)
	{
		if (stock->tokens[i].type == COMMAND_TOKEN)
		{
			verify_command(&stock->tokens[i]);
			check_command_placement(&stock->tokens[i], i);
		}
		i++;
	}
}
