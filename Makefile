# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hvromman <hvromman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/05 15:14:07 by hvromman          #+#    #+#              #
#    Updated: 2019/09/10 02:35:03 by sofchami         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COR = corewar
ASM = asm

CFLAGS = -Wall -Wextra -Werror
SRCS = srcs/
HEAD = includes/
LIB = libft/

FILE = common.h op.h
H = $(addprefix $(HEAD), $(FILE))
FILES = op.o util.o
OBJ = $(addprefix $(SRCS), $(FILES))

COR_DIR = core/
COR_FILE = corewar.h
COR_H = $(addprefix $(COR_DIR), $(addprefix $(HEAD), $(COR_FILE)))
COR_FILES = main.o error.o exit.o util.o arguments.o champ_instance.o lecteur.o \
visu.o print_info.o util_visu.o thread.o init.o init_visu.o ray.o proces.o init_frame.o \
io_arena.o print_visu.o filler.o buffer_visu.o create_lines.o
COR_OBJ = $(addprefix $(COR_DIR), $(addprefix $(SRCS), $(COR_FILES)))

OP_DIR = operations/
OP_FILES = add.o st.o sub.o aff.o live.o lfork.o fork.o zjmp.o ld.o st.o and.o or.o xor.o ldi.o sti.o lld.o lldi.o
OP_OBJ = $(addprefix $(COR_DIR), $(addprefix $(SRCS), $(addprefix $(OP_DIR), $(OP_FILES))))

ASM_DIR = asem/
ASM_FILE = asm.h
ASM_H = $(addprefix $(ASM_DIR), $(addprefix $(HEAD), $(ASM_FILE)))
ASM_FILES = main.o error.o exit.o io.o util.o util2.o header.o body.o label.o write_instr.o parse_line_info.o operation.o
ASM_OBJ = $(addprefix $(ASM_DIR), $(addprefix $(SRCS), $(ASM_FILES)))

SANITIZE = -fsanitize=address

RED=\033[0;91m
GREEN=\033[0;92m
CYAN=\033[0;96m
NC=\033[0m

all: $(COR) $(ASM)

$(COR): $(OP_OBJ) $(COR_OBJ) $(OBJ)
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
	@rm -f $(OBJ) $(COR_OBJ) $(ASM_OBJ) $(OP_OBJ)
	@echo "$(RED)$(ASM) and $(COR) cleaned$(NC)"

fclean: clean
	@rm -f $(ASM) $(COR) debug_asm debug_corewar
	@make -C $(LIB) fclean
	@echo "$(RED)$(ASM) and $(COR) fcleaned$(NC)"

debug_asm: $(ASM_OBJ) $(OBJ)
	@make -C $(LIB)
	@$(CC) -o $@ $^ -L$(LIB) -lft $(SANITIZE)
	@echo "$@ compiled$(NC)"

debug_corewar: $(OP_OBJ) $(COR_OBJ) $(OBJ)
	@make -C $(LIB)
	@$(CC) -o $@ $^ -L$(LIB) -lft $(SANITIZE)
	@echo "$@ compiled$(NC)"

re: fclean all
