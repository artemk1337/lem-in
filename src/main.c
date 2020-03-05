/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <cchadwic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 15:04:40 by cchadwic          #+#    #+#             */
/*   Updated: 2020/03/02 15:32:02 by cchadwic         ###   ########.fr       */
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
			&& prev_r != g_lemin->finish && !curr->room->superpos) /*
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





t_solution	*find_s(t_room **arr)
{
	t_solution	*tmp;

	tmp = g_lemin->solution;
	while (tmp)
		if (tmp->arr == arr)
			return (tmp);
	return (NULL);
}




void	revive(t_room **arr)
{
	int		i;
	t_next	*neigh;
	t_next	*neigh_;

	i = 0;
	while (arr[i] && arr[i + 1])
	{
		if (arr[i]->path == arr)
			arr[i]->path = NULL;
		neigh = arr[i]->next;
		while (neigh && neigh->room != arr[i + 1])
			neigh = neigh->next;
		neigh->toggle = 1;
		neigh_ = arr[i + 1]->next;
		while (neigh_ && neigh_->room != arr[i])
			neigh_ = neigh_->next;
		if (neigh_->toggle && neigh->toggle)
		{
			neigh->weight = 1;
			neigh_->weight = 1;
		}
		else
		{
			neigh->weight = -1;
			neigh_->weight = -1;
		}
		i++;
	}
}

void	remove_sol(t_solution *sol)
{
	t_solution	*t_s;

	t_s = g_lemin->solution;
	while (t_s && t_s->next && t_s->next != sol)
		t_s = t_s->next;
	t_s->next = sol->next;
	free(sol->arr);
	free(sol);
}

void	put_new_arr(t_solution *sol, t_room **arr)
{
	int		i;
	t_next	*neigh;

	i = 0;
	sol->arr = arr;
	while (arr[i] && arr[i + 1])
	{
		if (!arr[i]->path
			&& arr[i] != g_lemin->start
			&& arr[i] != g_lemin->finish)
			arr[i]->path = arr;
		neigh = arr[i]->next;
		while (neigh && neigh->room != arr[i + 1])
			neigh = neigh->next;
		neigh->toggle = 0;
		neigh = arr[i + 1]->next;
		while (neigh && neigh->room != arr[i])
			neigh = neigh->next;
		neigh->weight = -1;
		i++;
	}
}

void	fix_c(t_solution *s_1, t_solution *s_2, int i_1)
{
	t_room	**arr;
	
	int		i_2;

	i_2 = 0;
	s_1->arr[i_1]->superpos = 1;
	while (s_2->arr[i_2] != s_1->arr[i_1])
		i_2++;
	ft_putnbr(i_2 + s_1->path_len - i_1);
	ft_putstr(" - size\n");
	arr = malloc(sizeof(t_room *) * (i_2 + s_1->path_len - i_1 + 1));
	arr[i_2 + s_1->path_len - i_1] = NULL;
	s_2->path_len = i_2 + s_1->path_len - i_1;
	i_2 = -1;
	while (s_2->arr[++i_2] != s_1->arr[i_1])
		arr[i_2] = s_2->arr[i_2];
	while (s_1->arr[i_1])
		arr[i_2++] = s_1->arr[i_1++];
	revive(s_1->arr);
	revive(s_2->arr);
	free(s_2->arr);
	put_new_arr(s_2, arr);
	remove_sol(s_1);
}




int		check_conflicts(void)
{
	int			i;
	t_solution	*t_s;

	t_s = g_lemin->solution;
	while (t_s)
	{
		i = 0;
		while (t_s->arr[i])
		{
			if (t_s->arr[i] != g_lemin->start
				&& t_s->arr[i] != g_lemin->finish
				&& t_s->arr[i]->path != t_s->arr
				&& !t_s->arr[i]->superpos)
			{
				fix_c(t_s, find_s(t_s->arr[i]->path), i);
				return (1);
			}
			i++;
		}
		t_s = t_s->next;
	}
	return (0);
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
			break ;
		}
		if (!save_tmp())
			break ;
		i = 0;
		print_sol();
		if (check_conflicts())
		{
			ft_putstr("There was conflic!\n");
			ft_putnbr(i++);
			ft_putchar('\n');
			print_sol();
		}
		/// Часть Макса
		//test_way();
		if ((check_solutions(g_lemin->prev_solution, g_lemin->solution)))
		{
			destroy_solutions(&g_lemin->solution);
			g_lemin->solution = g_lemin->prev_solution;
			return ;
		}
		if (g_lemin->prev_solution)
			destroy_solutions(&(g_lemin->prev_solution));
		g_lemin->prev_solution = copy_solution(g_lemin->solution);
		ft_putstr("TEST");
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
	//show_input();
	//alg_4();
	//check_struct(tmp);
	//show_max_lines();
	return (0);
}
