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


/* <================================> */
/* <========== Считывание ==========> */
/* <============ Готово ============> */


void	put_way_dop(t_tmp *tmp, t_tmp *tmp_2, char *s2, int weight)
{
	t_next *neigh;

	if (!tmp->room->next)
	{
		if (!(tmp->room->next = ft_memalloc(sizeof(t_next))))
			error_exit();
		neigh = tmp->room->next;
	}
	else
	{
		neigh = tmp->room->next;
		while (neigh->next)
		{
			if (!ft_strcmp(neigh->room->name, s2))
			    return ;
			neigh = neigh->next;
		}
		if (!(neigh->next = ft_memalloc(sizeof(t_next))))
			error_exit();
		neigh = neigh->next;
	}
	neigh->weight = weight;
	neigh->toggle = 1;
	neigh->global_toggle = 1;
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


/* <==================================> */
/* <========== Беллман-Форд ==========> */
/* <============= Готово =============> */


static int	bellman_ford(t_tmp *start, int counter)
{
	t_tmp	*curr;
	t_next	*curr_n;

	counter = 0;
	curr = start;
	while (curr)
	{
		//ft_putstr("Room: ");
		//ft_putstr(curr->room->name);
		//ft_putstr("\n");

		curr_n = curr->room->next;
		while (curr_n)
		{
			//ft_putstr("Neigh: ");
			//ft_putstr(curr_n->room->name);
			//ft_putstr("\n");

			if (curr_n->toggle && curr_n->global_toggle
				&& curr->room->min_w + curr_n->weight < curr_n->room->min_w
				&& curr->room != g_lemin->finish &&  curr->room->min_w != (INT_MAX / 2))
			{
				counter++;
				curr_n->room->prev = curr->room;
				curr_n->room->min_w = curr->room->min_w + curr_n->weight;
			}
			curr_n = curr_n->next;
		}
		curr = curr->next;
	}
	return (counter);
}


/* <=====================================> */
/* <========== Сохранение пути ==========> */
/* <=============== Готово ==============> */


t_room	**malloc_array_rooms(int len_way)
{
	t_room	**arr;

	if (!(arr = ft_memalloc(sizeof(t_room) * (len_way + 1))))
		exit(1);
	arr[len_way] = NULL;
	return (arr);
}


void	save_way(int len_way)
{
	t_solution	*solution;
	t_room		**arr_rooms;
	t_room		*curr_r;
	int			counter_len;

	counter_len = len_way;
	arr_rooms = malloc_array_rooms(len_way);
	curr_r = g_lemin->finish;
	while (curr_r->prev)
	{
		if (curr_r->out == NULL)
			arr_rooms[--counter_len] = curr_r;
		curr_r = curr_r->prev;
	}
	arr_rooms[--counter_len] = curr_r;

	solution = g_lemin->solution;
	if (!solution)
	{
		if (!(g_lemin->solution = ft_memalloc(sizeof(t_solution))))
			exit(1);
		solution = g_lemin->solution;

		solution->arr = arr_rooms;
		solution->path_len = len_way;
		solution->next = NULL;
	}
	else
	{
		while (solution->next)
			solution = solution->next;
		if (!(solution->next = ft_memalloc(sizeof(t_solution))))
			exit(1);
		solution = solution->next;

		solution->arr = arr_rooms;
		solution->path_len = len_way;
		solution->next = NULL;
	}
}


/* <======================================> */
/* <========== Удаление решения ==========> */
/* <=============== Готово ===============> */


void	del_sol(t_solution *sol)
{
	t_solution	*tmp;
	while (sol)
	{
		free(sol->arr);
		tmp = sol->next;
		free(sol);
		sol = tmp;
	}
}


/* <=======================================================> */
/* <========== Длина пути и проверка пересечений ==========> */
/* <======================= Готово ========================> */


// Возвращаю либо длину пути, либо -1 с глобальным занулением связей
int		count_len_way(void)
{
	t_room	*curr;
	t_room	*prev;
	t_next	*neigh;
	int		len;
	int		cross_way;

	len = 1;
	cross_way = 0;
	curr = g_lemin->finish;
	//ft_putstr("CHECK\n");
	// Считаю длину пути
	prev = curr->prev;
	while (prev)
	{
		//ft_putstr("Room: ");
		//ft_putstr(prev->name);
		//ft_putstr((prev->in) ? "_out": "");
		//ft_putstr((prev->out) ? "_in": "");
		//ft_putstr("\n");
		if (prev == g_lemin->start)
			break ;
		len++;
		// Если перешел из комнаты in в комнату out
		if (curr->in && prev->out)
		{
			// Глоб
			//ft_putstr("1\n");
			neigh = curr->next;
			while (neigh->room != prev)
				neigh = neigh->next;
			//ft_putstr((neigh) ? "YES\n": "NO\n");
			neigh->global_toggle = 0;
			//ft_putstr("2\n");
			neigh = prev->next;
			while (neigh->room != curr)
				neigh = neigh->next;
			neigh->global_toggle = 0;
			cross_way = 1;
			//ft_putstr("3\n");
		}
		curr = prev;
		prev = curr->prev;
	}
	len++;
	if (cross_way)
		return (-1);
	return (len);
}


// Ищет последнюю комнату
t_room	*find_last_room(t_tmp *list)
{
	t_tmp	*curr;

	curr = list;
	while(curr->next)
		curr = curr->next;
	return (curr->room);
}


/* <======================================> */
/* <========== Разбиение комнат ==========> */
/* <============== Готово ================> */


t_room	*split_room(t_room *curr, t_tmp *list)
{
	t_next	*neigh;
	t_next	*neigh_neigh;
	t_room	*in;
	t_room	*out;

	if (curr->in || curr->out)
	{
		// НИКОГДА НЕ ДОЛЖНО СРАБАТЫВАТЬ
		ft_putstr("ERROR 1\n");
		exit(1);
	}
	g_lemin->finish->was_here = 1;
	// Создал комнату
	list = init_tmp(list, 1, curr->name); // ft_strjoin(curr->name, "123")
	in = find_last_room(list);
	out = curr;
	out->in = in;
	in->out = out;

	// Перенес соседей
	// Перекинул связи с out на in кроме той, по которой шли
	neigh = out->next;
	// Проблема в этом while в случае прохода по последнему соседу.
	// Непонятно, почему. Предположительно, ошибка при считывании.
	while (neigh)
	{

		if (!neigh->room->was_here)
		{
			if (neigh->room->out)
				neigh_neigh = neigh->room->out->next;
			else
				neigh_neigh = neigh->room->next;
			while (neigh_neigh && neigh_neigh->room != out)
				neigh_neigh = neigh_neigh->next;
			neigh_neigh->room = in;
		}
		neigh = neigh->next;
	}

	// Создал соседа для in
	if (!(neigh = ft_memalloc(sizeof(t_next))))
		exit(1);
	g_lemin->edge++;
	neigh->weight = -1;
	neigh->toggle = 1;
	neigh->global_toggle = 1;
	neigh->next = NULL;
	neigh->room = out->prev;
	in->next = neigh;
	in->prev = out->prev;

 	// Перекинул связь на in
	neigh = out->next;
	while (neigh)
	{
		if (neigh->room == out->prev)
		{
			neigh->room = in;
			neigh->weight = 0;
		}
		neigh = neigh->next;
	}
	out->prev = in;

	in->was_here = 1;
	out->was_here = 1;
	return (in->prev);
}


// Удаляем раздвоение на всем графе, заново переносим связи и удаляем in-связь
void	reset_graph(t_tmp *list)
{
	t_tmp	*curr;
	t_tmp	*next;
	t_room	*out;
	t_next	*neigh;
	t_next	*neigh_neigh;

	// Ищу комнату-in 
	curr = list;
	while (curr && curr->next && !curr->next->room->out)
		curr = curr->next;
	// Указатель на NULL
	next = curr->next;
	curr->next = NULL;
	// Зачищаю список и переношу связи
	curr = next;
	while (curr)
	{
		//ft_putstr("\nDELETED: ");
		//ft_putstr(curr->room->name);
		//ft_putchar('\n');

		next = curr->next; // Можно удалить
		out = curr->room->out;
		// Переношу связь с in на предыдущую комнату
		neigh_neigh = out->next;
		while (neigh_neigh && neigh_neigh->room != curr->room)
			neigh_neigh = neigh_neigh->next;
		if (neigh_neigh)
		{
			neigh_neigh->room = curr->room->next->room;
			neigh_neigh->global_toggle = curr->room->next->global_toggle;
		}
		// Переношу связи на out
		neigh = out->next;
		while (neigh)
		{
			if (neigh->room->out)
				neigh_neigh = neigh->room->out->next;
			else
				neigh_neigh = neigh->room->next;
			while (neigh_neigh && neigh_neigh->room != curr->room)
				neigh_neigh = neigh_neigh->next;
			if (neigh_neigh)
				neigh_neigh->room = out;
			neigh = neigh->next;
		}
		// Удаляю комнату и ее связь
		free(curr->room->next);
		free(curr->room->name);
		free(curr->room);
		free(curr);
		g_lemin->edge--;
		curr = next;
	}

	// Переключаю toggle и восстанавливаю веса связей
	curr = list;
	while (curr)
	{
		neigh = curr->room->next;
		while (neigh)
		{
			neigh->toggle = 1;
			neigh->weight = 1;
			neigh = neigh->next;
		}
		curr->room->out = NULL;
		curr->room->in = NULL;
		curr = curr->next;
	}
}


/* <====================================> */
/* <========== Восстановление ==========> */
/* <============== Готово ==============> */


// Сбрасывает предыдущую комнату и восстанавливает веса
void			reset_minw_prev(t_tmp *list)
{
	t_tmp *tmp;

	tmp = list;
	while (tmp)
	{
		tmp->room->prev = NULL;
        if (tmp->room != g_lemin->start)
		    tmp->room->min_w = INT_MAX / 2;
		tmp->room->was_here = 0;
		tmp = tmp->next;
	}
}


/* <========================================> */
/* <========== Количество решений ==========> */
/* <================ Готово ================> */


int		count_sols(t_solution *sol)
{
	int	counter;

	counter = 0;
	while (sol)
	{
		counter++;
		sol = sol->next;
	}
	return (counter);
}


/* <===============================> */
/* <========== Суурбалле ==========> */
/* <============ Готово ===========> */


int		suurballe(t_tmp *list)
{
	t_room	*curr;
	t_room	*prev;
	t_next	*neigh;
	t_next	*neigh_neigh;
	int		len_way;

	curr = g_lemin->finish;
	prev = curr->prev;
	len_way = count_len_way();
	if (len_way == -1)
		return (0);
	while (prev)
	{
		//ft_putnbr(1);
		//ft_putstr("\n");
		neigh = curr->next;
		while (neigh && neigh->room != prev)
			neigh = neigh->next;
		neigh->weight = -1;
		//ft_putnbr(2);
		//ft_putstr("\n");
		neigh_neigh = neigh->room->next;
		while (neigh_neigh && neigh_neigh->room != curr)
			neigh_neigh = neigh_neigh->next;
		neigh_neigh->toggle = 0;
		//ft_putnbr(3);
		//ft_putstr("\n");
		if (curr == g_lemin->start)
			break ;
		if (curr != g_lemin->finish)
		{
			//ft_putnbr(4);
			//ft_putstr("\n");
			prev = split_room(curr, list); // ПРОБЛЕМЫ
		}
		curr = prev;
		prev = curr->prev;
	}
	//check_struct(list);
	return (len_way);
}


/* <==============================> */
/* <========== Алгоритм ==========> */
/* <=========== Готово ===========> */


void	algorithm(t_tmp *list)
{
	int i;
	int	max_ways;
	int	count_sol;

	count_sol = 0;
	max_ways = 8;
	while (max_ways != count_sol)
	{
		// Нашли кратчайший путь
		i = 0;
		//print_sol();
		//ft_putstr("Bellman-Ford started\n");
		while (i++ < g_lemin->edge)
			if (!bellman_ford(list, 0))
				break ;
		//ft_putstr("Bellman-Ford finished\n");
		check_struct(list);
		//test_way();
		if (!g_lemin->finish->prev)
			return ;
		
		//check_struct(list);
		//test_way();
		i = suurballe(list); // Проблема здесь
		//test_way();
		if (i)
		{
			//test_way();
			save_way(i);
		}
		else
		{
			//ft_putstr("Problems with way, need reset and restart\n");
			//exit(1);
			del_sol(g_lemin->solution);
			g_lemin->solution = NULL;
			//check_struct(list);
			reset_graph(list);
			//check_struct(list);
		}
		count_sol = count_sols(g_lemin->solution);
		reset_minw_prev(list);
		//check_struct(list);
	}
	//ft_putstr("\nSuccess\n");
}





int		main()
{
#ifdef DEBUG
	g_fd = open("/home/poligon/42school/lemin/interesting_maps/gemerald4", O_RDONLY);
#endif
	t_tmp	*tmp;

	g_lemin = init_lemin();
	tmp = create_struct();
	g_lemin->arr = create_array(&tmp);
	check_duplicate_nodes(g_lemin->arr);
	algorithm(tmp);
	print_sol();
    /*sort_solutions(&g_lemin->solution);
	if (!(g_lemin->solution))
		error_exit();
	show_input();
	alg_4();
	show_max_lines();*/
    clean_tmp(&tmp);
	return (0);
}
