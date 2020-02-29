/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <cchadwic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 15:04:40 by cchadwic          #+#    #+#             */
/*   Updated: 2020/02/29 13:30:35 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
//#define DEBUG
#ifndef DEBUG
# define STDIN 0
#endif

// TODO Comments and unknown commands must be ignored by program
//  - 101
// TODO Replace checking funcs if necessary


// TODO delete DEBUG macros before deploy
//  - 24
//  - 155

#ifdef DEBUG
# include <fcntl.h>
# define STDIN 3
int g_fd;
#endif

void	put_way_dop(t_tmp *tmp, t_tmp *tmp_2, char *s2, int weight)
{
	t_next *neigh;

	if (!tmp->room->next)
	{
		if (!(tmp->room->next = malloc(sizeof(t_next))))
			error_exit();
		neigh = tmp->room->next;
	}
	else
	{
		neigh = tmp->room->next;
		while (neigh->next)
		{
			if (!ft_strcmp(neigh->room->name, s2))
				error_exit();
			neigh = neigh->next;
		}
		if (!(neigh->next = malloc(sizeof(t_next))))
			error_exit();
		neigh = neigh->next;
	}
	neigh->weight = weight;
	neigh->toggle = 1;
	neigh->next = NULL;
	while (tmp_2 && ft_strcmp(tmp_2->room->name, s2))
		tmp_2 = tmp_2->next;
	if (tmp_2)
		neigh->room = tmp_2->room;
}

void	put_way(char *s, t_tmp *tmp)
{
	t_tmp	*start;
	int		i;

	i = 0;
	(g_lemin->edge)++;
	check_edge(s);
	while (s[i] != '-')
		i++;
	s[i] = '\0';
	start = tmp;
	while (tmp && ft_strcmp(tmp->room->name, s))
		tmp = tmp->next;
	if (tmp)
		put_way_dop(tmp, start, &(s[i + 1]), 1);
	tmp = start;
	while (tmp && ft_strcmp(tmp->room->name, &(s[i + 1])))
		tmp = tmp->next;
	if (tmp)
		put_way_dop(tmp, start, s, 1);
	else
		error_exit();
}

static t_tmp	*create_struct_(char *line, t_tmp *tmp)
{
	if (ft_strchr(line, ' '))
	{
		check_node(line);
		tmp = init_tmp(tmp, 1, line);
		(g_lemin->rooms)++;
	}
	else if (ft_strchr(line, '-'))
		put_way(line, tmp);
	return (tmp);
}

static t_tmp	*create_struct_prefix(char **line, t_tmp *tmp)
{
	if (!ft_strcmp(&(line[0][2]), "start"))
	{
		ft_strdel(line);
		if ((get_next_line(STDIN, line)) < 1)
			error_exit();
		check_node(*line);
		g_lemin->vector = ft_put_vec(g_lemin->vector, *line);
		tmp = init_tmp(tmp, 0, *line);
		(g_lemin->rooms)++;
	}
	else if (!ft_strcmp(&(line[0][2]), "end"))
	{
		ft_strdel(line);
		if ((get_next_line(STDIN, line)) < 1)
			error_exit();
		check_node(*line);
		g_lemin->vector = ft_put_vec(g_lemin->vector, *line);
		tmp = init_tmp(tmp, -1, *line);
		(g_lemin->rooms)++;
	}
	return (tmp);
}

void	check_ants(char *line)
{
	g_lemin->count = check_ant_num(line);
	g_lemin->vector = ft_put_vec(g_lemin->vector, line);
	ft_strdel(&line);
}

t_tmp	*create_struct(void)
{
	char	*line;
	t_tmp	*tmp;

	tmp = NULL;
	if (get_next_line(STDIN, &line) > 0)
		check_ants(line);
	while (get_next_line(STDIN, &line) > 0)
	{
		if (*line == '\0')
		{
			ft_strdel(&line);
			break ;
		}
		g_lemin->vector = ft_put_vec(g_lemin->vector, line);
		if (line[0] != '#')
			tmp = create_struct_(line, tmp);
		else if (line[0] == '#' && line[1] == '#')
			tmp = create_struct_prefix(&line, tmp);
		ft_strdel(&line);
	}
	if (!(tmp))
		error_exit();
	return (tmp);
}





void	show_input()
{
	size_t	i;

	g_lemin->vector = ft_put_vec(g_lemin->vector, "");
	i = 0;
	while (i < g_lemin->vector->curr_size)
	{
		if (g_lemin->vector->vec[i] == '\0')
			write(1, "\n", 1);
		else
			write(1, &(g_lemin->vector->vec[i]), 1);
		i++;
	}
}

void	show_max_lines()
{
	size_t	i;

	i = 0;
	while (i < g_lemin->vector->curr_size)
	{
		if (ft_strstr(&(g_lemin->vector->vec[i]), "#Here is the number of lines required"))
		{
			ft_putstr("\n");
			ft_putstr(&(g_lemin->vector->vec[i]));
			ft_putstr("\n");
			break ;
		}
		i += ft_strlen(&(g_lemin->vector->vec[i])) + 1;
	}
}














static int	put_min_weights(t_tmp *start, int counter)
{
	t_tmp	*curr;
	t_room	*prev_r;
	t_next	*curr_n;
	t_next	*prev_n;

	curr = start;
	while (curr)
	{
		curr_n = curr->room->next;
		while (curr_n)
		{
			prev_r = curr_n->room;
			prev_n = prev_r->next;
			while (prev_n && prev_n->room != curr->room)
				prev_n = prev_n->next;
			if (prev_n->toggle && prev_r->min_w + prev_n->weight < curr->room->min_w
			&& prev_r->path == NULL && prev_r != g_lemin->finish && curr->room->path == NULL) /*
			**addprev_r->path == NULL && prev_r != g_lemin->finish && curr->room->path == NULL */
			{
				counter++;
				curr->room->min_w = prev_r->min_w + prev_n->weight;
				curr->room->prev = prev_r;
			}
			curr_n = curr_n->next;
		}
		curr = curr->next;
	}
	return (counter);
}





