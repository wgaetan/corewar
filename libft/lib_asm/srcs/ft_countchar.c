/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_countchar.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <wgaetan@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/08 16:20:24 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/23 18:50:56 by wgaetan     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_countchar(const char *str, const char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
		count += (str[i++] == c ? 1 : 0);
	return (count);
}
