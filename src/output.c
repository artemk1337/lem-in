/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <cchadwic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 13:23:11 by cchadwic          #+#    #+#             */
/*   Updated: 2020/02/29 13:26:07 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "lemin.h"

int			check_ant(t_solution *sol, int len_way)
{
	t_solution		*sol_tmp;
	int				i;
	unsigned long	delta;


	sol_tmp = g_lemin->solution;
	delta = 0;
	i = 0;
	while (sol_tmp != sol)
	{
		delta += len_way - sol_tmp->path_len;
		sol_tmp = sol_tmp->next;
		i++;
	}
	if (delta <= g_lemin->start->ant)
		return (1);
	return (0);
}

static void	print_anc(int c, char *s)
{
	ft_putstr("L");
	ft_putnbr(c);
	ft_putstr("-");
	ft_putstr(s);
	ft_putstr(" ");
}

static void	move_ant(t_solution *sol, int len_way)
{
	t_room	*curr_r;
	t_room	*pr_r;
	int		len_cpy;

	len_cpy = len_way--;
	while (len_way > 0)
	{
		if (len_way == 1 && !check_ant(sol, len_cpy))
			break ;
		curr_r = sol->arr[len_way];
		pr_r = sol->arr[len_way - 1];
		if (pr_r->ant)
		{
			curr_r->ant += 1;
			pr_r->ant -= 1;
			if (len_way > 1)
				curr_r->number_anc = pr_r->number_anc;
			else
				curr_r->number_anc = g_lemin->count - pr_r->ant;
			pr_r->number_anc = 0;
			print_anc(curr_r->number_anc, curr_r->name);
		}
		len_way--;
	}
}

void		alg_4(void)
{
	t_solution	*sol;
	int			i;
	int			step;

	g_lemin->start->ant = g_lemin->count;
	g_lemin->finish->ant = 0;
	ft_putstr("\tSolution:\n\n");
	step = 1;
	while (g_lemin->finish->ant != g_lemin->count)
	{
		i = 0;
		sol = g_lemin->solution;
		while (sol)
		{
			move_ant(sol, sol->path_len);
			sol = sol->next;
			i++;
		}
		ft_putstr("\t| step - ");
		ft_putnbr(step++);
		ft_putstr("\n");
	}
}
