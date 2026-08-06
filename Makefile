NAME        = push_swap

CC          = cc
CFLAGS      = -Wall -Wextra -Werror

LIBFT_DIR   = ./ft_printf/libft
LIBFT       = $(LIBFT_DIR)/libft.a

PRINTF_DIR  = ./ft_printf/
PRINTF      = $(PRINTF_DIR)/libftprintf.a

SRCS        = src/main/push_swap.c \
			  src/main/init.c \
			  src/main/utils.c \
			  src/parsing/parser_utils.c \
			  src/parsing/flag_utils.c \
			  src/parsing/compare_utils.c \
			  src/operations/op_push.c \
			  src/operations/op_swap.c \
			  src/operations/op_rotate.c \
			  src/operations/op_rev_rotate.c \
			  src/algorithms/algo_simple_sort.c \
			  src/algorithms/algo_medium_sort.c \
			  src/algorithms/algo_medium_sort_utils.c \
			  src/algorithms/algo_complex_sort.c \
			  src/algorithms/algo_sort_utils.c \
			  src/bench/bench.c

OBJS        = $(SRCS:.c=.o)

INCLUDES    = -I $(LIBFT_DIR) -I $(PRINTF_DIR) -I $(PRINTF_DIR)mandatory -I include

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

makeclean:
	make
	find . -type f -name "*.o" -delete

FORCE:

.PHONY: all clean fclean re FORCE