static int	check_neigh(t_room **arr, int i)
{
	t_next	*neigh;
	int		k;

	k = 0;
	neigh = arr[i]->next;
	while (neigh)
	{
		k++;
		neigh = neigh->next;
	}
	if (k > 2)
		return (0);
	arr[i]->superpos = 1;
	return (1);
}

void		clean_one_sol(t_solution *sol, t_room *curr_r)
{
	t_solution	*curr_s;
	t_solution	*prev_s;
	int			i;

	prev_s = NULL;
	curr_s = sol;
	while (curr_s)
	{
		if (curr_s->arr == curr_r->path)
		{
			i = 0;
			while (curr_s->arr[i])
			{
				curr_s->arr[i++]->path = NULL;
				if (curr_s->arr[i])
					curr_s->arr[i]->prev = curr_s->arr[i - 1];
			}
			i = 0;
			while (curr_s->arr[i] && curr_s->arr[i] != curr_r)
				i++;
			i--;
			while (i >= 0 && check_neigh(curr_s->arr, i))
				curr_s->arr[i--] = NULL;
			free(curr_s->arr);
			if (prev_s)
				prev_s->next = curr_s->next;
			else
				g_lemin->solution = curr_s->next;
			free(curr_s);
			break ;
		}
		prev_s = curr_s;
		curr_s = curr_s->next;
	}
}

