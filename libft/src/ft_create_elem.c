/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_elem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 20:02:13 by cchadwic          #+#    #+#             */
/*   Updated: 2019/09/08 20:02:30 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_create_elem(void *data)
{
	t_list	*new_el;

	new_el = malloc(sizeof(t_list));
	if (new_el == 0)
		return (NULL);
	new_el->data = data;
	new_el->next = NULL;
	return (new_el);
}
