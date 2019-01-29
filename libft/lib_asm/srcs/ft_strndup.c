/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strndup.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <wgaetan@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/11 12:31:38 by shthevak     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/24 13:12:00 by wgaetan     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strndup(const char *s, int n)
{
	size_t	l;
	char	*r;

	if ((size_t)n > ft_strlen(s))
		n = ft_strlen(s);
	if (n <= 0 || !s)
		return (NULL);
	r = gc_alloc(sizeof(*r) * (n + 1), 0);
	l = 0;
	while (s[l] && l < (size_t)n)
	{
		r[l] = s[l];
		l++;
	}
	r[n] = '\0';
	return (r);
}
