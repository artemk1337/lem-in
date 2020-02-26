/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 11:59:57 by cchadwic          #+#    #+#             */
/*   Updated: 2019/09/09 12:00:27 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_list_clear(t_list **begin_list)
{
	t_list *mass;

	if (*begin_list && begin_list)
	{
		while (*begin_list)
		{
			mass = *begin_list;
			*begin_list = (*begin_list)->next;
			free(mass);
		}
	}
	*begin_list = NULL;
}
