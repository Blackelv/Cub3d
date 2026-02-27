/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel <kel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 00:23:02 by kel               #+#    #+#             */
/*   Updated: 2025/02/10 17:54:20 by kel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include "../includes/libft.h"

// checks if argc is 2 or more
typedef enum flags
{
	MORE_ARGC,
	ONE_ARGC,
}		t_flags;

typedef struct s_list_s
{
	int				val;
	int				index;
	int				cost_a;
	int				cost_b;
	int				position;
	int				target_node;
	struct s_list_s	*next;
}					t_s_list;

typedef struct push_swap
{
	t_s_list	*current;
	t_s_list	*cur_val;
	int			i;
	int			j;
	int			pos;
	int			size;
	int			sign;
	int			value;
	int			zeros;
	int			new_ac;
	int			*local_a;
	int			*local_b;
	int			smallest;
	char		**onearg;
	long		n;
}			t_variables;

/*******************************************************************************
*							Calculate_moves.c	  						       *
*******************************************************************************/
int			max_element(t_s_list *stack, int *index);
int			min_element(t_s_list *stack, int *index);
int			find_next_larger(t_s_list *stack_a, int b);
int			calculate_mov_b(int index, int size);
int			calculate_mov_a(t_s_list *stack_a, int b, int size_a);
/*******************************************************************************
*						Free_exit_error.c	  							       *
*******************************************************************************/
void		ft_free_st(char **mtx);
void		ft_free_stack(t_s_list *stack);
void		ft_error_exit(char **av, t_s_list **stack_a, t_flags mode);
/*******************************************************************************
*						Full_sorter.c	 	 							       *
*******************************************************************************/
void		settle_stack(t_s_list **stack_a);
int			fetch_moves(t_s_list **s_a, t_s_list **s_b, int size_a, int size_b);
void		ft_sort_all(t_s_list **s_a, t_s_list **s_b, int size_a, int size_b);
int			ft_issorted(t_s_list *stack);
void		ft_sort_three(t_s_list **stack);
void		ft_sort_four(t_s_list **stack_a, t_s_list **stack_b);
void		ft_sort_five(t_s_list **stack_a, t_s_list **stack_b);
void		ft_start_sort(t_s_list **stack_a, t_s_list **stack_b, int size);
/*******************************************************************************
*						In_parsing.c	 	 							       *
*******************************************************************************/
int			ft_digit_args(char *av);
long		ft_atol(const char *str);
int			ft_are_duplicates(char **av);
int			ft_is_all_space(const char *str);
void		ft_check_args(char **av, t_s_list **stack_a, t_flags mode);
/*******************************************************************************
*						Inside_lis.c		 				 			       *
*******************************************************************************/
int			*end_index(int *lis_len, int size, int *end, int *max);
void		ft_push_a_lis(t_s_list **s_a, t_s_list **s, int *arr, int size);
int			*search_lis(int *arr, int size);
int			*get_lis(int *arr, int *lis_len, int *prev, int size);
int			*list_to_array(t_s_list *stack_a, int size);
int			size_of_lis(int *lis);
/*******************************************************************************
*						List_elements.c	 	 							       *
*******************************************************************************/
void		ft_stack_positioning(t_s_list **stack);
int			find_smallest_index_position(t_s_list **stack);
int			biggest_index(t_s_list *stack);
int			ft_smallest_index(t_s_list *stack);
void		ft_positioning(t_s_list **stack);
t_s_list	*ft_lastnode(t_s_list *stack);
void		ft_lstcreat_append(t_s_list **stack_a, int n);
int			ft_listsize(t_s_list *lst);
void		ft_indexing_stack(t_s_list *stack, int size);
void		positive_gap(int *gap, int *target, int *small_gap, int *tmp_pos);
int			find_insert_pos(t_s_list **s_a, int indx_b, int gap, int target);
void		set_target_node(t_s_list **stack_a, t_s_list **stack_b);
int			lastnode_val(t_s_list *stack);
/*******************************************************************************
*						Move_costs.c	 	 							       *
*******************************************************************************/
int			ft_abs_val(int mov_a, int mov_b);
int			that_small_move(int *costs, int size_b);
int			*fetch_acosts(int *loc_a, int *loc_b, int size_b);
int			fall_moves(int *move_a, int *move_b, int size_b);
int			prepare_a(int move_a, int move_b, t_s_list **s_a, t_s_list **s_b);
/*******************************************************************************
*						Operation_moves.c	 	 						       *
*******************************************************************************/
void		push(t_s_list **from, t_s_list **to);
void		pa(t_s_list **a, t_s_list **b);
void		pb(t_s_list **a, t_s_list **b);
void		rev_rotate(t_s_list **stack);
void		rra(t_s_list **a);
void		rrb(t_s_list **b);
void		rrr(t_s_list **a, t_s_list **b);
void		rotate(t_s_list **stack);
void		ra(t_s_list **a);
void		rb(t_s_list **b);
void		rr(t_s_list **a, t_s_list **b);
void		swap(t_s_list **stack);
void		sa(t_s_list **stack_a);
void		sb(t_s_list **stack_b);
void		ss(t_s_list **a, t_s_list **b);
/*******************************************************************************
 * 								Dot_H_file	 	 			    			   *
*******************************************************************************/

#endif
