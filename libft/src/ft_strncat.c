/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 14:56:29 by cchadwic          #+#    #+#             */
/*   Updated: 2019/09/08 13:00:51 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	ft_dop(char *src, char *dest, int *i, int *nb)
{
	int k;

	k = 0;
	if (*nb < 0)
	{
		while (src[k] != '\0')
		{
			dest[*i] = src[k];
			*i += 1;
			k += 1;
		}
	}
	else
	{
		while (src[k] != '\0' && k < *nb)
		{
			dest[*i] = src[k];
			*i += 1;
			k += 1;
		}
	}
}

char		*ft_strncat(char *dest, char *src, int nb)
{
	int i;

	i = 0;
	while (dest[i] != '\0')
		i++;
	ft_dop(src, dest, &i, &nb);
	dest[i] = '\0';
	return (dest);
}
