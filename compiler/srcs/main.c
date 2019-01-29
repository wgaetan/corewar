/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <wgaetan@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/29 21:37:39 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/24 20:36:01 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

int				main(int argc, char **argv)
{
	t_stock		*stock;
	int			i;

	stock = get_stock();
	i = 0;
	fetch_options(stock, argc, argv);
	init();
	get_file_content(&stock->dot_s);
	tokenize();
	check_commands();
	create_label_array();
	create_op_array();
	op_parsing();
	if (stock->run_options & VISUAL_DEBUG_OPTION)
		print_tokens();
	error_output();
	get_labels_and_op_pos();
	calc_label_params();
	build_output_content();
	gc_exit(1);
	return (0);
}
