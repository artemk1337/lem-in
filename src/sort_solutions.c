/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_solutions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 14:16:29 by aolen             #+#    #+#             */
/*   Updated: 2020/03/02 14:16:29 by aolen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void sort_solutions(t_solution **solution)
{
	t_solution *begin;
	t_solution *temp[2];
	t_solution *main_iter;
	t_solution *iter;

	if (!*solution || !(*solution)->next)
		return ;
	begin = (*solution);
	main_iter = begin->next;
	while (main_iter)
	{
		iter = begin;
		while (iter != main_iter)
		{
			if (iter->path_len > main_iter->path_len)
			{
				if (iter == begin)
				{
					temp[1] = begin;
					begin = main_iter;
					temp[0]->next = main_iter->next;
					main_iter->next = temp[1];
				}
				else
				{
					temp[0]->next = main_iter->next;
					temp[1]->next = main_iter;
					main_iter->next = iter;
				}
				break ;
			}
			temp[1] = iter;
			iter = iter->next;
		}
		temp[0] = main_iter;
		main_iter = main_iter->next;
	}
	*solution = begin;
}

//#include <stdlib.h>
//
//int main()
//{
//	t_solution *ptr, *begin;
//
//	begin = ptr = malloc(sizeof(*ptr));
//	ptr->path_len = 8;
//	ptr->next = malloc(sizeof(*ptr));
//	ptr = ptr->next;
//	ptr->path_len = 8;
//	ptr->next = malloc(sizeof(*ptr));
//	ptr = ptr->next;
//	ptr->path_len = 6;
//	ptr->next = malloc(sizeof(*ptr));
//	ptr = ptr->next;
//	ptr->path_len = 7;
//	ptr->next = 0;
//	sort_solutions(&begin);
//}