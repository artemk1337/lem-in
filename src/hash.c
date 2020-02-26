/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <cchadwic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 16:31:35 by aolen             #+#    #+#             */
/*   Updated: 2020/02/17 21:57:33 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

#include <stdio.h>

//c program hash

unsigned long	hash(unsigned char *str)
{
	unsigned long	hash;
	int				c;

	hash = 5381;
	while ((c = (*str++)))
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	return hash;
}

void			add_el_in_array(t_room *room, t_room **array)
{
	unsigned long	tmp_hash;
	unsigned int	i;

	tmp_hash = hash((unsigned char*)room->name) % g_lemin->rooms;
	i = tmp_hash * g_lemin->rooms;
	while (array[i])
		i++;
	array[i] = room;
}

// Не чищу!!! 
t_room			**create_array(t_tmp **list_begin)
{
	t_room	**rooms_array;
	t_tmp	*start; // Добавил
	int		i;
	t_tmp	*temp_ptr;

	rooms_array = ft_memalloc(sizeof(t_room*) * g_lemin->rooms * g_lemin->rooms);
	i = -1;
	start = *list_begin; // Добавил
	while (++i < g_lemin->rooms)
	{
		temp_ptr = *list_begin;
		add_el_in_array(temp_ptr->room, rooms_array);
		temp_ptr = (*list_begin)->next;
		//free(*list_begin); // Добавил
		*list_begin = temp_ptr;
	}
	*list_begin = start; // Добавил
	return rooms_array;
}

t_room			*find_element(char *name, t_room **room_array)
{
	unsigned int	element_hash;

	element_hash = hash((unsigned char*)name);
	while (ft_strcmp(room_array[element_hash]->name, name))
		element_hash++;
	return (room_array[element_hash]);
}
