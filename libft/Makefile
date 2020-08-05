# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 09:47:08 by mbourand          #+#    #+#              #
#    Updated: 2020/08/04 04:05:35 by mbourand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
INCS		= -I. -Iprintf -Iget_next_line
SRCS_PATH	= ./
PRINTF		= ./printf/
GNL			= ./get_next_line/
NAME		= libft.a
SRCS_NAME	=	ft_lstnew.c ft_lstdelone.c ft_lstsize.c ft_lstclear.c ft_lstlast.c ft_lstadd_front.c \
				ft_lstadd_back.c ft_lstiter.c ft_lstmap.c malloc_zero.c ft_strcmp.c ft_strjoinuntil.c \
				ft_atoi.c ft_strnstr.c ft_strlcat.c ft_strlcpy.c ft_strncmp.c ft_strrchr.c ft_strchr.c \
				ft_tolower.c ft_toupper.c ft_isprint.c ft_isascii.c ft_isalnum.c ft_isalpha.c ft_isdigit.c \
				ft_strlen.c ft_memcmp.c ft_memchr.c ft_memmove.c ft_memccpy.c ft_memcpy.c ft_bzero.c \
				ft_memset.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
				ft_itoa.c ft_strmapi.c ft_putchar_fd.c ft_putendl_fd.c ft_putstr_fd.c ft_putnbr_fd.c \
				ft_min_max.c ft_strlenuntil.c ft_strnjoin.c ft_straddchar.c ft_strcut.c ft_strcpy.c \
				ft_strnew.c ft_memdel.c ft_free.c ft_lstdelat.c ft_lstat.c ft_strncpy.c ft_strndup.c \
				ft_lstreplace.c ft_numlen.c

GNL_NAME	=	get_next_line.c get_next_line_utils.c

PRINTF_NAME	=	ft_printf.c ft_printf_conv.c ft_printf_conv_int.c ft_printf_conv_int_utils.c \
				ft_printf_conv_int_hh.c ft_printf_conv_int_hh_utils.c ft_printf_conv_int_ll.c \
				ft_printf_conv_int_ll_utils.c ft_printf_conv_int_h.c ft_printf_conv_int_h_utils.c \
				ft_printf_conv_int_l.c ft_printf_conv_int_l_utils.c ft_printf_conv_str.c \
				ft_printf_conv_ptr.c ft_printf_conv_uns.c ft_printf_conv_uns_utils.c \
				ft_printf_conv_uns_hh.c ft_printf_conv_uns_hh_utils.c ft_printf_conv_uns_ll.c \
				ft_printf_conv_uns_ll_utils.c ft_printf_conv_uns_h.c ft_printf_conv_uns_h_utils.c \
				ft_printf_conv_uns_l.c ft_printf_conv_uns_l_utils.c ft_printf_conv_n.c \
				ft_printf_utils.c ft_dprintf.c

PRINTF_OBJS_PATH = printf/objs/
GNL_OBJS_PATH = get_next_line/objs/

SRCS	= $(addprefix $(SRCS_PATH), $(SRCS_NAME))

OBJS_PATH = ./objs/
OBJS	= $(addprefix $(OBJS_PATH), $(SRCS_NAME:.c=.o))

ALL_OBJS = $(addprefix $(OBJS_PATH), $(SRCS_NAME:.c=.o))
ALL_OBJS += $(addprefix $(GNL_OBJS_PATH), $(GNL_NAME:.c=.o))
ALL_OBJS += $(addprefix $(PRINTF_OBJS_PATH), $(PRINTF_NAME:.c=.o))

DEF= \033[0m
RED= \033[31;1m
GRN= \033[32;1m
YEL= \033[33;1m

.PHONY: all re clean fclean

all: compile

$(NAME): $(OBJS)
	@echo "$(RED)[libft]$(DEF) Compiling..."
	@ar -rcs $(NAME) $(ALL_OBJS)
	@echo "$(RED)[libft]$(DEF) Compilation $(GRN)[OK]$(DEF)"

compile:
	@$(MAKE) -C get_next_line SRCS_NAME="$(GNL_NAME)" | sed '/^make\[/d'
	@$(MAKE) -C printf SRCS_NAME="$(PRINTF_NAME)" | sed '/^make\[/d'
	@$(MAKE) $(NAME) | sed '/^make\[/d'

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	@mkdir $(OBJS_PATH) 2> /dev/null || true
	@echo "$(RED)[libft]$(DEF) Compiling $<"
	@$(CC) $(CFLAGS) $(INCS) -o $@ -c $<

clean:
	@$(MAKE) -C printf clean | sed '/^make\[/d'
	@$(MAKE) -C get_next_line clean | sed '/^make\[/d'
	@rm -rf $(OBJS_PATH)
	@echo "$(RED)[libft]$(DEF) Cleaning $(GRN)[OK]$(DEF)"

fclean: clean
	@$(MAKE) -C printf fclean | sed '/^make\[/d'
	@$(MAKE) -C get_next_line fclean | sed '/^make\[/d'
	@rm -rf $(NAME)
	@echo "$(RED)[libft]$(DEF) Full Cleaning $(GRN)[OK]$(DEF)"

re: fclean all
