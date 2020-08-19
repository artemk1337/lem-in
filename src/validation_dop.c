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

void				free_word_list(char ***words)
{
	int		i;
	char	**words_ar;

	i = -1;
	words_ar = *words;
	if (!*words_ar)
		return ;
	while (words_ar[++i])
		ft_strdel(&words_ar[i]);
	free(*words);
}
