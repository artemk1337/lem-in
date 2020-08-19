/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <cchadwic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 15:04:40 by cchadwic          #+#    #+#             */
/*   Updated: 2020/02/29 13:24:52 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lemin.h"


/* Ищет последнюю комнату */
t_room	*find_last_room(t_tmp *list)
{
	t_tmp	*curr;

	curr = list;
	while(curr->next)
		curr = curr->next;
	return (curr->room);
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


void	show_input(void)
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

void	show_max_lines(void)
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
