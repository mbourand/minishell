# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nforay <nforay@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 09:47:08 by mbourand          #+#    #+#              #
#    Updated: 2020/07/31 17:33:22 by nforay           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
INCS		= -I.. -I../printf -I.
SRCS_PATH	= ./

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))

OBJS_PATH	= ./objs/
OBJS		= $(addprefix $(OBJS_PATH), $(SRCS_NAME:.c=.o))

DEF= \033[0m
RED= \033[31;1m
GRN= \033[32;1m
YEL= \033[33;1m

.PHONY: all re clean fclean

all: $(OBJS)
	@echo -n "" > /dev/null

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	@mkdir $(OBJS_PATH) 2> /dev/null || true
	@echo "$(RED)[gnl]$(DEF) Compiling $<"
	@$(CC) $(CFLAGS) $(INCS) -o $@ -c $<

clean:
	@rm -rf $(OBJS_PATH)
	@echo "$(RED)[gnl]$(DEF) Cleaning $(GRN)[OK]$(DEF)"

fclean: clean

re: fclean all