/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <cchadwic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 15:26:54 by cchadwic          #+#    #+#             */
/*   Updated: 2020/02/26 15:37:24 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			clean_tmp(t_tmp **tmp)
{
	t_tmp	*temp_ptr;

	while (*tmp)
	{
		temp_ptr = (*tmp)->next;
		free(*tmp);
		*tmp = temp_ptr;
	}
}
