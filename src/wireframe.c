/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wireframe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:14/35 by kfreyer           #+#    #+#             */
/*   Updated: 2024/10/29 13:14:35 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

void	add_back_idx_pair(t_list **l, unsigned int i, unsigned int j)
{
	t_idx_pair	*new;

	new = (t_idx_pair *)malloc(sizeof(t_idx_pair) * 1);
	new->i = i;
	new->j = j;
	ft_lstadd_back(l, ft_lstnew(new));
}

t_list	*get_wireframe_indices(size_t wf_m, size_t wf_n)
{
	t_list	*ret;
	size_t	count_m;
	size_t	count_n;
	size_t	idx;

	ret = NULL;
	count_m = 0;
	idx = 0;
	while (count_m < wf_m)
	{
		count_m++;
		count_n = 0;
		while (count_n < wf_n)
		{
			if (count_n < wf_n-1) {
				add_back_idx_pair(&ret, idx, idx+1);
			}
			if (count_m < wf_m) {
				add_back_idx_pair(&ret, idx, idx + wf_n);
			}
			/* add_back_idx_pair(&ret, count_n, count_n + 1); */
			count_n++;
			idx++;
		}
	}
	return (ret);
}
