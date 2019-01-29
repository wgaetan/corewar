/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strjoinfree.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <wgaetan@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/17 17:48:17 by shthevak     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/23 19:05:22 by wgaetan     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoinfree(char **s1, char *s2)
{
	char *ret;

	ret = gc_alloc(sizeof(char) * (ft_strlen(*s1) + ft_strlen(s2) + 1), 0);
	ret[0] = '\0';
	ret = ft_strcat(ret, *s1);
	ret = ft_strcat(ret, s2);
	ft_strdel(s1);
	return (ret);
}
