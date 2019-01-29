/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <wgaetan@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/29 17:36:32 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/24 20:53:20 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

/*
** Base sur le fichier op.h ecrit par zaz <marvin@42.fr>
** Toutes les tailles sont en octet
*/

#ifndef ASM_H
# define ASM_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "../../libft/lib_asm/includes/libft.h"

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','
# define COMMAND_CHAR			'.'

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define REG_NUMBER				16

# define MAX_ARGS_NUMBER		4

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

# define CONTENT_BUFF_SIZE		100

# define OP_COUNT				17

/*
** Token's define
*/

# define UNKNOWN_TOKEN			0
# define COMMAND_TOKEN			1
# define LABEL_TOKEN			2
# define OP_TOKEN				3
# define NEWLINE_TOKEN			4
# define WHITESPACE_TOKEN		5
# define COMMENT_TOKEN			6

# define TOKENS_LIMIT_INC		10

/*
** Colors code
*/

# define BLACK					"\033[0;30m"
# define YELLOW					"\033[1;33m"
# define BLUE					"\033[0;34m"
# define MAGENTA				"\033[1;35m"
# define CYAN					"\033[0;36m"
# define WHITE					"\033[0;37m"
# define G_BACK					"\e[48;5;28m"
# define R_BACK					"\e[48;5;124m"
# define RESET					"\e[0m"

/*
** Errors and Fatal errors masks
*/

# define E1						1
# define E2						2
# define E3						4
# define E4						8
# define E5						16
# define E6						32
# define E7						64
# define E8						128

/*
** Unsigned to signed conversion masks
*/

# define LONG_MASK				0xFFFFFFFFFFFFFFFF
# define INT_MASK				0xFFFFFFFF
# define SHORT_MASK				0xFFFF

/*
** run_options masks
*/

# define HELP_OPTION			1
# define ERROR_VERBOSE_OPTION	2
# define VISUAL_DEBUG_OPTION	4

typedef struct		s_token
{
	char			*content;
	int				len;
	int				pos[2];
	unsigned char	type;
	unsigned char	error;
}					t_token;

typedef struct		s_header
{
	unsigned int	magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	unsigned int	prog_size;
	char			comment[COMMENT_LENGTH + 1];
	int				name_exist;
	int				comment_exist;
}					t_header;

typedef struct		s_op_model
{
	char			*tag;
	int				pcount;
	int				pcheck[MAX_ARGS_NUMBER];
	int				ocp;
	int				dir_size;
}					t_op_model;

typedef struct		s_file
{
	char			*content;
	char			*name;
	int				fd;
	size_t			size;
}					t_file;

typedef struct		s_op_param
{
	char			*str;
	int				len;
	unsigned long	value;
	char			is_negative;
	unsigned char	error;
	unsigned char	type;
	int				size;
}					t_op_param;

typedef struct		s_op
{
	t_token			*token;
	char			*instruction;
	int				index;
	int				size;
	unsigned char	type;
	int				ocp;
	int				pcount;
	t_op_param		*params;
}					t_op;

typedef struct		s_stock
{
	t_file			dot_s;
	t_file			dot_cor;
	t_header		header;
	t_token			*tokens;
	t_op			*operators;
	int				*tokens_limits;
	int				tokens_count;
	char			**labels;
	int				*labels_pos;
	int				labels_count;
	int				op_count;
	char			run_options;
}					t_stock;

void				get_file_content(t_file *file);
void				init_file_content(t_file *content, char *file_name);
void				clear_file(t_file *file);
t_stock				*get_stock(void);

void				push_token_limit(int limit);
void				tokenize(void);

int					end_of_wsp_token(char *buff);
int					end_of_cmt_token(char *buff);
int					end_of_cmd_token(char *buff);
int					end_of_lbl_or_op_token(char *c);
int					end_of_unknown_token(char *buff);

void				expand_tokens_limits_table(void);
void				push_token_limit(int limit);
void				get_tokens_limits(void);

void				print_tokens(void);
t_op_model			get_op_model(int op_code);

void				get_op_type(t_op *o);
void				create_op_array(void);

void				op_parsing(void);

void				create_label_array(void);
void				check_labels(void);
int					wrong_label_char(char *content);

void				check_commands(void);

void				init(void);
void				error_output(void);

void				analyze_op_param(t_op_param *param);
void				split_params(t_op *op, char *str);
void				get_param_str(t_op *op);

void				calc_op_size(t_op *op);
void				get_labels_and_op_pos(void);
void				calc_label_params(void);
void				build_output_content(void);
void				get_dot_cor_name(void);

void				exit_failure(char *failure_message);
void				exit_success(char *filename);
void				fetch_options(t_stock *stock, int argc, char **argv);
const char			*get_error_message(int token_type, int error);
#endif
