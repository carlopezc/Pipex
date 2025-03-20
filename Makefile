# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: carlopez <carlopez@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/12 11:09:32 by carlopez          #+#    #+#              #
#    Updated: 2025/03/20 13:18:57 by carlopez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address

NAME = pipex
LIB = pipex.h
SRC = utils/ft_check.c utils/ft_build.c utils/ft_strncmp.c utils/ft_utils.c utils/ft_memcpy.c utils/ft_split.c utils/ft_strdup.c utils/ft_strjoin.c utils/ft_strlen.c utils/ft_substr.c 
OBJ = $(SRC:.c=.o)
MAIN = main/main.c

PRINTFDIR = printf
PRINTF = $(PRINTFDIR)/libftprintf.a
SRC_PRINTF = printf/ft_printf.c printf/ft_print_types.c printf/ft_print_types2.c
LIB_PRINTF = printf/ft_printf.h
MAKEFILE_PRINTF = printf/Makefile

LIGHT_YELLOW	= \033[1;33m
BOLD_GREEN    = \033[1;32m
BOLD_PURPLE   = \033[1;35m
BOLD_CYAN     = \033[1;36m
PINK_LIGHT= \033[38;5;217m
RED_BRIGHT     = \033[38;2;255;0;0m
PINK_FUCHSIA    = \033[38;2;255;20;147m

RESET  = \033[0m

all:
	@echo "$(PINK_FUCHSIA)\n	 MAKING PIPEX ... $(RESET)"
	@$(MAKE) --no-print-directory $(NAME)

$(NAME): $(MAIN) $(OBJ) $(PRINTF)
	@echo "$(BOLD_CYAN)\nCompiling program...$(RESET)"
	$(CC) $(CFLAGS) $(MAIN) $(OBJ) $(PRINTF) -o $(NAME)
	@echo "$(BOLD_CYAN)\n!Compilation completed, $(LIGHT_YELLOW)pipex🚀$(BOLD_CYAN) ready to be used!\n$(RESET)"

%.o: %.c $(LIB) Makefile 
	@echo "$(PINK_LIGHT)🡲 Creating object...$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

$(PRINTF): $(SRC_PRINTF) $(LIB_PRINTF) $(MAKEFILE_PRINTF) Makefile $(LIB)
	@echo "$(BOLD_PURPLE)\nCompiling printf...$(RESET)"
	@$(MAKE) -C $(PRINTFDIR)

clean:
	@echo "$(RED_BRIGHT)\nThrowing object files of pipex to 🗑️$(RESET)"
	@rm -f $(OBJ)
	@echo "$(RED_BRIGHT)Throwing object files of Printf to 🗑️$(RESET)"
	@$(MAKE) --silent -C $(PRINTFDIR) clean

fclean: clean
	@echo "$(RED_BRIGHT)Destroying printf 💥$(RESET)"
	@$(MAKE) --silent -C $(PRINTFDIR) fclean
	@echo "$(RED_BRIGHT)Destroying program 💥$(RESET)"
	@rm -f $(NAME)
	@echo "\n$(BOLD_GREEN) Bye bye 👋 $(RESET)\n"

re: fclean all

.PHONY: all clean fclean re
