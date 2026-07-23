# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vicdos-s <vicdos-s@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/15 13:07:58 by vicdos-s          #+#    #+#              #
#    Updated: 2026/06/24 13:49:56 by vicdos-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a

SRCS_DIR	= ./mandatory
SRCS		= $(SRCS_DIR)/ft_printf.c \
			$(SRCS_DIR)/handlers_str.c \
			$(SRCS_DIR)/handlers_nbr.c \
			$(SRCS_DIR)/handlers_hex.c

OBJS		= $(SRCS:.c=.o)

INCLUDES	= -I $(LIBFT_DIR) -I$(SRCS_DIR)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
		cp $(LIBFT) $(NAME)
		ar rcs $(NAME) $(OBJS)
		
$(LIBFT): FORCE
	make -C $(LIBFT_DIR)

%.o: %.c
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
		rm -f $(NAME)
		make -C $(LIBFT_DIR) fclean

re: fclean all

FORCE:

.PHONY: all clean fclean re