/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_vector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <cchadwic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:22:58 by cchadwic          #+#    #+#             */
/*   Updated: 2020/02/22 16:19:32 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec	*ft_create_vec(int len)
{
	t_vec	*vec;

	if (!(vec = malloc(sizeof(t_vec))))
		return (NULL);
	vec->vec = ft_memalloc(len + 1);
	vec->max_size = len;
	vec->curr_size = 0;
	return (vec);
}

t_vec	*ft_realloc_vec(t_vec *vec)
{
	char	*buf;
	size_t	i;

	buf = ft_memalloc(vec->max_size * 4 + 1);
	i = -1;
	while (++i < vec->max_size)
		buf[i] = vec->vec[i];
	vec->max_size *= 4;
	free(vec->vec);
	vec->vec = buf;
	return (vec);
}

t_vec	*ft_put_vec(t_vec *vec, char *line)
{
	size_t		len_line;
	size_t		i;

	len_line = ft_strlen(line) + 1;
	if (!vec)
		vec = ft_create_vec(len_line);
	while (len_line >= (vec->max_size - vec->curr_size))
		vec = ft_realloc_vec(vec);
	i = 0;
	while (i < len_line)
		vec->vec[vec->curr_size++] = line[i++];
	return (vec);
}
