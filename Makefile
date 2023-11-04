# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/13 11:52:25 by karisti-          #+#    #+#              #
#    Updated: 2023/11/04 15:04:49 by karisti-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project compilation files and directories

NAME	=	minishell

SRCSFD	=	srcs/
OBJSFD	=	objs/
HDR_INC	=	-I./includes/minishell.h

PARSERFD = $(SRCSFD)parser/
EXECFD = $(SRCSFD)exec/
BUILTINSFD = $(SRCSFD)builtins/
UTILSFD = $(SRCSFD)utils/

SRCS	=	$(SRCSFD)main.c						\
			$(SRCSFD)signals.c					\
			$(UTILSFD)init_shell.c				\
			$(SRCSFD)prompt.c					\
			$(PARSERFD)parser.c					\
			$(PARSERFD)check_syntax.c			\
			$(PARSERFD)quotes.c					\
			$(PARSERFD)redirections.c			\
			$(PARSERFD)heredoc.c				\
			$(PARSERFD)cmd_options.c			\
			$(PARSERFD)tokens.c					\
			$(UTILSFD)cmd_table.c				\
			$(UTILSFD)files.c					\
			$(UTILSFD)envs.c					\
			$(PARSERFD)expand_envs.c			\
			$(EXECFD)exec.c						\
			$(EXECFD)exec1.c					\
			$(EXECFD)pipes.c					\
			$(EXECFD)redirections.c				\
			$(UTILSFD)ft_split_no_quotes.c		\
			$(UTILSFD)ft_strjoin_free.c			\
			$(UTILSFD)ft_split_two.c			\
			$(UTILSFD)ft_isalnum_underscore.c	\
			$(UTILSFD)errors.c					\
			$(UTILSFD)str_is_number.c			\
			$(UTILSFD)ft_strstrlen.c			\
			$(BUILTINSFD)ft_pwd.c				\
			$(BUILTINSFD)ft_cd.c				\
			$(BUILTINSFD)ft_env.c				\
			$(BUILTINSFD)ft_export.c			\
			$(BUILTINSFD)ft_unset.c				\
			$(BUILTINSFD)ft_echo.c				\
			$(BUILTINSFD)ft_exit.c			

OBJS 	=	$(patsubst $(SRCSFD)%.c, $(OBJSFD)%.o, $(SRCS))
# # # # # # # # # # # # # # # # # # # # # # # # # # # # #

# Libraries
LIBFT	=	libft/bin/libft.a
RL_LIB	=	-L/usr/local/opt/readline/lib #-L/Users/$(USER)/.brew/opt/readline/lib
RL_INC	=	-I/usr/local/opt/readline/include#-I/Users/$(USER)/.brew/opt/readline/include
RL		=	$(RL_LIB) $(RL_INC) -lreadline
# # # # # # # # # # # # # # # # # # # # # # # # # # # # #

# Compilation
COMP	=	gcc
CFLAGS	=	-Wall -Wextra -Werror
# # # # # # # # # # # # # # # # # # # # # # # # # # # # #

# Colors
RED		=	\033[0;31m
GREEN	=	\033[0;32m
NONE	=	\033[0m
# # # # # # # # # # # # # # # # # # # # # # # # # # # # #

all: check_libft project $(NAME)
	@echo "... project ready"

check_libft: $(LIBFT)

project:
	@echo "Checking project ..."

projectb:
	@echo "Checking project bonus ..."

$(LIBFT):
	@make -C libft extras

$(OBJSFD):
	@mkdir $@
	@mkdir -p $(OBJSFD)parser
	@mkdir -p $(OBJSFD)exec
	@mkdir -p $(OBJSFD)builtins
	@mkdir -p $(OBJSFD)utils
	@echo "\t[ $(GREEN)✔$(NONE) ] $@ directories"

$(OBJSFD)%.o: $(SRCSFD)%.c
	@$(COMP) $(CFLAGS) $(HDR_INC) $(RL_INC) -o $@ -c $<
	@echo "\t[ $(GREEN)✔$(NONE) ] $@ object"

$(NAME): $(OBJSFD) $(OBJS)
	@$(COMP) $(CFLAGS) $(OBJS) $(RL) $(LIBFT) -o $@
	@echo "\t[ $(GREEN)✔$(NONE) ] $@ executable"

bonus: check_libft projectb $(NAME)
	@echo "... project bonus ready"

clean:
	@echo "Cleaning project ..."
	@/bin/rm -rf $(OBJSFD)
	@/bin/rm -rf $(SRCSFD)/.heredoc.tmp
	@echo "\t[ $(RED)✗$(NONE) ] Objects directory"
	@make -C ./libft clean

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "\t[ $(RED)✗$(NONE) ] $(NAME) executable"
	@make -C ./libft fclean

re: fclean all

.PHONY: check_libft project all clean fclean re
