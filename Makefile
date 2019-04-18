# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hvromman <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/05 15:14:07 by hvromman          #+#    #+#              #
#    Updated: 2019/04/05 15:14:10 by hvromman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COR = corewar
ASM = asm

CC = gcc
CFLAGS = -Wall -Wextra -Werror -O3
SRCS = srcs/
HEAD = includes/
LIB = libft/

FILE = common.h op.h
H = $(addprefix $(HEAD), $(FILE))
FILES = op.o
OBJ = $(addprefix $(SRCS), $(FILES))

COR_DIR = core/
COR_FILE = corewar.h
COR_H = $(addprefix $(COR_DIR), $(addprefix $(HEAD), $(COR_FILE)))
COR_FILES = main.o
COR_OBJ = $(addprefix $(COR_DIR), $(addprefix $(SRCS), $(COR_FILES)))

ASM_DIR = asem/
ASM_FILE = asm.h
ASM_H = $(addprefix $(ASM_DIR), $(addprefix $(HEAD), $(ASM_FILE)))
ASM_FILES = main.o error.o exit.o io.o util.o header.o body.o
ASM_OBJ = $(addprefix $(ASM_DIR), $(addprefix $(SRCS), $(ASM_FILES)))

SANITIZE = -fsanitize=address

RED=\033[0;91m
GREEN=\033[0;92m
CYAN=\033[0;96m
NC=\033[0m

all: $(COR) $(ASM)

$(COR): $(COR_OBJ) $(OBJ)
	@make -C $(LIB)
	@$(CC) $(CFLAGS) -o $@ $^ -L$(LIB) -lft
	@echo "$(GREEN)$@ compiled$(NC)"

$(ASM): $(ASM_OBJ) $(OBJ)
	@make -C $(LIB)
	@$(CC) $(CFLAGS) -o $@ $^ -L$(LIB) -lft
	@echo "$(GREEN)$@ compiled$(NC)"

%.o: %.c $(H) $(COR_H) $(ASM_H)
	@$(CC) $(CFLAGS) -c -o $@ $< -I $(HEAD) -I $(LIB)$(HEAD) -I $(COR_DIR)$(HEAD) -I $(ASM_DIR)$(HEAD)

clean:
	@make -C $(LIB) clean
	@rm -f $(OBJ) $(COR_OBJ) $(ASM_OBJ)
	@echo "$(RED)$(ASM) and $(COR) cleaned$(NC)"

fclean: clean
	@rm -f $(ASM) $(COR)
	@make -C $(LIB) fclean
	@echo "$(RED)$(ASM) and $(COR) fcleaned$(NC)"

debug_asm: $(ASM_OBJ) $(OBJ)
	@make -C $(LIB)
	@$(CC) $(CFLAGS) -o $@ $^ -L$(LIB) -lft $(SANITIZE)
	@echo "$@ compiled$(NC)"

re: fclean all
