# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: bodibon <marvin@le-101.fr>                 +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/01/17 15:12:55 by bodibon      #+#   ##    ##    #+#        #
#    Updated: 2019/01/24 21:02:23 by bodibon     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = lib_asm.a

SRCS = $(addsuffix .c, ft_atoi ft_atou ft_bzero ft_charpos ft_chartotrim \
	ft_countchar ft_intlen_base ft_inttochar ft_isalldigit ft_isalnum \
	ft_isalpha ft_isascii ft_isdigit ft_isprint ft_itoa ft_itoa_base \
	ft_lstadd ft_lstdel ft_lstdelone ft_lstiter ft_lstmap ft_lstnew \
	ft_memalloc ft_memccpy ft_memchr ft_memcmp ft_memcpy ft_memdel ft_memmove \
	ft_memset ft_putchar ft_putchar_fd ft_putendl ft_putendl_fd ft_putnbr \
	ft_putnbr_base ft_putnbr_fd ft_putstr ft_putstr_fd ft_puttab2d ft_strcat \
	ft_strchr ft_strclr ft_strcmp ft_strcpy ft_strdel ft_strdup ft_strequ \
	ft_strisalnum ft_striter ft_striteri ft_strjoin ft_strjoinfree ft_strlcat \
	ft_strlen ft_strmap ft_strmapi ft_strncat ft_strncmp ft_strncpy \
	ft_strndup ft_strnequ ft_strnew ft_strnstr ft_strrchr ft_strsplit \
	ft_strstr ft_strsub ft_strtrim ft_tolower ft_toupper ft_voidrev \
	ft_voidswap gc gc_alloc gc_free get_next_line)

DIR = ../
SDIR = ./srcs/
IDIR = ./includes/

OBJ = $(SRCS:.c=.o)

HEADER = $(addsuffix .h, libft)

CC = gcc
AR = ar
ARFLAGS = -rc

CFLAGS = -Wall -Wextra -Werror

all: $(addprefix $(DIR), $(NAME))

$(addprefix $(DIR), $(NAME)): $(OBJ)
	$(AR) $(ARFLAGS) $@ $(OBJ)

%.o: $(addprefix $(SDIR), %.c) $(addprefix $(IDIR), $(HEADER))
	$(CC) -I $(IDIR) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(addprefix $(DIR), $(NAME))

re: fclean all
