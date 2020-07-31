# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nforay <nforay@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/31 16:42:25 by nforay            #+#    #+#              #
#    Updated: 2020/07/31 17:33:12 by nforay           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= gcc

ifeq ($(DB),1)
    CFLAGS	=  -g3 -Wall -Wextra -Werror
else
	CFLAGS	=  -Wall -Wextra -Werror
endif

INCS			= -I. -I.. -I../get_next_line

SRCS_PATH	= ./srcs/
SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))

OBJS_PATH	= ./objs/
OBJS		= $(addprefix $(OBJS_PATH), $(SRCS_NAME:.c=.o))

DEF= \033[0m
RED= \033[31;1m
GRN= \033[32;1m
YEL= \033[33;1m

all: $(OBJS)
	@echo -n "" > /dev/null

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	@mkdir $(OBJS_PATH) 2> /dev/null || true
	@echo "$(RED)[ft_printf]$(DEF) Compiling $<"
	@$(CC) $(CFLAGS) $(INCS) -o $@ -c $<

clean:
	@rm -rf $(OBJS_PATH)
	@echo "$(RED)[ft_printf] $(DEF)Cleaning $(GRN)[OK]$(DEF)"

fclean: clean

re: fclean all

.PHONY: all clean fclean re
