/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_atoi.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <wgaetan@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/11 12:31:21 by shthevak     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/23 18:50:56 by wgaetan     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_atoi(const char *str)
{
	unsigned long	r;
	int				s;

	s = 1;
	r = 0;
	while ((*str == '\t' || *str == '\f' || *str == '\v' ||
			*str == '\n' || *str == '\r' || *str == ' ')
			&& *str != '\0')
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			s = -1;
	while (*str >= '0' && *str <= '9')
	{
		r = r * 10 + *str - 48;
		str++;
	}
	if (r >= 9223372036854775807)
		return (s == 1 ? -1 : 0);
	return (s * (int)r);
}
