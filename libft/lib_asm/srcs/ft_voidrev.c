/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_voidrev.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <wgaetan@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/11 12:31:39 by shthevak     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/23 18:50:56 by wgaetan     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_voidrev(void *s)
{
	size_t		i;
	size_t		j;
	char		*c;

	i = 0;
	c = (char *)s;
	while (c[i])
		i++;
	j = 0;
	i--;
	while (i > j)
	{
		ft_voidswap(&c[i--], &c[j++]);
	}
	return (s);
}
