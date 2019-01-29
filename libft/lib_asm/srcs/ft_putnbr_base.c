/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putnbr_base.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <wgaetan@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/11 12:31:38 by shthevak     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/23 18:50:56 by wgaetan     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_putnbr_base(int nb, int base)
{
	if (nb < 0)
	{
		ft_putchar('-');
		if (-(nb / base))
			ft_putnbr_base(-(nb / base), base);
		ft_putchar(ft_inttochar(-(nb % base)));
	}
	else if (nb >= base)
	{
		ft_putnbr_base(nb / base, base);
		ft_putchar(ft_inttochar(nb % base));
	}
	else if (nb < base)
		ft_putchar(ft_inttochar(nb));
}
