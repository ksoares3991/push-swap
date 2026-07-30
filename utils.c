/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicdos-s <vicdos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 16:36:14 by vicdos-s          #+#    #+#             */
/*   Updated: 2026/07/30 13:15:15 by vicdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void print_error_debug(t_state *state)
{
    // 1. O print de erro obrigatório do push_swap na saída de erro (stderr)
    ft_putstr_fd("Error\n", 2);

    // 2. Início do Dump de Debug
    printf("\n============================================\n");
    printf("              CRASH DUMP (DEBUG)            \n");
    printf("============================================\n");

    if (!state)
    {
        printf("[!] t_state é NULL. O erro ocorreu antes da alocação do estado.\n");
        exit(1);
    }

    // --- VARIÁVEIS GERAIS ---
    printf("\n[1. STATE CONFIGS]\n");
    printf("  Strategy: %d\n", state->strategy);
    printf("  Bench Mode: %d\n", state->bench_mode);
    printf("  Print Mode: %d\n", state->print_mode);
    printf("  Total Flags: %d\n", state->total_flags);
    printf("  Total Elements: %d\n", state->total_elements);

    // --- STACKS ---
    printf("\n[2. STACKS]\n");
    
    // Stack A
    if (state->a)
    {
        printf("  Stack A (size: %d): [HEAD] ", state->a->size);
        t_node *curr_a = state->a->head;
        while (curr_a)
        {
            printf("%d ", curr_a->number);
            curr_a = curr_a->next;
            // Prevenção de loop infinito se a sua lista for circular
            if (curr_a == state->a->head) break; 
        }
        printf("[TAIL]\n");
    }
    else
        printf("  Stack A: NULL\n");

    // Stack B
    if (state->b)
    {
        printf("  Stack B (size: %d): [HEAD] ", state->b->size);
        t_node *curr_b = state->b->head;
        while (curr_b)
        {
            printf("%d ", curr_b->number);
            curr_b = curr_b->next;
            // Prevenção de loop infinito se a sua lista for circular
            if (curr_b == state->b->head) break;
        }
        printf("[TAIL]\n");
    }
    else
        printf("  Stack B: NULL\n");

    // --- BENCHMARK ---
    printf("\n[3. BENCHMARK / OP COUNTS]\n");
    if (state->bench)
    {
        char *op_names[] = {"SA", "SB", "SS", "RA", "RB", "RR", "RRA", "RRB", "RRR", "PA", "PB", "TOTAL"};
        
        for (int i = 0; i <= TOTAL; i++)
        {
            printf("  %-5s: %d\n", op_names[i], state->bench->count_op[i]);
        }
    }
    else
    {
        printf("  Bench: NULL\n");
    }

    printf("============================================\n\n");
    exit(1);
}

int is_int(long n)
{
	if(n > 2147483647 || n < -2147483648)
		{
			ft_putstr_fd("Error\n", 2);
			exit(1);
		}
	return (1);
}
void print_error()
{
	ft_putstr_fd("Error\n", 2);
	exit(1);
}
int ft_isnumber(char *s)
{
    long i;

    i = 0;
	(void)s;
	if (search_flag(s))
		return (0);
    if (!s || s[0] == '\0')
    	print_error();
    if (s[i] == '-')
        i++;
    if (!s[i])
        print_error();
    while (s[i])
    {
        if (!ft_isdigit(s[i]))
            print_error();
        i++;
    }
    if (!is_int(ft_atol(s)))
        print_error();

    return (1);
}

long	ft_atol(char *s)
{
	long	i;
	long	result;
	int		is_negative;

	is_negative = 0;
	i = 0;
	while ((s[i] == 32) || ((s[i] >= 9) && (s[i] <= 13)))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			is_negative = 1;
		i++;
	}
	result = 0;
	while (ft_isdigit(s[i]))
	{
		result = ((result * 10) + (s[i] - '0'));
		i++;
	}
	if (is_negative)
		result = result * -1;
	return (result);
}

int ft_strcmp(const char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i])||(s2[i]))
	{
		if ((s1[i]) != (s2[i]))
			return (0);
		else if ((s1[i]) == (s2[i]) && ((s1[i + 1]) || (s2[i + 1])))
			i++;
		else if ((s1[i]) == (s2[i]) && (!s1[i + 1]) == (!s2[i + 1]))
			return (1);
	}
	return (0);
}
// int ft_isaflag(char *av)
// {
// 	int	i;

// 	i = 0;
	
// }