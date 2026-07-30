# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vicdos-s <vicdos-s@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/07/17 16:04:49 by vicdos-s          #+#    #+#              #
#    Updated: 2026/07/30 18:22:10 by vicdos-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = push_swap

CC          = cc
CFLAGS      = -Wall -Wextra -Werror

LIBFT_DIR   = ./ft_printf/libft
LIBFT       = $(LIBFT_DIR)/libft.a

PRINTF_DIR  = ./ft_printf/
PRINTF      = $(PRINTF_DIR)/libftprintf.a

SRCS_DIR    = .
SRCS        = $(SRCS_DIR)/push_swap.c \
              $(SRCS_DIR)/utils.c \
			  $(SRCS_DIR)/init.c \
			  $(SRCS_DIR)/parser_utils.c\
              operations/push.c \
              operations/rev_rotate.c \
              operations/rotate.c \
              operations/swap.c \
              algorithms/selection_sort.c \

OBJS        = $(SRCS:.c=.o)

INCLUDES    = -I $(LIBFT_DIR) -I $(PRINTF_DIR) -I $(PRINTF_DIR)mandatory -I $(SRCS_DIR)

all: $(NAME)

$(NAME): $(LIBFT) $(PRINTF) $(OBJS)
	$(CC) -g $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) -o $(NAME)
        
$(LIBFT): FORCE
	make -C $(LIBFT_DIR)

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