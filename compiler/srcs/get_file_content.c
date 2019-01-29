/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_file_content.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <wgaetan@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/30 15:25:45 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/24 20:34:27 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static void	expand_buffer(t_file *file, int i)
{
	char	*tmp;

	if (i == 1)
		tmp = gc_alloc(CONTENT_BUFF_SIZE + 1, 0);
	else
	{
		tmp = gc_alloc((CONTENT_BUFF_SIZE * i) + 1, 0);
		ft_strcpy(tmp, file->content);
		gc_free(file->content, 0);
	}
	file->content = tmp;
}

static void	file_to_buffer(t_file *file)
{
	ssize_t	read_size;
	char	read_buff[CONTENT_BUFF_SIZE + 1];
	int		i;

	file->fd = open(file->name, O_RDONLY);
	if (file->fd < 0)
		exit_failure("Invalid file\n");
	i = 0;
	while ((read_size = read(file->fd, read_buff, CONTENT_BUFF_SIZE)) > 0)
	{
		read_buff[read_size] = '\0';
		if ((read_size + file->size) > (size_t)(CONTENT_BUFF_SIZE * i))
			expand_buffer(file, ++i);
		ft_strcat(file->content, read_buff);
		file->size += read_size;
	}
	file->size = ft_strlen(file->content);
	if (file->size == 0)
		exit_failure("No content in file\n");
}

void		get_file_content(t_file *file)
{
	clear_file(file);
	file_to_buffer(file);
}
