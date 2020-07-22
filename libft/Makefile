# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 09:47:08 by mbourand          #+#    #+#              #
#    Updated: 2020/07/22 02:50:39 by mbourand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
OPTIONS		= -c -I. -Iprintf -Iget_next_line
FOLDER		= ./
PRINTF		= ./printf/
GNL			= ./get_next_line/
NAME		= libft.a
SRCS =	$(FOLDER)ft_lstnew.c $(FOLDER)ft_lstdelone.c $(FOLDER)ft_lstsize.c $(FOLDER)ft_lstclear.c \
		$(FOLDER)ft_lstlast.c $(FOLDER)ft_lstadd_front.c $(FOLDER)ft_lstadd_back.c $(FOLDER)ft_lstiter.c \
		$(FOLDER)ft_lstmap.c $(FOLDER)malloc_zero.c $(FOLDER)ft_strcmp.c $(FOLDER)ft_strjoinuntil.c \
		$(FOLDER)ft_atoi.c $(FOLDER)ft_strnstr.c $(FOLDER)ft_strlcat.c $(FOLDER)ft_strlcpy.c \
		$(FOLDER)ft_strncmp.c $(FOLDER)ft_strrchr.c $(FOLDER)ft_strchr.c $(FOLDER)ft_tolower.c \
		$(FOLDER)ft_toupper.c $(FOLDER)ft_isprint.c $(FOLDER)ft_isascii.c $(FOLDER)ft_isalnum.c \
		$(FOLDER)ft_isalpha.c $(FOLDER)ft_isdigit.c $(FOLDER)ft_strlen.c $(FOLDER)ft_memcmp.c \
		$(FOLDER)ft_memchr.c $(FOLDER)ft_memmove.c $(FOLDER)ft_memccpy.c $(FOLDER)ft_memcpy.c \
		$(FOLDER)ft_bzero.c $(FOLDER)ft_memset.c $(FOLDER)ft_calloc.c $(FOLDER)ft_strdup.c $(FOLDER)ft_substr.c \
		$(FOLDER)ft_strjoin.c $(FOLDER)ft_strtrim.c $(FOLDER)ft_split.c $(FOLDER)ft_itoa.c $(FOLDER)ft_strmapi.c \
		$(FOLDER)ft_putchar_fd.c $(FOLDER)ft_putendl_fd.c $(FOLDER)ft_putstr_fd.c $(FOLDER)ft_putnbr_fd.c \
		$(FOLDER)ft_min_max.c $(FOLDER)ft_strlenuntil.c $(FOLDER)ft_strnjoin.c $(FOLDER)ft_straddchar.c \
		$(FOLDER)ft_free.c $(FOLDER)ft_lstdelat.c $(FOLDER)ft_lstat.c $(FOLDER)ft_strncpy.c $(FOLDER)ft_strndup.c \
		$(PRINTF)ft_abs.c $(PRINTF)ft_get_arg.c $(PRINTF)ft_numberlen.c $(PRINTF)ft_numberlenl.c $(PRINTF)ft_printf.c \
		$(PRINTF)ft_printutils.c $(PRINTF)ft_putunsignednbr_fd.c $(PRINTF)ft_tobase.c $(PRINTF)print_char.c $(PRINTF)print_hex.c \
		$(PRINTF)print_int.c $(PRINTF)print_pointer.c $(PRINTF)print_string.c $(PRINTF)print_unsigned_int.c \
		$(GNL)get_next_line.c $(GNL)get_next_line_utils.c
OBJECTS		= $(SRCS:.c=.o)

.PHONY: clean all fclean re bonus .c.o

all: $(NAME)

.c.o:
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(OPTIONS) $< -o $(<:.c=.o)

$(NAME): $(OBJECTS)
	@echo "Compiling libft..."
	@ar -rc $(NAME) $(OBJECTS)
	@ranlib $(NAME)

clean:
	@echo "Cleaning libft..."
	@rm -rf $(OBJECTS) $(BONUS)

fclean: clean
	@echo "Full cleaning libft..."
	@rm -rf $(NAME)

re: fclean all
