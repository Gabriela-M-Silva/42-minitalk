# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/29 02:00:21 by gde-mora          #+#    #+#              #
#    Updated: 2022/11/22 06:21:11 by gde-mora         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_CLIENT = client

SRC_CLIENT = client.c finish_error.c

OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

NAME_SERVER = server

SRC_SERVER = server.c finish_error.c

OBJ_SERVER = $(SRC_SERVER:.c=.o)

LIBFT_A = ./libft/libft.a

HEADER = minitalk.h

CCFLAGS = -Wall -Wextra -Werror

RM = rm -f

all: $(NAME_CLIENT) $(NAME_SERVER)

.c.o:
	cc $(CCFLAGS) -c $< -o $(<:.c=.o) 

$(LIBFT_A):
	make -C libft

$(NAME_CLIENT): $(OBJ_CLIENT) $(HEADER) $(LIBFT_A)
	cc $(CCFLAGS) -o $(NAME_CLIENT) $(OBJ_CLIENT) $(LIBFT_A)

$(NAME_SERVER): $(OBJ_SERVER) $(HEADER) $(LIBFT_A)
	cc $(CCFLAGS) -o $(NAME_SERVER) $(OBJ_SERVER) $(LIBFT_A)

clean:
	$(RM) $(OBJ_CLIENT)
	$(RM) $(OBJ_SERVER)
	make clean -C libft

fclean: clean
	$(RM) $(NAME_CLIENT)
	$(RM) $(NAME_SERVER)
	$(RM) $(LIBFT_A)

re: fclean all

.PHONY: all clean fclean re
