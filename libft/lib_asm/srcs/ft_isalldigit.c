/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_isalldigit.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <wgaetan@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/29 15:08:49 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/23 18:51:28 by wgaetan     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_isalldigit(char *str)
{
	int		ret;
	int		i;

	ret = 1;
	i = -1;
	while (str && str[++i])
		if (!(str[i] >= '0' && str[i] <= '9'))
			ret = 0;
	return (ret);
}
