# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: bodibon <marvin@le-101.fr>                 +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/10/31 15:47:43 by bodibon      #+#   ##    ##    #+#        #
#    Updated: 2019/01/25 12:16:29 by bodibon     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME_1 = corewar

LIB = libft.a
LIB_ASM = lib_asm.a
LDIR = ./libft/

DIR_1 = ./vm/
SDIR_1 = $(addprefix $(DIR_1), srcs/)
IDIR_1 = $(addprefix $(DIR_1), includes/)
ODIR_1 = $(addprefix $(DIR_1), objects/)
SRCS_1 = $(addsuffix .c, champ_tools errors errors2 get_options_01 \
		get_options_02 init_champ launch_champ mem_tools op ope1 ope2 ope3 \
		ope4 operateurs parse_champ print_info proc_tools proc_tools2 \
		size_and_nega verb_cycle verbose verbose_ope1 verbose_ope2 \
		verbose_ope3 verbose_ope4 visualizer_01 visualizer_02 visualizer_03 \
		visualizer_04)
HEADERS_1 = $(addsuffix .h, op_vm)
OBJ_1 = $(addprefix $(ODIR_1), $(SRCS_1:.c=.o))

NAME_2 = asm

DIR_2 = ./compiler/
SDIR_2 = $(addprefix $(DIR_2), srcs/)
IDIR_2 = $(addprefix $(DIR_2), includes/)
ODIR_2 = $(addprefix $(DIR_2), objects/)
SRCS_2 = $(addsuffix .c, build_output_content commands error_messages \
		error_verbose exit get_dot_cor_name get_file_content init labels \
		labels_value main op_model op_params_analysis op_parsing op_size \
		print_tokens stock t_file tokenization tokens_end tokens_limits)
HEADERS_2 = $(addsuffix .h, asm)
OBJ_2 = $(addprefix $(ODIR_2), $(SRCS_2:.c=.o))

CC = gcc
CFLAGS_11 = -Wall -Wextra -Werror
CFLAGS_12 = -lncurses -Wall -Wextra -Werror
CFLAGS_2 = -Wall -Wextra -Werror

all: $(LIB) $(NAME_1) $(NAME_2)

$(NAME_1): $(addprefix $(LDIR),$(LIB)) $(OBJ_1)
	$(CC) $(addprefix $(LDIR), $(LIB)) $(CFLAGS_12) $(OBJ_1) -o $@

$(LIB):
	@make -C $(LDIR)

$(addprefix $(LDIR),$(LIB)): $(LIB)

$(addprefix $(ODIR_1), %.o): $(addprefix $(SDIR_1), %.c) $(addprefix $(IDIR_1), $(HEADERS_1))
	mkdir -p $(ODIR_1)
	$(CC) -I $(IDIR_1) $(CFLAGS_11) -c $< -o $@

$(NAME_2): $(addprefix $(LDIR), $(LIB_ASM)) $(OBJ_2)
	$(CC) $(addprefix $(LDIR), $(LIB_ASM)) $(CFLAGS_2) $(OBJ_2) -o $@

$(addprefix $(LDIR), $(LIB_ASM)): $(LIB)

$(addprefix $(ODIR_2), %.o): $(addprefix $(SDIR_2), %.c) $(addprefix $(IDIR_2), $(HEADERS_2))
	mkdir -p $(ODIR_2)
	$(CC) -I $(IDIR_2) $(CFLAGS_2) -c $< -o $@

clean:
	rm -rf $(ODIR_1)
	rm -rf $(ODIR_2)
	make -C $(LDIR) clean

fclean: clean
	rm -f $(NAME_1) $(NAME_2)
	make -C $(LDIR) fclean

re: fclean all
