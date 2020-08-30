/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 13:09:04 by aolen             #+#    #+#             */
/*   Updated: 2020/02/18 13:09:05 by aolen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

unsigned long int	check_ant_num(char *str)
{
	int ant_num;

	if ((ft_strlen(str) > 19) || !ft_isdigitstr(str) || ft_strlen(str) == 0)
		error_exit();
	ant_num = ft_atoul(str);
	if (ant_num <= 0)
		error_exit();
	return (ant_num);
}

void				check_node(char *str)
{
	char	**words;
	int		i;
	int		spaces;

	i = -1;
	spaces = 0;
	while (str[++i])
		spaces += 1 ? str[i] == ' ' : 0;
	if (spaces != 2)
		error_exit();
	i = -1;
	words = ft_strsplit(str, ' ');
	while (words[++i])
		;
	if (str[0] == 'L' || i != 3)
		error_exit();
	while (--i != 1)
		if (!ft_isdigitstr(words[i]))
			error_exit();
	free_word_list(&words);
}

void				check_edge(char *str)
{
	char	**nodes;
	int		i;

	i = 0;
	nodes = ft_strsplit(str, '-');
	while (nodes[++i])
		;
	if (str[0] == 'L' || i != 2)
		error_exit();
	free_word_list(&nodes);
}

void				check_one_hash(t_room **rooms_array, int i)
{
	int max_threshold;
	int j;

	max_threshold = (i / g_lemin->rooms) * g_lemin->rooms + g_lemin->rooms;
	j = max_threshold - g_lemin->rooms;
	while (j < max_threshold && rooms_array[j])
	{
		if (ft_strequ(rooms_array[i]->name, rooms_array[j]->name)
		&& i != j)
			error_exit();
		j++;
	}
}

void				check_duplicate_nodes(t_room **rooms_array)
{
	int i;

	i = 0;
	if (!g_lemin->start || !g_lemin->finish)
		error_exit();
	while (i < (g_lemin->rooms * g_lemin->rooms))
	{
		if (!rooms_array[i])
			i = (i / g_lemin->rooms + 1) * g_lemin->rooms;
		else
			check_one_hash(rooms_array, i++);
	}
}
