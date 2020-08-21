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

# define STDIN 0
# define ULLONG_MAX_STR "18446744073709551615"

typedef struct			s_next
{
	struct s_room		*room;
	int					weight;
	int					toggle;
	int					global_toggle;
	struct s_next		*next;
}						t_next;

typedef struct			s_room
{
	char				*name;
	t_next				*next;
	int					was_here;

	int					min_w;
	struct s_room		*prev;
	struct s_room		*in;
	struct s_room		*out;

	struct s_room		**path;
	int					idx;

	unsigned long		ant;
	unsigned long		number_ant;
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
	int					v;

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
t_lemin					*init_lemin(int argc, char **argv);
t_room					*init_room(char *s);
t_tmp					*init_tmp(t_tmp *tmp, int a, char *s);

/*
** _check.c
*/
void					check_struct(t_tmp *tmp);
void					print_sol(void);
void					test_way(void);

/*
** save_solution.c
*/
t_room					**malloc_array_rooms(int len_way);
void					save_way(int len_way);

/*
** del_solution.c
*/
void					del_sol(t_solution **solution);

/*
** len_way_and_check_crossing.c
*/
int						count_len_way(void);

/*
** clear.c
*/
void					clean_tmp(t_tmp **tmp);
void					reset_minw_prev(t_tmp *list);

/*
** validation
*/
void					check_duplicate_nodes(t_room **rooms_array);
void					check_edge(char *str);
void					check_node(char *str);
unsigned long int		check_ant_num(char *str);

/*
** validation_dop.c
*/
void					free_word_list(char ***words);

/*
** Error handling
*/
void					error_exit(void);

/*
** output.c
*/
int						alg_4(int print);

/*
** global VARS
*/
t_lemin					*g_lemin;

/*
** Solution copy and destroy
*/
int						check_solutions(t_solution *prev_solution,
										t_solution *current_solution);
void					sort_solutions(t_solution **solution);

/*
** split_room.c
*/
t_room					*split_room(t_room *curr, t_tmp *list);

/*
** del_split_room.c
*/
void					reset_graph(t_tmp *list);

/*
** utils1.c
*/
t_room					*find_last_room(t_tmp *list);
int						count_sols(t_solution *sol);
void					show_input(void);
void					show_max_lines(void);

/*
** bellman_ford.c
*/
int						bellman_ford(t_tmp *start, int counter);

/*
** suuballe.c
*/
int						suurballe(t_tmp *list);

/*
** alg_suurballe.c
*/
int						algorithm(t_tmp *list, int max_ways);

/*
** dop_main.c
*/
void					dop_main(int tmp_, int ways, t_tmp *tmp);

/*
** read_file_1.c
*/
t_tmp					*create_struct(void);
void					check_ants(char *line);
t_tmp					*create_struct_prefix(char **line, t_tmp *tmp);

/*
** read_file_1.c
*/
t_tmp					*create_struct_(char *line, t_tmp *tmp);
void					put_way(char *s, t_tmp *tmp);
void					put_way_dop(t_tmp *tmp, t_tmp *tmp_2,
						char *s2, int weight);

#endif
