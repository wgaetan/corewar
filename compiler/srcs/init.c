/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/11 10:53:23 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/24 20:35:39 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static void	print_usage(void)
{
	ft_putstr("Corewar's ASM compiler\n");
	ft_putstr("\tCompile asm files in bytecode used by corewar's vm\n\n");
	ft_putstr("Synopsis:\n");
	ft_putstr("\t$ ./asm [options] file_name\n\n");
	ft_putstr("Options:\n");
	ft_putstr("\t-h: Show this usage. (override any other options)\n");
	ft_putstr("\t-v: Detailed errors message if there is errors in file.\n");
	ft_putstr("\t-d: Display a visual representation of how the compiler ");
	ft_putstr("parse the file.\n");
	gc_exit(1);
}

void		fetch_options(t_stock *stock, int argc, char **argv)
{
	int		i;

	i = 0;
	stock->run_options = 0;
	while (++i < argc)
	{
		if (argv[i][0] == '-')
		{
			if (ft_strlen(argv[i]) == 2 && argv[i][1] == 'h')
				stock->run_options |= HELP_OPTION;
			else if (ft_strlen(argv[i]) == 2 && argv[i][1] == 'd')
				stock->run_options |= VISUAL_DEBUG_OPTION;
			else if (ft_strlen(argv[i]) == 2 && argv[i][1] == 'v')
				stock->run_options |= ERROR_VERBOSE_OPTION;
			else
				exit_failure("Wrong parameter(s), run -h to see options\n");
		}
		else
			stock->dot_s.name = argv[i];
	}
	if (stock->run_options & HELP_OPTION)
		print_usage();
}

void		init(void)
{
	t_stock	*stock;
	int		i;

	stock = get_stock();
	i = 0;
	while (i < PROG_NAME_LENGTH + 1)
		stock->header.prog_name[i++] = '\0';
	i = 0;
	while (i < COMMENT_LENGTH + 1)
		stock->header.comment[i++] = '\0';
	stock->tokens = NULL;
	stock->operators = NULL;
	stock->labels = NULL;
	stock->labels_pos = NULL;
	stock->header.name_exist = 0;
	stock->header.comment_exist = 0;
}
