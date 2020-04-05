/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <cchadwic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 15:05:08 by cchadwic          #+#    #+#             */
/*   Updated: 2020/03/02 15:43:15 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include <string.h>
# include <libft.h>
# include <limits.h>

typedef struct			s_next
{
	struct s_room		*room;
	int					weight;
	int					toggle;
	struct s_next		*next;
}						t_next;

typedef struct			s_room
{
	char				*name;
	t_next				*next;

	int					min_w;
	int					superpos;
	int					was_sup;
	struct s_room		*prev;
	struct s_room		*prev1;

	struct s_room		**path;
	int					idx;

	// For ant
	unsigned long		ant;
	unsigned long		number_anc;
}						t_room;

typedef struct			s_tmp
{
	t_room				*room;
	struct s_tmp		*next;
}						t_tmp;

typedef struct			s_solution
{
	t_room				**arr;
	unsigned int		path_len;
	int					hide;
	struct s_solution	*next;
}						t_solution;

typedef struct			s_lemin
{
	t_vec				*vector;
	unsigned long		count;

	int					rooms;
	int					edge;

	t_room				*start;
	t_room				*finish;
	t_room				**arr;
	t_solution			*solution;
	t_solution			*prev_solution;

	t_tmp				*sup_list;
}						t_lemin;

/*
** hash.c
*/
t_room					*find_element(char *name, t_room **room_array);
t_room					**create_array(t_tmp **list_begin);

/*
** init.c
*/
t_lemin					*init_lemin(void);
t_room					*init_room(char *s);
t_tmp					*init_tmp(t_tmp *tmp, int a, char *s);

/*
** _check.c
*/
void					check_struct(t_tmp *tmp);
void					print_sol(void);
void					test_way(void);

/*
** solution.c
*/
int						save_tmp(void);
void					reset_struct(t_tmp *list);
void	    			init_sol(t_solution *sol, int size);

/*
** clear.c
*/
t_solution				*clean_sol(void);
void					clean_tmp(t_tmp **tmp);

/*
** Validation
*/
void					check_duplicate_nodes(t_room **rooms_array);
void					check_edge(char *str);
void					check_node(char *str);
unsigned long int		check_ant_num(char *str);

/*
** Error handling
*/
void					error_exit(void);

/*
** output.c
*/
void					alg_4(void);

/*
** global VARS
*/
t_lemin					*g_lemin;

/*
** Solution copy and destroy
*/
t_solution				*copy_solution(t_solution *source_solutions);
void					destroy_solutions(t_solution **solution);
int						check_solutions(t_solution *prev_solution,
										t_solution *current_solution);
void					sort_solutions(t_solution **solution);

#endif
