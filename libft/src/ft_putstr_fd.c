/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 20:47:58 by cchadwic          #+#    #+#             */
/*   Updated: 2019/09/07 22:54:34 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	ft_putstr_fd(char const *s, int fd)
{
	int i;

	if (!s)
		return ;
	i = ft_strlen(s);
	write(fd, s, i);
}
