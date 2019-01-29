/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tokens_end.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <wgaetan@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/08 13:37:48 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/24 20:37:24 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

int		end_of_cmt_token(char *buff)
{
	int	i;

	i = 0;
	while (buff[i] != '\0' && buff[i] != '\n')
		i++;
	return (i - 1);
}

int		end_of_cmd_token(char *buff)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (buff[i] != '\0')
	{
		if (buff[i] == '"')
			count++;
		if ((buff[i] == '\n' && count == 0) || count == 2)
			break ;
		i++;
	}
	i += count == 2 ? 1 : 0;
	return (i - 1);
}

int		end_of_lbl_or_op_token(char *buff)
{
	int	i;
	int	a;

	i = 0;
	a = 1;
	while (buff[i] != '\0' && buff[i] != '\n' && buff[i] != COMMENT_CHAR)
	{
		if (buff[i] == LABEL_CHAR && ft_strchr(LABEL_CHARS, buff[i - 1]))
			break ;
		i++;
	}
	while (a > 0 && (buff[i - 1] == ' ' || buff[i - 1] == '\t'))
		i--;
	return (i - (buff[i] == LABEL_CHAR ? 0 : 1));
}

int		end_of_wsp_token(char *buff)
{
	int	i;

	i = 0;
	while (buff[i] != '\0' && (buff[i] == '\t' || buff[i] == ' '))
		i++;
	return (i - 1);
}

int		end_of_unknown_token(char *buff)
{
	int	i;

	i = 0;
	while (buff[i] != '\0' && buff[i] != '\t' && buff[i] != ' ' &&
			buff[i] != COMMENT_CHAR && buff[i] != '\n')
		i++;
	return (i - 1);
}
