/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_atou.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <wgaetan@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/11 15:56:09 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/23 18:50:56 by wgaetan     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/libft.h"

static unsigned char	*prep_string(char *str, int *len)
{
	unsigned char		*new;
	int					limits[2];
	int					i;

	i = 0;
	limits[0] = -1;
	limits[1] = -1;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	limits[0] = i;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	limits[1] = i;
	if ((*len = (limits[1] - limits[0])) == 0)
		new = NULL;
	else
		new = gc_alloc(sizeof(char) * (*len) + 1, 0);
	i = -1;
	while (++i < *len)
		new[i] = str[i + limits[0]] - 48;
	return (new);
}

static void				div_by_two(unsigned char *str, int len)
{
	short				add[2];
	int					i;

	i = 0;
	add[0] = 0;
	add[1] = 0;
	while (i < len)
	{
		add[1] = (str[i] & 1) * 5;
		str[i] = (str[i] >> 1) + add[0];
		add[0] = add[1];
		i++;
	}
}

static int				is_zero(unsigned char *str, int len)
{
	int					i;

	i = 0;
	while (i < len)
	{
		if (str[i] > 0)
			return (0);
		i++;
	}
	return (1);
}

int						ft_atou(char *str, unsigned long *number)
{
	unsigned char		*tmp;
	int					len;
	unsigned long		bin;
	int					i;

	bin = 1;
	i = 0;
	*number = 0;
	tmp = prep_string(str, &len);
	while (!(is_zero(tmp, len)))
	{
		if (tmp[len - 1] & 1)
			*number = *number | bin;
		bin = bin << 1;
		div_by_two(tmp, len);
		i++;
	}
	gc_free(tmp, 0);
	return (len);
}
