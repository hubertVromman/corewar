# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hvromman <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/04 15:22:35 by hvromman          #+#    #+#              #
#    Updated: 2018/10/04 15:22:46 by hvromman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
HEAD = ./includes

IS = ft_isalnum.o ft_isalpha.o ft_isascii.o ft_isdigit.o ft_isprint.o \
ft_isspace.o

STR = ft_strcat.o ft_strchr.o ft_strclr.o ft_strcmp.o ft_strcpy.o \
ft_strdel.o ft_strdup.o ft_strequ.o ft_striter.o ft_striteri.o ft_strjoin.o \
ft_strlcat.o ft_strlen.o ft_strmap.o ft_strmapi.o ft_strncat.o ft_strncmp.o \
ft_strncpy.o ft_strnequ.o ft_strnew.o ft_strnstr.o ft_strrchr.o ft_strsplit.o \
ft_strstr.o ft_strsub.o ft_strtrim.o ft_strnjoin.o ft_indexof.o \
ft_last_indexof.o

LST = ft_lstnew.o ft_lstdelone.o ft_lstdel.o ft_lstadd.o ft_lstiter.o ft_lstmap.o

PUT = ft_putendl.o ft_putendl_fd.o ft_putnbr.o ft_putnbr_fd.o ft_putstr.o \
ft_putstr_fd.o ft_putchar.o ft_putchar_fd.o

MEM = ft_memalloc.o ft_memccpy.o ft_memchr.o ft_memcmp.o ft_bzero.o \
ft_memcpy.o ft_memdel.o ft_memmove.o ft_memset.o ft_memrcpy.o

INT = ft_atoi.o ft_itoa.o ft_min.o ft_max.o ft_pow.o ft_tolower.o ft_toupper.o

TAB = ft_tablen.o ft_free_tab.o

GNL = get_next_line.o

PRINTF = ft_printf.o parser.o parser2.o util.o dispatcher.o dispatcher2.o \
dispatcher3.o color.o color2.o n1.o n2.o float.o float2.o wchar.o char.o \
int.o uint.o octal.o hex.o binary.o other.o

OBJ = $(addprefix ./is/, $(IS)) $(addprefix ./str/, $(STR)) \
$(addprefix ./lst/, $(LST)) $(addprefix ./put/, $(PUT)) \
$(addprefix ./mem/, $(MEM)) $(addprefix ./int/, $(INT)) \
$(addprefix ./tab/, $(TAB)) $(addprefix ./gnl/, $(GNL)) \
$(addprefix ./printf/, $(PRINTF))

RED=\033[0;91m
GREEN=\033[0;92m
CYAN=\033[0;96m
NC=\033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $@ $^
	@echo "$(GREEN)libft compiled$(NC)"

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $< -I $(HEAD)

clean:
	@rm -f $(OBJ)
	@echo "$(RED)libft cleaned$(NC)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)libft fcleaned$(NC)"

re: fclean all
