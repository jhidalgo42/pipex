# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhidalgo <jhidalgo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/24 16:06:46 by jhidalgo          #+#    #+#              #
#    Updated: 2023/04/27 10:03:50 by jhidalgo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Libraries 
GNL = gnl/gnl.a
LIBFT = libft/libft.a
FT_PRINTF = ft_printf/ft_printf.a


NAME = pipex

all: $(NAME)
  
# Files 
SRCS = main.c errors.c 	\
	   check_input.c	\
	   utils.c			\
	   pipex.c			\
	   fd_control.c		\
	   cmd_control.c

#	Compilation
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address
OBJS = $(SRCS:.c=.o)
RM = rm -f

### Compiling Libraries ###


$(GNL):
	@make -C gnl
$(LIBFT):
	@make -C libft
$(FT_PRINTF):
	@make -C ft_printf



$(NAME):$(OBJS)  $(GNL) $(LIBFT) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(OBJS) $(GNL) $(LIBFT) $(FT_PRINTF) -o $(NAME)


clean:
	@make clean -C libft 
	@make clean -C gnl 
	@make clean -C ft_printf
	$(RM) $(OBJS)

fclean:	clean
	@make fclean -C libft 
	@make fclean -C gnl
	@make fclean -C ft_printf
	$(RM) $(NAME)

re: fclean all

.PHONY:	all, clean, fclean,  re