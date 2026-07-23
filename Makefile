# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vicdos-s <vicdos-s@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/07/17 16:04:49 by vicdos-s          #+#    #+#              #
#    Updated: 2026/07/21 17:06:24 by vicdos-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = push_swap

CC          = cc
CFLAGS      = -Wall -Wextra -Werror

LIBFT_DIR   = ./ft_printf/libft
LIBFT       = $(LIBFT_DIR)/libft.a

PRINTF_DIR  = ./ft_printf/
PRINTF      = $(PRINTF_DIR)/libftprintf.a

# Aqui você lista apenas os arquivos .c do seu push_swap em si!
SRCS_DIR    = .
SRCS        = $(SRCS_DIR)/push_swap.c \
              $(SRCS_DIR)/utils.c
OBJS        = $(SRCS:.c=.o)

# Adicionado o include do printf
INCLUDES    = -I $(LIBFT_DIR) -I $(PRINTF_DIR) -I $(PRINTF_DIR)mandatory -I $(SRCS_DIR)

all: $(NAME)

# A regra agora usa o compilador (cc) para linkar os .o e as bibliotecas .a
$(NAME): $(LIBFT) $(PRINTF) $(OBJS)
	$(CC) -g $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) -o $(NAME)
        
$(LIBFT): FORCE
	make -C $(LIBFT_DIR)

# Ensinando o Make a compilar o printf antes do push_swap
$(PRINTF): FORCE
	make -C $(PRINTF_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean
	make -C $(PRINTF_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
	make -C $(PRINTF_DIR) fclean

re: fclean all

teste:
	make
	find . -type f -name "*.o" -delete

FORCE:

.PHONY: all clean fclean re FORCE