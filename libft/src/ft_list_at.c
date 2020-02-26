/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_at.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 12:03:07 by cchadwic          #+#    #+#             */
/*   Updated: 2019/09/09 12:03:12 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_list_at(t_list *begin_list, unsigned int nbr)
{
	if (!(begin_list))
		return (NULL);
	while (begin_list && nbr-- > 0)
	{
		begin_list = begin_list->next;
	}
	if (nbr == 0)
		return (NULL);
	else
		return (begin_list);
}