int		check_superpos(t_solution *sol, int count)
{
	t_room	*curr_r;
	t_room	*prev_r;
	t_next	*neigh;
	t_next	*tmp_n;

	prev_r = NULL;
	curr_r = g_lemin->start;
	while (curr_r)
	{
		// ft_putstr(curr_r->name);
		// ft_putstr("\n");
		neigh = curr_r->next;
		while (neigh && neigh->room->prev != curr_r)
			neigh = neigh->next;
		if (neigh && neigh->room->prev == curr_r)
		{
			prev_r = neigh->room->prev;
		}
		if (!neigh)
		{
			tmp_n = curr_r->next;
			while (tmp_n)
			{
				if (!(tmp_n->room->superpos) && tmp_n->room->path)
				{
					prev_r = curr_r;
					curr_r = tmp_n->room;
					break ;
				}
				tmp_n = tmp_n->next;
			}
			break ;
		}
		curr_r = neigh->room;
	}
	if (!curr_r || !(curr_r->path) || curr_r == prev_r)
	{
		// ft_putstr("EXIT\n");
		if (!count)
			return (1);
		return (0);
	}
	// ft_putstr(curr_r->name);
	// ft_putstr("\n");

	clean_one_sol(sol, curr_r);
	curr_r->prev = prev_r;
	// ft_putstr(prev_r->name);
	// ft_putstr("\n");
	if (!save_tmp())
		exit (1);
	curr_r = g_lemin->finish->prev;
	while (curr_r != g_lemin->start)
	{
		curr_r->superpos = 1;
		curr_r = curr_r->prev;
	}
	// test_way();
	if (!check_superpos(sol, count + 1))
		return (0);
	return (1);
}

void	reset_superpos(t_tmp *list)
{
	t_tmp	*tmp;
	t_next	*curr_n;

	reset_struct(list);
	tmp = list;
	while (tmp)
	{
		// ft_putstr(tmp->room->name);
		// ft_putstr("\n");
		if (tmp->room->superpos == 0)
		{
			curr_n = tmp->room->next;
			while (curr_n)
			{
				if (curr_n->room->superpos == 0)
					curr_n->toggle = 1;
				curr_n = curr_n->next;
			}
		}
		tmp = tmp->next;
	}
}

void	algorithm_super_pos(t_tmp *list)
{
	int i;

	while (1)
	{
		i = 0;
		while (i++ < g_lemin->edge)
		{
			if (!put_min_weights(list, 0))
				break ;
		}
		if (!(g_lemin->finish->prev))
		{
			break ;
		}
		if (!save_tmp())
			break ;
		/// Часть Макса
		// test_way();
		if ((check_solutions(g_lemin->prev_solution, g_lemin->solution)))
		{
			destroy_solutions(&g_lemin->solution);
			g_lemin->solution = g_lemin->prev_solution;
			return ;
		}
		if (g_lemin->prev_solution)
			destroy_solutions(&(g_lemin->prev_solution));
		g_lemin->prev_solution = copy_solution(g_lemin->solution);
		///
		reset_struct(list);
	}
}

void	algorithm(t_tmp *list)
{
	int i;

	while (1)
	{
		i = 0;
		while (i++ < g_lemin->edge)
		{
			if (!put_min_weights(list, 0))
				break ;
		}
		if (!(g_lemin->finish->prev))
		{
			//check_struct(list);
			if (check_superpos(g_lemin->solution, 0))
			{
				// check_struct(list);
				break ;
			}
			else
			{
				// check_struct(list);
				reset_superpos(list);
				algorithm_super_pos(list);
				break ;
			}
		}
		if (!save_tmp())
			break ;
		/// Часть Макса
		// test_way();
		if ((check_solutions(g_lemin->prev_solution, g_lemin->solution)))
		{
			destroy_solutions(&g_lemin->solution);
			g_lemin->solution = g_lemin->prev_solution;
			return ;
		}
		if (g_lemin->prev_solution)
			destroy_solutions(&(g_lemin->prev_solution));
		g_lemin->prev_solution = copy_solution(g_lemin->solution);
		///
		reset_struct(list);
	}
}
	









int		main()
{
#ifdef DEBUG
	g_fd = open("../test_2", O_RDONLY);
#endif
	t_tmp	*tmp;

	g_lemin = init_lemin();
	tmp = create_struct();
	g_lemin->arr = create_array(&tmp);
	check_duplicate_nodes(g_lemin->arr);
	algorithm(tmp);
	print_sol();
	if (!(g_lemin->solution))
		error_exit();
	show_input();
	alg_4();
	//check_struct(tmp);
	show_max_lines();
	return (0);
}
